//---------------------------------------------------------------------------
/*
TestQtCreatorProFile, tool to test the QtCreatorProFile class
Copyright (C) 2010-2013 Richel Bilderbeek

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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttestqtcreatorprofilemenudialog.h"

#include "qtaboutdialog.h"
#include "qttestqtcreatorprofilemaindialog.h"
#include "testqtcreatorprofilemenudialog.h"
#include "ui_qttestqtcreatorprofilemenudialog.h"

QtTestQtCreatorProFileMenuDialog::QtTestQtCreatorProFileMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestQtCreatorProFileMenuDialog)
{
  ui->setupUi(this);
}

QtTestQtCreatorProFileMenuDialog::~QtTestQtCreatorProFileMenuDialog()
{
  delete ui;
}

void QtTestQtCreatorProFileMenuDialog::on_button_start_clicked()
{
  this->hide();
  QtTestQtCreatorProFileMainDialog d;
  d.exec();
  this->show();
}

void QtTestQtCreatorProFileMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = TestQtCreatorProFileMenuDialog::GetAbout();
  //a.AddLibrary("QtRichelBilderbeekGalleryDialog version: " + QtRichelBilderbeekGalleryDialog::GetVersion());
  //a.AddLibrary("QtRichelBilderbeekResources version: " + RichelBilderbeek::QtResources::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.exec();
  this->show();
}

void QtTestQtCreatorProFileMenuDialog::on_button_quit_clicked()
{
  close();
}

