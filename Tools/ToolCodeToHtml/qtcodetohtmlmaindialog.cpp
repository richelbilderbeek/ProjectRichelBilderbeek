// ---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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


#include "qtcodetohtmlmaindialog.h"

#define QTCODETOHTMLMAINDIALOG_TEMPORARILY_REMOVE_QWEBVIEW_253489729387428907

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

#include <QDesktopWidget>
#include <QFile>
#include <QKeyEvent>
#include <QTextBlock>
#include <QTextDocument>

#include "codetohtmlversion.h"
#include "codetohtml.h"
#include "codetohtmldialog.h"
#include "qtaboutdialog.h"
#include "trace.h"
#include "ui_qtcodetohtmlmaindialog.h"

ribi::QtCodeToHtmlMainDialog::QtCodeToHtmlMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtCodeToHtmlMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Put this dialog in the screen center
  const QRect scr = QApplication::desktop()->screenGeometry();
  move( scr.center() - rect().center() );

  on_tab_source_currentChanged(0);
}

ribi::QtCodeToHtmlMainDialog::~QtCodeToHtmlMainDialog()
{
  delete ui;
}

const std::vector<std::string> ribi::QtCodeToHtmlMainDialog::EditToVector(
  const QPlainTextEdit * const edit)
{
  std::vector<std::string> v;

  const QTextDocument * const doc = edit->document();
  if (!doc) return v;
  const int n_lines = doc->lineCount();
  //std::clog << "Source text contains " << n_lines << " line(s)\n";
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
    //std::clog << "Line " << i << "/" << n_lines
    //  << " has text '" << line.toStdString() << "'\n";
    v.push_back(line.toStdString());
  }
  return v;
}

c2h::PageType ribi::QtCodeToHtmlMainDialog::GetPageType() const
{
  const std::string s = ui->box_header->currentText().toStdString();
  if (s == "C++") return c2h::PageType::cpp;
  if (s == "Music") return c2h::PageType::music;
  if (s == "Text") return c2h::PageType::text;
  if (s == "Tool") return c2h::PageType::tool;
  assert(!"Should not get here");
  throw std::logic_error("QtCodeToHtmlMainDialog::GetPageType");
}

c2h::ContentType ribi::QtCodeToHtmlMainDialog::GetContentType() const
{
  const std::string s = ui->box_source->currentText().toStdString();
  if (s == "C++") return c2h::ContentType::cpp;
  if (s == "Text") return c2h::ContentType::txt;
  if (s == "Project file") return c2h::ContentType::pro;
  assert(!"Should not get here");
  throw std::logic_error("QtCodeToHtmlMainDialog::GetContentType");
}

c2h::TechInfoType ribi::QtCodeToHtmlMainDialog::GetTechInfo() const
{
  const std::string s = ui->box_tech_info->currentText().toStdString();
  if (s == "Auto") return c2h::TechInfoType::automatic;
  if (s == "No") return c2h::TechInfoType::no;
  if (s == "Yes") return c2h::TechInfoType::yes;
  assert(!"Should not get here");
  throw std::logic_error("QtCodeToHtmlMainDialog::GetTechInfo");
}

void ribi::QtCodeToHtmlMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtCodeToHtmlMainDialog::on_button_convert_clicked()
{
  if (ui->tab_source->currentIndex() == 0)
  {
    //Convert code snippet
    const std::string source
      = std::string(std::tmpnam(0))
      + (GetContentType() == c2h::ContentType::cpp ? ".cpp" : ".txt");
    {
      const std::vector<std::string> v = EditToVector(ui->edit_source_snippet);
      std::ofstream f(source.c_str());
      std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    }
    c2h::Dialog d(
      GetPageType(),
      source,
      GetContentType(),
      GetTechInfo());
    const std::vector<std::string> v = d.ToHtml();
    Display(v);
    std::remove(source.c_str());
  }
  else
  {
    //Convert file or folder
    const std::string source = ui->edit_source->text().toStdString();
    if (!QFile::exists(source.c_str()))
    {
      ui->button_convert->setText("Source (file or folder) does not exist");
      ui->button_convert->setEnabled(false);
      return;
    }
    c2h::Dialog d(
      GetPageType(),
      source,
      GetContentType(),
      GetTechInfo());
    const std::vector<std::string> v = d.ToHtml();
    Display(v);
  }
}

void ribi::QtCodeToHtmlMainDialog::Display(const std::vector<std::string>& v)
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

void ribi::QtCodeToHtmlMainDialog::on_tab_source_currentChanged(int index)
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

void ribi::QtCodeToHtmlMainDialog::on_edit_source_textChanged(QString )
{
  const std::string source = ui->edit_source->text().toStdString();

  if (!QFile::exists(source.c_str()))
  {
    ui->button_convert->setText("Source does not exist");
    ui->button_convert->setEnabled(false);
    return;
  }

  if (!c2h::IsRegularFile(source))
  {
    //source is a folder
    const std::vector<std::string> v
      = c2h::SortFiles(
          c2h::FilterFiles(
            c2h::GetFilesInFolder(source)));
    const std::string s
      = std::string("Convert (source type: folder, ")
      + boost::lexical_cast<std::string>(v.size())
      + std::string(" files)");

    ui->button_convert->setText(s.c_str());
    ui->button_convert->setEnabled(true);
  }
  else
  {
    assert(c2h::IsRegularFile(source.c_str()));
    ui->button_convert->setText("Convert (source type: file)");
    ui->button_convert->setEnabled(true);
  }
}

#ifndef NDEBUG
void ribi::QtCodeToHtmlMainDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtCodeToHtmlMainDialog::Test");
  //IsRegularFile
  {
    assert(!c2h::IsRegularFile("../ToolCodeToHtml"));
  }
  {
    QtCodeToHtmlMainDialog d;
    for (int index = 0; index != 2; ++index)
    {
      d.ui->tab_source->setCurrentIndex(index);
      for (const std::string& s:
        {
          "/home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml",
          "E:/Projects/Tools/ToolCodeToHtml",
          "../../Tools/ToolCodeToHtml"
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
  TRACE("Finished QtCodeToHtmlMainDialog::Test successfully");
}
#endif
