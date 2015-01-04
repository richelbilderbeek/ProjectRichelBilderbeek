//---------------------------------------------------------------------------
/*
MazeCreator, creates a maze and displays it on screen.
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From hhtp://www.richelbilderbeek.nl/ToolMazeCreator.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmazecreatormenudialog.h"

#include "mazecreatormenudialog.h"
#include "qtaboutdialog.h"
#include "qtmazecreatormaindialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtmazecreatormenudialog.h"
#pragma GCC diagnostic pop

ribi::QtMazeCreatorMenuDialog::QtMazeCreatorMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtMazeCreatorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtMazeCreatorMenuDialog::~QtMazeCreatorMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtMazeCreatorMenuDialog::on_button_start_clicked()
{
  QtMazeCreatorMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtMazeCreatorMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = MazeCreatorMenuDialog().GetAbout();
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtMazeCreatorMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtMazeCreatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
