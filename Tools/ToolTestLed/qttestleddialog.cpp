//---------------------------------------------------------------------------
/*
TestLed, tool to test the Led class
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestLed.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttestleddialog.h"

#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include "qtaboutdialog.h"
#include "qtledwidget.h"
#include "testledmenudialog.h"
#include "ui_qttestleddialog.h"
//---------------------------------------------------------------------------
QtTestLedDialog::QtTestLedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTestLedDialog)
{
  ui->setupUi(this);
  ui->led_red->GetWidget()->GetLed()->SetColor(  255,  0,  0);
  ui->led_green->GetWidget()->GetLed()->SetColor(  0,255,  0);
  ui->led_blue->GetWidget()->GetLed()->SetColor(   0,  0,255);

  ui->led_cyan->GetWidget()->GetLed()->SetColor(     0,255,255);
  ui->led_magenta->GetWidget()->GetLed()->SetColor(255,  0,255);
  ui->led_yellow->GetWidget()->GetLed()->SetColor( 255,255,  0);

  ui->led_black->GetWidget()->GetLed()->SetColor(  0,  0,  0);
  ui->led_gray->GetWidget()->GetLed()->SetColor( 127,127,127);
  ui->led_white->GetWidget()->GetLed()->SetColor(255,255,255);
}
//---------------------------------------------------------------------------
QtTestLedDialog::~QtTestLedDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtTestLedDialog::changeEvent(QEvent *e)
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
void QtTestLedDialog::on_slider_valueChanged(int value)
{
  const double intensity = boost::numeric_cast<double>(value)
    / boost::numeric_cast<double>(ui->slider->maximum());
  ui->led_red->GetWidget()->GetLed()->SetIntensity(intensity);
  ui->led_green->GetWidget()->GetLed()->SetIntensity(intensity);
  ui->led_blue->GetWidget()->GetLed()->SetIntensity(intensity);

  ui->led_cyan->GetWidget()->GetLed()->SetIntensity(intensity);
  ui->led_magenta->GetWidget()->GetLed()->SetIntensity(intensity);
  ui->led_yellow->GetWidget()->GetLed()->SetIntensity(intensity);

  ui->led_black->GetWidget()->GetLed()->SetIntensity(intensity);
  ui->led_gray->GetWidget()->GetLed()->SetIntensity(intensity);
  ui->led_white->GetWidget()->GetLed()->SetIntensity(intensity);
}
//---------------------------------------------------------------------------
void QtTestLedDialog::on_button_about_clicked()
{
  this->hide();
  About a = TestLedMenuDialog::GetAbout();
  a.AddLibrary("QtLedWidget version: " + QtLedWidget::GetVersion());
  QtAboutDialog d(a);
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
