//---------------------------------------------------------------------------
/*
TestNeuralNet, tool to test the NeuralNet class
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
//From http://www.richelbilderbeek.nl/ToolTestNeuralNet.htm
//---------------------------------------------------------------------------
#include "dialogabout.h"
#include "dialogmain.h"
#include "ui_dialogmain.h"
//---------------------------------------------------------------------------
DialogMain::DialogMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMain)
{
  ui->setupUi(this);

  QObject::connect(ui->button_about,SIGNAL(clicked()),
    this,SLOT(onAbout()));
}
//---------------------------------------------------------------------------
DialogMain::~DialogMain()
{
  delete ui;
}
//---------------------------------------------------------------------------
void DialogMain::changeEvent(QEvent *e)
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
void DialogMain::onAbout()
{
  DialogAbout d;
  d.exec();
}
//---------------------------------------------------------------------------
