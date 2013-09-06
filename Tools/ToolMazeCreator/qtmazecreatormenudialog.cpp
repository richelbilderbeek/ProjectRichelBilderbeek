//---------------------------------------------------------------------------
/*
MazeCreator, creates a maze and displays it on screen.
Copyright (C) 2007-2012 Richel Bilderbeek

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


#include "qtmazecreatormenudialog.h"

#include "mazecreatormenudialog.h"
#include "qtaboutdialog.h"
#include "qtmazecreatormaindialog.h"
#include "ui_qtmazecreatormenudialog.h"
//---------------------------------------------------------------------------
ribi::QtMazeCreatorMenuDialog::QtMazeCreatorMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtMazeCreatorMenuDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
ribi::QtMazeCreatorMenuDialog::~QtMazeCreatorMenuDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void ribi::QtMazeCreatorMenuDialog::on_button_start_clicked()
{
  this->hide();
  QtMazeCreatorMainDialog d;
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void ribi::QtMazeCreatorMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = MazeCreatorMenuDialog::GetAbout();
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  QtAboutDialog d(a);
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void ribi::QtMazeCreatorMenuDialog::on_button_quit_clicked()
{
  close();
}
//---------------------------------------------------------------------------
