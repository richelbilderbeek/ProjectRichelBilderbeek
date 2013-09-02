//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpictocodemenudialog.h"


#include "about.h"
#include "pictocodemenudialog.h"
#include "qtaboutdialog.h"
#include "qtpictocodemaindialog.h"
#include "ui_qtpictocodemenudialog.h"
//---------------------------------------------------------------------------
QtPicToCodeMenuDialog::QtPicToCodeMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtPicToCodeMenuDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
QtPicToCodeMenuDialog::~QtPicToCodeMenuDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtPicToCodeMenuDialog::changeEvent(QEvent *e)
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
//---------------------------------------------------------------------------
void QtPicToCodeMenuDialog::on_button_start_clicked()
{
  QtPicToCodeMainDialog d;
  this->hide();
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtPicToCodeMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(PicToCodeMenuDialog::GetAbout());
  this->hide();
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtPicToCodeMenuDialog::on_button_quit_clicked()
{
  close();
}
//---------------------------------------------------------------------------
