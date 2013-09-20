//---------------------------------------------------------------------------
/*
TestAbout, tests the About classes
Copyright (C) 2012-2013 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestAbout.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtaboutdialog.h"
#include "qttestaboutmaindialog.h"
#include "ui_qttestaboutmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestAboutMainDialog::QtTestAboutMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestAboutMainDialog)
{
  ui->setupUi(this);
}

ribi::QtTestAboutMainDialog::~QtTestAboutMainDialog() noexcept
{
  delete ui;
}

const std::string ribi::QtTestAboutMainDialog::GetVersion() noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::QtTestAboutMainDialog::GetVersionHistory() noexcept
{
  return {
    "2012-01-25: Version 1.0: initial version in Qt4 and C++98",
    "2013-07-12: Version 1.1: transitioned to Qt5 and C++11"
    "2013-09-05: version 1.2: transition to namespace ribi"
  };
}

void ribi::QtTestAboutMainDialog::on_button_about_clicked() noexcept
{
  ribi::About a(
    "Richel Bilderbeek",
    "TestAbout",
    "test the About classes",
    "the 12th of July 2013",
    "2012-2013",
    "http://www.richelbilderbeek.nl/ToolTestAbout.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("SomeLibrary version: X.Y");
  ribi::QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtTestAboutMainDialog::on_button_quit_clicked() noexcept
{
  close();
}

