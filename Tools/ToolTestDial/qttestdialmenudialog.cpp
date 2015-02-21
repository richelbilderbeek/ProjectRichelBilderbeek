//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestDial.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testdialmenudialog.h"

#include "about.h"
#include "qtaboutdialog.h"
#include "qtdialwidget.h"
#include "qttestdialmaindialog.h"
#include "qttestdialmenudialog.h"
#include "ui_qttestdialmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestDialMenuDialog::QtTestDialMenuDialog(QWidget *parent) noexcept
 : QtHideAndShowDialog(parent),
   ui(new Ui::QtTestDialMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestDialMenuDialog::~QtTestDialMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestDialMenuDialog::on_button_start_clicked() noexcept
{
  QtTestDialMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestDialMenuDialog::on_button_about_clicked() noexcept
{
  About a = TestDialMenuDialog().GetAbout();
  a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtTestDialMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestDialMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtTestDialMainDialog d;
  }
}
#endif
