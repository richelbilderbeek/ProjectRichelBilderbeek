//---------------------------------------------------------------------------
/*
TicTacToeLearner, evolving neural network playing tic-tac-toe
Copyright (C) 2010 Richel Bilderbeek

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
#include "dialogabout.h"
#include "dialogwhatsnew.h"
#include "ui_dialogabout.h"
//---------------------------------------------------------------------------
DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
  ui->setupUi(this);
  QObject::connect(ui->button_whats_new,SIGNAL(clicked()),
    this,SLOT(onWhatsNew()));

  QObject::connect(ui->button_about_qt,SIGNAL(clicked()),qApp,SLOT(aboutQt()));
}
//---------------------------------------------------------------------------
DialogAbout::~DialogAbout()
{
  delete ui;
}
//---------------------------------------------------------------------------
void DialogAbout::changeEvent(QEvent *e)
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
void DialogAbout::onWhatsNew()
{
  DialogWhatsNew d;
  d.exec();
}
//---------------------------------------------------------------------------
