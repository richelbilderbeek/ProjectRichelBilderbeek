//---------------------------------------------------------------------------
/*
QtAboutDialog, Qt dialog for About
Copyright (C) 2011-2012 Richel Bilderbeek

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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtAboutDialog.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtaboutdialog.h"

#include <cassert>
#include <string>

#include "about.h"
//#include "trace.h"

#include "ui_qtaboutdialog.h"


QtAboutDialog::QtAboutDialog(const About& about)
  : ui(new Ui::QtAboutDialog)
{
  ui->setupUi(this);

  ui->label_title->setText(
    QString(about.GetFileTitle().c_str())
    + QString(", version ")
    + QString(about.GetVersion().c_str()));
  ui->label_copyright->setText(
    QString("Copyright (C) ")
    + QString(about.GetYears().c_str())
    + QString(" ")
    + QString(about.GetAuthor().c_str()));
  ui->label_author->setText(
    QString("Programmed by ")
    + QString(about.GetAuthor().c_str()));
  ui->label_date->setText(
    QString("on ")
    + about.GetProgrammedAt().c_str());
  ui->label_download->setText(
    QString(about.GetFileTitle().c_str())
    + QString(" can be downloaded from:"));
  ui->edit_url->setText(about.GetUrl().c_str());

  About about_copy = about;
  about_copy.AddLibrary("Qt version: " + std::string(QT_VERSION_STR));
  about_copy.AddLibrary("QtAboutDialog version: " + GetVersion());

  ui->label_build_date_time->setText(
    QString(
      (std::string("Source code built on ")
      + std::string(__DATE__)
      + std::string(" ")
      + std::string(__TIME__)).c_str()));

  #ifdef NDEBUG
  ui->label_build_type->setText(QString("Release version"));
  #else
  ui->label_build_type->setText(QString("Debug version"));
  #endif

  {
    const std::vector<std::string> v = about_copy.CreateLibrariesUsedText();
    const int j = v.size();
    for (int i=0; i!=j; ++i)
    {
      const std::string& s = v[i];
      assert(!s.empty());
      ui->text_libraries->appendPlainText(QString(s.c_str()));
    }
  }

  {
    const std::vector<std::string> v = about_copy.CreateVersionHistory();
    const int j = v.size();
    for (int i=0; i!=j; ++i)
    {
      const std::string& s = v[i];
      assert(!s.empty());
      ui->text_whatsnew->appendPlainText(QString(s.c_str()));
    }
  }

  {
    const std::vector<std::string> v = about_copy.CreateLicenceText();
    const int j = v.size();
    for (int i=0; i!=j; ++i)
    {
      const std::string& s = v[i];
      ui->text_licence->appendPlainText(QString(s.c_str()));
    }
  }

  ui->text_libraries->moveCursor(QTextCursor::Start);
  ui->text_licence->moveCursor(QTextCursor::Start);
  ui->text_whatsnew->moveCursor(QTextCursor::Start);
}

QtAboutDialog::~QtAboutDialog()
{
  delete ui;
}

const std::string QtAboutDialog::GetVersion()
{
  return "1.5";
}

const std::vector<std::string> QtAboutDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-01-11: version 1.0: initial version of QtAboutDialog");
  v.push_back("2011-04-11: version 1.1: minor changes");
  v.push_back("2011-06-27: version 1.2: added date and time when source code is built");
  v.push_back("2011-09-11: version 1.3: display the type of build");
  v.push_back("2012-01-12: version 1.4: fixed grammatical error");
  v.push_back("2012-01-27: version 1.5: abandoned use of BOOST_FOREACH, due to run-time errors");
  return v;
}

