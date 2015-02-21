// ---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
// ---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
// ---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtcodetohtmlmaindialog.h"

#define QTCODETOHTMLMAINDIALOG_TEMPORARILY_REMOVE_QWEBVIEW_253489729387428907

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
#include <QFile>
#include <QKeyEvent>
#include <QTextBlock>
#include <QTextDocument>

#include "codetohtmlversion.h"
#include "codetohtml.h"
#include "codetohtmlinfo.h"
#include "codetohtmldialog.h"
#include "fileio.h"
#include "qtaboutdialog.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qtcodetohtmlmaindialog.h"
#pragma GCC diagnostic pop

ribi::c2h::QtCodeToHtmlMainDialog::QtCodeToHtmlMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtCodeToHtmlMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Put this dialog in the screen center
  const QRect scr = QApplication::desktop()->screenGeometry();
  move( scr.center() - rect().center() );

  {
    assert(!QApplication::instance()->arguments().empty());
    const std::string argv0 { QApplication::instance()->arguments()[0].toStdString() };
    const std::string path = ribi::fileio::FileIo().GetPath(argv0);
    assert(ribi::fileio::FileIo().IsFolder(path));
    this->ui->edit_source->setText(path.c_str());
  }
  on_tab_source_currentChanged(0);
}

ribi::c2h::QtCodeToHtmlMainDialog::~QtCodeToHtmlMainDialog() noexcept
{
  delete ui;
}

std::vector<std::string> ribi::c2h::QtCodeToHtmlMainDialog::EditToVector(
  const QPlainTextEdit * const edit) noexcept
{
  std::vector<std::string> v;

  const QTextDocument * const doc = edit->document();
  if (!doc) return v;
  const int n_lines = doc->lineCount();
  for (int i=0; i!=n_lines; ++i)
  {
    const QTextBlock block = doc->findBlockByNumber(i);
    if (!block.isValid())
    {
      std::stringstream warning;
      warning  << "block #" << i << " is not valid and is skipped...";
      TRACE(warning.str());
      continue;
    }
    assert(block.isValid());
    const QString line = block.text();
    v.push_back(line.toStdString());
  }
  return v;
}

void ribi::c2h::QtCodeToHtmlMainDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::c2h::QtCodeToHtmlMainDialog::on_button_convert_clicked() noexcept
{
  if (ui->tab_source->currentIndex() == 0)
  {
    //Convert code snippet
    const std::vector<std::string> v = EditToVector(ui->edit_source_snippet);
    const std::vector<std::string> w = Dialog().SnippetToHtml(v,SnippetType::cpp);
    Display(w);
  }
  else
  {
    //Convert file or folder
    const std::string source = ui->edit_source->text().toStdString();
    if (!ribi::fileio::FileIo().IsFolder(source)
      && !ribi::fileio::FileIo().IsRegularFile(source))
    {
      ui->button_convert->setText("Source (file or folder) does not exist");
      ui->button_convert->setEnabled(false);
      return;
    }
    if (ribi::fileio::FileIo().IsRegularFile(source))
    {
      const std::vector<std::string> v { Dialog().FileToHtml(source) };
      Display(v);
    }
    else
    {
      assert(ribi::fileio::FileIo().IsFolder(source));
      const std::vector<std::string> v {
        Dialog().FolderToHtml(source)
      };
      Display(v);
    }

  }
}

void ribi::c2h::QtCodeToHtmlMainDialog::Display(const std::vector<std::string>& v) noexcept
{
  QString text;
  std::for_each(v.begin(),v.end(),
    [&text](std::string s)
    {
      text += QString(s.c_str()) + '\n';
    }
  );
  #ifndef  QTCODETOHTMLMAINDIALOG_TEMPORARILY_REMOVE_QWEBVIEW_253489729387428907
  ui->webView->setHtml(text);
  #endif

  ui->edit_html->setPlainText(text);
}

void ribi::c2h::QtCodeToHtmlMainDialog::on_tab_source_currentChanged(int index) noexcept
{
  if (index == 0)
  {
    ui->button_convert->setText("&Convert");
    ui->button_convert->setEnabled(true);
  }
  else
  {
    const std::string source = ui->edit_source->text().toStdString();
    if (!QFile::exists(source.c_str()))
    {
      ui->button_convert->setText("Source (file or folder) does not exist");
      ui->button_convert->setEnabled(false);
    }
    else
    {
      ui->button_convert->setText("&Convert");
      ui->button_convert->setEnabled(true);
    }
  }
}

void ribi::c2h::QtCodeToHtmlMainDialog::on_edit_source_textChanged(QString ) noexcept
{
  const std::string source = ui->edit_source->text().toStdString();

  if (!QFile::exists(source.c_str()))
  {
    ui->button_convert->setText("Source does not exist");
    ui->button_convert->setEnabled(false);
    return;
  }

  if (!ribi::fileio::FileIo().IsRegularFile(source))
  {
    //source is a folder
    const std::vector<std::string> v
      = c2h::SortFiles(
          c2h::FilterFiles(
            ribi::fileio::FileIo().GetFilesInFolder(source)));
    const std::string s
      = "Convert (source type: folder, "
      + boost::lexical_cast<std::string>(v.size())
      + " files)";

    ui->button_convert->setText(s.c_str());
    ui->button_convert->setEnabled(true);
  }
  else
  {
    assert(ribi::fileio::FileIo().IsRegularFile(source.c_str()));
    ui->button_convert->setText("Convert (source type: file)");
    ui->button_convert->setEnabled(true);
  }
}

#ifndef NDEBUG
void ribi::c2h::QtCodeToHtmlMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
    Dialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //IsRegularFile
  {
    assert(!ribi::fileio::FileIo().IsRegularFile("../ToolCodeToHtml"));
  }
  {
    QtCodeToHtmlMainDialog d;
    for (int index = 0; index != 2; ++index)
    {
      d.ui->tab_source->setCurrentIndex(index);
      for (const std::string& s:
        {
          "/home/richel/ProjectRichelBilderbeek/Tools/ToolTestAbout",
          "D:/Projects/Tools/ToolTestAbout",
          "D:\\Projects\\Tools\\ToolTestAbout",
          "D:/Projects/Test/ToolTestAbout",
          "D:\\Projects\\Test\\ToolTestAbout",
          //"../../Tools/ToolCodeToHtml",
          "..\\..\\Tools\\ToolTestAbout",
          "../../Tools/ToolTestAbout",
          "..\\..\\Tools\\ToolTestAbout",
          "/home/richel/ProjectRichelBilderbeek/Test/ToolTestAbout"
        }
      )
      {
        d.ui->edit_source->setText(s.c_str());
        if (d.ui->button_convert->isEnabled())
        {
          d.on_button_convert_clicked();
        }
      }
    }
  }
}
#endif
