//---------------------------------------------------------------------------
/*
RandomCode, tool to generate random C++ code
Copyright (C) 2007-2012  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------


#include "qtrandomcodemenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "randomcodemenudialog.h"
#include "qtaboutdialog.h"
#include "qtrandomcodemaindialog.h"
#include "qthideandshowdialog.h"
#include "ui_qtrandomcodemenudialog.h"

ribi::QtRandomCodeMenuDialog::QtRandomCodeMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRandomCodeMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtRandomCodeMenuDialog::~QtRandomCodeMenuDialog()
{
  delete ui;
}

void ribi::QtRandomCodeMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtRandomCodeMenuDialog::on_button_about_clicked()
{
  About a = RandomCodeMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtRandomCodeMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtRandomCodeMenuDialog::on_button_start_clicked()
{
  QtRandomCodeMainDialog d;
  //d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

