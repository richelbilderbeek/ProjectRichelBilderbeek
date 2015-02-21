//---------------------------------------------------------------------------
/*
TestPolyFile, tool to test the PolyFile class
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestPolyFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestpolyfilemenudialog.h"

#include "qtaboutdialog.h"
#include "qttestpolyfilemaindialog.h"
#include "testpolyfilemenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestpolyfilemenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestPolyFileMenuDialog::QtTestPolyFileMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestPolyFileMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestPolyFileMenuDialog::~QtTestPolyFileMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestPolyFileMenuDialog::on_button_start_clicked()
{
  QtTestPolyFileMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestPolyFileMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = TestPolyFileMenuDialog().GetAbout();
  //a.AddLibrary("QtRichelBilderbeekGalleryDialog version: " + QtRichelBilderbeekGalleryDialog::GetVersion());
  //a.AddLibrary("QtRichelBilderbeekResources version: " + RichelBilderbeek::QtResources::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtTestPolyFileMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestPolyFileMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
