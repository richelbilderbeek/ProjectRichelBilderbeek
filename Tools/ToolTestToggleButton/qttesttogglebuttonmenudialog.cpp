//---------------------------------------------------------------------------
/*
TestToggleButton, tool to test the ToggleButton class
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
//From http://www.richelbilderbeek.nl/ToolTestToggleButton.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttesttogglebuttonmenudialog.h"

#include "about.h"
#include "qtaboutdialog.h"
#include "qttogglebuttonwidget.h"
#include "qttesttogglebuttonmaindialog.h"
#include "rainbow.h"
#include "testtimer.h"
#include "testtogglebuttonmenudialog.h"
#include "trace.h"
#include "ui_qttesttogglebuttonmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestToggleButtonMenuDialog::QtTestToggleButtonMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestToggleButtonMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestToggleButtonMenuDialog::~QtTestToggleButtonMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestToggleButtonMenuDialog::on_button_start_clicked()
{
  QtTestToggleButtonMainDialog d;
  //d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestToggleButtonMenuDialog::on_button_about_clicked()
{
  hide();
  About a = TestToggleButtonMenuDialog().GetAbout();
  a.AddLibrary("QtToggleButtonWidget version: " + QtToggleButtonWidget::GetVersion());
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtTestToggleButtonMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestToggleButtonMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
