//---------------------------------------------------------------------------
/*
TestQtCreatorProFile, tool to test the QtCreatorProFile class
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtCreatorProFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestqtcreatorprofilemenudialog.h"

#include <cassert>

#include "qtaboutdialog.h"
#include "qttestqtcreatorprofilemaindialog.h"
#include "testtimer.h"
#include "testqtcreatorprofilemenudialog.h"
#include "trace.h"
#include "ui_qttestqtcreatorprofilemenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtCreatorProFileMenuDialog::QtTestQtCreatorProFileMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestQtCreatorProFileMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestQtCreatorProFileMenuDialog::~QtTestQtCreatorProFileMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtCreatorProFileMenuDialog::on_button_start_clicked()
{
  QtTestQtCreatorProFileMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestQtCreatorProFileMenuDialog::on_button_about_clicked()
{
  About a = TestQtCreatorProFileMenuDialog().GetAbout();
  //a.AddLibrary("QtRichelBilderbeekGalleryDialog version: " + QtRichelBilderbeekGalleryDialog::GetVersion());
  //a.AddLibrary("QtRichelBilderbeekResources version: " + RichelBilderbeek::QtResources::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtTestQtCreatorProFileMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestQtCreatorProFileMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TestQtCreatorProFileMenuDialog();
  {
    const TestQtCreatorProFileMenuDialog d;
    assert(!d.GetVersion().empty());
  }
  {
    const QtTestQtCreatorProFileMainDialog d;
    assert(!d.GetVersion().empty());
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
