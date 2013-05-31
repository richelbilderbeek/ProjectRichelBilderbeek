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
#include "qtaboutdialog.h"
#include "qtsurfaceplotwidget.h"
#include "toolsurfaceplottermenudialog.h"
#include "qttoolsurfaceplottermaindialog.h"
#include "qttoolsurfaceplottermenudialog.h"
#include "ui_qttoolsurfaceplottermenudialog.h"

QtToolSurfacePlotterMenuDialog::QtToolSurfacePlotterMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtToolSurfacePlotterMenuDialog)
{
    ui->setupUi(this);
}

QtToolSurfacePlotterMenuDialog::~QtToolSurfacePlotterMenuDialog()
{
    delete ui;
}

void QtToolSurfacePlotterMenuDialog::on_button_start_clicked()
{
  QtToolSurfacePlotterMainDialog d;
  this->hide();
  d.exec();
  this->show();
}

void QtToolSurfacePlotterMenuDialog::on_button_about_clicked()
{
  About a(ToolSurfacePlotterMenuDialog::GetAbout());
  a.AddLibrary("QtSurfacePlotWidget version: " + QtSurfacePlotWidget::GetVersion());
  QtAboutDialog d(a);
  this->hide();
  d.exec();
  this->show();
}

void QtToolSurfacePlotterMenuDialog::on_button_quit_clicked()
{
  this->close();
}
