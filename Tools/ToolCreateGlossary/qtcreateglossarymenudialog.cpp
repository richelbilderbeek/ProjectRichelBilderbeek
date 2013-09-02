//---------------------------------------------------------------------------
/*
CreateGlossary, tool to create my glossaries
Copyright (C) 2011-2012 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCreateGlossary.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtcreateglossarymenudialog.h"

#include "createglossarymenudialog.h"
#include "qtaboutdialog.h"
#include "qtcreateglossarymaindialog.h"
#include "ui_qtcreateglossarymenudialog.h"
#include "createglossarymaindialog.h"

QtCreateGlossaryMenuDialog::QtCreateGlossaryMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtCreateGlossaryMenuDialog)
{
  ui->setupUi(this);
}

QtCreateGlossaryMenuDialog::~QtCreateGlossaryMenuDialog()
{
  delete ui;
}

void QtCreateGlossaryMenuDialog::changeEvent(QEvent *e)
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

void QtCreateGlossaryMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(CreateGlossaryMenuDialog::GetAbout());
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtCreateGlossaryMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtCreateGlossaryMenuDialog::on_button_start_clicked()
{
  //Make a screenshot
  QPixmap::grabWidget(this,this->window()->rect()).save("ToolCreateGlossaryMenuDialog.png");

  QtCreateGlossaryMainDialog d;
  //d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

