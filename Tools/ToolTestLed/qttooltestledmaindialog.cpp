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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttooltestledmaindialog.h"

#include <boost/numeric/conversion/cast.hpp>

#include "qtaboutdialog.h"
#include "qtledwidget.h"
#include "tooltestledmenudialog.h"
#include "ui_qttooltestledmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestLedMainDialog::QtTestLedMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestLedMainDialog)
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

ribi::QtTestLedMainDialog::~QtTestLedMainDialog() noexcept
{
  delete ui;
}


void ribi::QtTestLedMainDialog::on_slider_valueChanged(int value) noexcept
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
