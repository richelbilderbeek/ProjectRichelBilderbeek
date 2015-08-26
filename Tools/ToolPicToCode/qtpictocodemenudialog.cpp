//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpictocodemenudialog.h"

#include <cassert>

#include "about.h"
#include "pictocodemenudialog.h"
#include "qtaboutdialog.h"
#include "testtimer.h"
#include "qtpictocodemaindialog.h"
#include "trace.h"
#include "ui_qtpictocodemenudialog.h"
#pragma GCC diagnostic pop

ribi::p2c::QtMenuDialog::QtMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtPicToCodeMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::p2c::QtMenuDialog::~QtMenuDialog() noexcept
{
  delete ui;
}

void ribi::p2c::QtMenuDialog::on_button_start_clicked()
{
  QtMainDialog d;
  this->ShowChild(&d);
}

void ribi::p2c::QtMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(MenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::p2c::QtMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::p2c::QtMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
