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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtrandomcodemenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "randomcodemenudialog.h"
#include "qtaboutdialog.h"
#include "qtrandomcodemaindialog.h"
#include "qthideandshowdialog.h"
#include "ui_qtrandomcodemenudialog.h"

QtRandomCodeMenuDialog::QtRandomCodeMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRandomCodeMenuDialog)
{
  ui->setupUi(this);
}

QtRandomCodeMenuDialog::~QtRandomCodeMenuDialog()
{
  delete ui;
}

void QtRandomCodeMenuDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void QtRandomCodeMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtRandomCodeMenuDialog::on_button_about_clicked()
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

void QtRandomCodeMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtRandomCodeMenuDialog::on_button_start_clicked()
{
  QtRandomCodeMainDialog d;
  //d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

