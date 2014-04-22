//---------------------------------------------------------------------------
/*
QtAboutDialog, Qt dialog for About
Copyright (C) 2011-2014 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtaboutdialog.h"

#include <cassert>
#include <string>

#include "about.h"
//#include "trace.h"

#include "ui_qtaboutdialog.h"

#pragma GCC diagnostic pop

ribi::QtAboutDialog::QtAboutDialog(const ribi::About& about) noexcept
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

  auto about_copy = about;
  about_copy.AddLibrary("Qt version: " + std::string(QT_VERSION_STR));
  about_copy.AddLibrary("QtAboutDialog version: " + GetVersion());

  ui->label_build_date_time->setText(
    QString(
      (std::string("Source code built on ")
      + __DATE__
      + " "
      + __TIME__).c_str()));

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

ribi::QtAboutDialog::~QtAboutDialog() noexcept
{
  delete ui;
}

std::string ribi::QtAboutDialog::GetVersion() noexcept
{
  return "1.9";
}

std::vector<std::string> ribi::QtAboutDialog::GetVersionHistory() noexcept
{
  return {
    "2011-01-11: version 1.0: initial version of QtAboutDialog",
    "2011-04-11: version 1.1: minor changes",
    "2011-06-27: version 1.2: added date and time when source code is built",
    "2011-09-11: version 1.3: display the type of build",
    "2012-01-12: version 1.4: fixed grammatical error",
    "2012-01-27: version 1.5: abandoned use of BOOST_FOREACH, due to run-time errors",
    "2013-09-05: version 1.6: transition to namespace ribi"
    "2013-09-10: version 1.7: explicitly disabled copying, compiles with -Weffc++"
    "2013-09-16: version 1.8: noexcept",
    "2013-09-19: version 1.9: derive from QtHideAndShowDialog"
  };
}

