//---------------------------------------------------------------------------
/*
SurfacePlotter, plots a bivariate function
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
//From http://www.richelbilderbeek.nl/ToolSurfacePlotter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtaboutdialog.h"
#include "qtsurfaceplotwidget.h"
#include "surfaceplottermenudialog.h"
#include "qtsurfaceplotterqwtdialog.h"
#include "qtsurfaceplotterribidialog.h"
#include "qtsurfaceplottermenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtsurfaceplottermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtSurfacePlotterMenuDialog::QtSurfacePlotterMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtSurfacePlotterMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtSurfacePlotterMenuDialog::~QtSurfacePlotterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtSurfacePlotterMenuDialog::on_button_about_clicked()
{
  About a(SurfacePlotterMenuDialog().GetAbout());
  a.AddLibrary("QtSurfacePlotWidget version: " + QtSurfacePlotWidget::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtSurfacePlotterMenuDialog::on_button_quit_clicked()
{
  this->close();
}

void ribi::QtSurfacePlotterMenuDialog::on_button_qwt_clicked()
{
  QtSurfacePlotterQwtDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtSurfacePlotterMenuDialog::on_button_ribi_clicked()
{
  QtSurfacePlotterRibiDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtSurfacePlotterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtSurfacePlotterRibiDialog();
  QtSurfacePlotterQwtDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

