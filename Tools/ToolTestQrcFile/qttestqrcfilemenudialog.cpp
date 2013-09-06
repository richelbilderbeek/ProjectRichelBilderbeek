//---------------------------------------------------------------------------
/*
TestQrcFile, tool to test the QrcFile class
Copyright (C) 2012-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQrcFile.htm
//---------------------------------------------------------------------------


#include "qttestqrcfilemenudialog.h"


#include "qtaboutdialog.h"
#include "qttestqrcfilemaindialog.h"
#include "testqrcfilemenudialog.h"
#include "ui_qttestqrcfilemenudialog.h"

QtTestQrcFileMenuDialog::QtTestQrcFileMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestQrcFileMenuDialog)
{
  ui->setupUi(this);
}

QtTestQrcFileMenuDialog::~QtTestQrcFileMenuDialog()
{
  delete ui;
}

void QtTestQrcFileMenuDialog::on_button_start_clicked()
{
  this->hide();
  QtTestQrcFileMainDialog d;
  d.exec();
  this->show();
}

void QtTestQrcFileMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = TestQrcFileMenuDialog::GetAbout();
  //a.AddLibrary("QtRichelBilderbeekGalleryDialog version: " + QtRichelBilderbeekGalleryDialog::GetVersion());
  //a.AddLibrary("QtRichelBilderbeekResources version: " + RichelBilderbeek::QtResources::GetVersion());
  QtAboutDialog d(a);
  d.exec();
  this->show();
}

void QtTestQrcFileMenuDialog::on_button_quit_clicked()
{
  close();
}

