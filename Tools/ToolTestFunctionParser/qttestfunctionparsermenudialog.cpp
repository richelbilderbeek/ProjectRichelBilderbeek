//---------------------------------------------------------------------------
/*
TestFunctionParser, tool to demonstrate Warp's FunctionParser class
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestFunctionParser.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestfunctionparsermenudialog.h"

#include "qtaboutdialog.h"
#include "qttestfunctionparsermaindialog.h"
#include "testfunctionparsermenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestfunctionparsermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestFunctionParserMenuDialog::QtTestFunctionParserMenuDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestFunctionParserMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestFunctionParserMenuDialog::~QtTestFunctionParserMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestFunctionParserMenuDialog::on_button_start_clicked() noexcept
{
  QtTestFunctionParserMainDialog d;
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  ShowChild(&d);
}

void ribi::QtTestFunctionParserMenuDialog::on_button_about_clicked() noexcept
{
  About a = TestFunctionParserMenuDialog().GetAbout();
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  ShowChild(&d);
}

void ribi::QtTestFunctionParserMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestFunctionParserMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    TestFunctionParserMenuDialog();
    QtTestFunctionParserMainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
