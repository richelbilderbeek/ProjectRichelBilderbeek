//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
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
//From http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtcreateqtprojectzipfilemenudialog.h"

#include <QKeyEvent>

#include "createqtprojectzipfilemenudialog.h"
#include "qtaboutdialog.h"
#include "qtcreateqtprojectzipfilemaindialog.h"
#include "ui_qtcreateqtprojectzipfilemenudialog.h"

QtCreateQtProjectZipFileMenuDialog::QtCreateQtProjectZipFileMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtCreateQtProjectZipFileMenuDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
}

QtCreateQtProjectZipFileMenuDialog::~QtCreateQtProjectZipFileMenuDialog()
{
  delete ui;
}

void QtCreateQtProjectZipFileMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtCreateQtProjectZipFileMenuDialog::on_button_start_clicked()
{
  QtCreateQtProjectZipFileMainDialog d;
  this->ShowChild(&d);
}

void QtCreateQtProjectZipFileMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = CreateQtProjectZipFile::MenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  d.exec();
  this->show();
}

void QtCreateQtProjectZipFileMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void QtCreateQtProjectZipFileMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  QtCreateQtProjectZipFileMainDialog d;
}
#endif
