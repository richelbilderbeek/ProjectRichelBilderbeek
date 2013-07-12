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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtcodetohtmlmaindialog.h"

#define QTCODETOHTMLMAINDIALOG_TEMPORARILY_REMOVE_QWEBVIEW_253489729387428907

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/filesystem.hpp>
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

QtCodeToHtmlMainDialog::QtCodeToHtmlMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtCodeToHtmlMainDialog)
{
  ui->setupUi(this);

  //Put this dialog in the screen center
  const QRect scr = QApplication::desktop()->screenGeometry();
  move( scr.center() - rect().center() );

  on_tab_source_currentChanged(0);
}

QtCodeToHtmlMainDialog::~QtCodeToHtmlMainDialog()
{
  delete ui;
}

void QtCodeToHtmlMainDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

const std::vector<std::string> QtCodeToHtmlMainDialog::EditToVector(
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

c2h::PageType QtCodeToHtmlMainDialog::GetPageType() const
{
  const std::string s = ui->box_header->currentText().toStdString();
  if (s == "C++") return c2h::PageType::cpp;
  if (s == "Music") return c2h::PageType::music;
  if (s == "Text") return c2h::PageType::text;
  if (s == "Tool") return c2h::PageType::tool;
  assert(!"Should not get here");
  throw std::logic_error("QtCodeToHtmlMainDialog::GetPageType");
}

c2h::ContentType QtCodeToHtmlMainDialog::GetContentType() const
{
  const std::string s = ui->box_source->currentText().toStdString();
  if (s == "C++") return c2h::ContentType::cpp;
  if (s == "Text") return c2h::ContentType::txt;
  if (s == "Project file") return c2h::ContentType::pro;
  assert(!"Should not get here");
  throw std::logic_error("QtCodeToHtmlMainDialog::GetContentType");
}

c2h::TechInfoType QtCodeToHtmlMainDialog::GetTechInfo() const
{
  const std::string s = ui->box_tech_info->currentText().toStdString();
  if (s == "Auto") return c2h::TechInfoType::automatic;
  if (s == "No") return c2h::TechInfoType::no;
  if (s == "Yes") return c2h::TechInfoType::yes;
  assert(!"Should not get here");
  throw std::logic_error("QtCodeToHtmlMainDialog::GetTechInfo");
}

void QtCodeToHtmlMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtCodeToHtmlMainDialog::on_button_convert_clicked()
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
    boost::filesystem::remove(source);
  }
  else
  {
    //Convert file or folder
    const std::string source = ui->edit_source->text().toStdString();
    if (!boost::filesystem::exists(source))
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
  //Make a screenshot
 // QPixmap::grabWidget(this).save("ToolCodeToHtmlMainDialog.png");
}

void QtCodeToHtmlMainDialog::Display(const std::vector<std::string>& v)
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

void QtCodeToHtmlMainDialog::on_tab_source_currentChanged(int index)
{
  if (index == 0)
  {
    ui->button_convert->setText("&Convert");
    ui->button_convert->setEnabled(true);
  }
  else
  {
    //assert(ui->tab_source->currentWidget() == ui->tab_source_snippet);
    const std::string source = ui->edit_source->text().toStdString();
    if (!boost::filesystem::exists(source))
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

void QtCodeToHtmlMainDialog::on_edit_source_textChanged(QString )
{
  const std::string source = ui->edit_source->text().toStdString();

  if (!boost::filesystem::exists(source))
  {
    ui->button_convert->setText("Source does not exist");
    ui->button_convert->setEnabled(false);
    return;
  }
  if (boost::filesystem::is_directory(source))
  {
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
    assert(boost::filesystem::exists(source));
    ui->button_convert->setText("Convert (source type: file)");
    ui->button_convert->setEnabled(true);
  }
}

