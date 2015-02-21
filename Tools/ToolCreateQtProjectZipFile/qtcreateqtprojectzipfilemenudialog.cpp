//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
Copyright (C) 2012-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtcreateqtprojectzipfilemenudialog.h"

#include <QKeyEvent>

#include "createqtprojectzipfilemenudialog.h"
#include "qtaboutdialog.h"
#include "qtcreateqtprojectzipfilemaindialog.h"
#include "ui_qtcreateqtprojectzipfilemenudialog.h"
#pragma GCC diagnostic pop

ribi::QtCreateQtProjectZipFileMenuDialog::QtCreateQtProjectZipFileMenuDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtCreateQtProjectZipFileMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtCreateQtProjectZipFileMenuDialog::~QtCreateQtProjectZipFileMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtCreateQtProjectZipFileMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtCreateQtProjectZipFileMenuDialog::on_button_start_clicked() noexcept
{
  QtCreateQtProjectZipFileMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtCreateQtProjectZipFileMenuDialog::on_button_about_clicked() noexcept
{
  this->hide();
  About a = CreateQtProjectZipFile::MenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtCreateQtProjectZipFileMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtCreateQtProjectZipFileMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtCreateQtProjectZipFileMainDialog d;
}
#endif
