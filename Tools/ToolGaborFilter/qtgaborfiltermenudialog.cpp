//---------------------------------------------------------------------------
/*
GaborFilter, tool to demonstrate Gabor filtering
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolGaborFilter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtgaborfiltermenudialog.h"

#include "qtaboutdialog.h"
#include "gaborfiltermenudialog.h"
#include "qtgaborfiltermaindialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtgaborfiltermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtToolGaborFilterMenuDialog::QtToolGaborFilterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtToolGaborFilterMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolGaborFilterMenuDialog::~QtToolGaborFilterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtToolGaborFilterMenuDialog::on_button_start_clicked()
{
  QtToolGaborFilterMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtToolGaborFilterMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(ToolGaborFilterMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtToolGaborFilterMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtToolGaborFilterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
