//---------------------------------------------------------------------------
/*
SurfacePlotter, plots a bivariate function
Copyright (C) 2010-2012  Richel Bilderbeek

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
#include "toolsurfaceplottermenudialog.h"
#include "qttoolsurfaceplottermaindialog.h"
#include "qttoolsurfaceplottermenudialog.h"
#include "trace.h"
#include "ui_qttoolsurfaceplottermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtToolSurfacePlotterMenuDialog::QtToolSurfacePlotterMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtToolSurfacePlotterMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolSurfacePlotterMenuDialog::~QtToolSurfacePlotterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtToolSurfacePlotterMenuDialog::on_button_start_clicked()
{
  QtToolSurfacePlotterMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtToolSurfacePlotterMenuDialog::on_button_about_clicked()
{
  About a(ToolSurfacePlotterMenuDialog().GetAbout());
  a.AddLibrary("QtSurfacePlotWidget version: " + QtSurfacePlotWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtToolSurfacePlotterMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtToolSurfacePlotterMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtToolSurfacePlotterMenuDialog::Test");
  TRACE("Finished ribi::QtToolSurfacePlotterMenuDialog::Test successfully");
}
#endif
