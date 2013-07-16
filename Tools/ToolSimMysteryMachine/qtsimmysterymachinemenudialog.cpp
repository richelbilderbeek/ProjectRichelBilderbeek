//---------------------------------------------------------------------------
/*
SimMysteryMachine, simulator of my mystery machine
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
//From http://www.richelbilderbeek.nl/ToolSimMysteryMachine.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtsimmysterymachinemenudialog.h"



#include "dial.h"
#include "led.h"
#include "ledwidget.h"
#include "qtaboutdialog.h"
#include "qtdialwidget.h"
#include "qtledwidget.h"

#include "qtmysterymachinewidget.h"
#include "qtsimmysterymachineinstructionsdialog.h"
#include "qtsimmysterymachinemaindialog.h"
#include "qtsimmysterymachinerealmachinedialog.h"
#include "qttogglebuttonwidget.h"
#include "simmysterymachinemenudialog.h"
#include "ui_qtsimmysterymachinemenudialog.h"

QtSimMysteryMachineMenuDialog::QtSimMysteryMachineMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtSimMysteryMachineMenuDialog)
{
  ui->setupUi(this);

  ui->led_1->GetWidget()->GetLed()->SetColor(255,255,255);
  ui->led_2->GetWidget()->GetLed()->SetColor(255,  0,  0);
  ui->led_3->GetWidget()->GetLed()->SetColor(  0,255,  0);
  ui->led_4->GetWidget()->GetLed()->SetColor(  0,  0,255);
  ui->led_5->GetWidget()->GetLed()->SetColor(  0,  0,  0);
  /*
  const int size = ui->button_about->height() + 8;
  ui->led_1->GetWidget()->SetGeometry(Rect(0,0,size,size));
  ui->led_2->GetWidget()->SetGeometry(Rect(0,0,size,size));
  ui->led_3->GetWidget()->SetGeometry(Rect(0,0,size,size));
  ui->led_4->GetWidget()->SetGeometry(Rect(0,0,size,size));
  ui->led_5->GetWidget()->SetGeometry(Rect(0,0,size,size));
  */
}

QtSimMysteryMachineMenuDialog::~QtSimMysteryMachineMenuDialog()
{
  delete ui;
}

void QtSimMysteryMachineMenuDialog::changeEvent(QEvent *e)
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

void QtSimMysteryMachineMenuDialog::on_button_start_clicked()
{
  this->hide();
  QtSimMysteryMachineMainDialog d;
  d.exec();
  this->show();
}

void QtSimMysteryMachineMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = SimMysteryMachineMenuDialog::GetAbout();
  a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  a.AddLibrary("QtLedWidget version: " + QtLedWidget::GetVersion());
  a.AddLibrary("QtMysteryMachineWidget version: " + QtMysteryMachineWidget::GetVersion());
  a.AddLibrary("QtToggleButtonWidget version: " + QtToggleButtonWidget::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  d.exec();
  this->show();
}

void QtSimMysteryMachineMenuDialog::on_button_quit_clicked()
{
  this->close();
}

void QtSimMysteryMachineMenuDialog::on_button_instructions_clicked()
{
  this->hide();
  QtSimMysteryMachineInstructionsDialog d;
  d.exec();
  this->show();
}

void QtSimMysteryMachineMenuDialog::on_button_real_clicked()
{
  this->hide();
  QtSimMysteryMachineRealMachineDialog d;
  d.exec();
  this->show();
}

