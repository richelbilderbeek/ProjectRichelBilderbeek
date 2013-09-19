//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
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
//From http://www.richelbilderbeek.nl/ToolTestDial.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestdialmaindialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "dial.h"
#include "dialwidget.h"
#include "qtaboutdialog.h"
#include "qtdialwidget.h"
#include "rainbow.h"
#include "ui_qttestdialmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestDialMainDialog::QtTestDialMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestDialMainDialog)
{
  ui->setupUi(this);

  ui->dial->GetWidget()->GetDial()->m_signal_color_changed.connect(
    boost::bind(
      &ribi::QtTestDialMainDialog::DisplayDialColor,
      this));

  ui->dial->GetWidget()->GetDial()->m_signal_position_changed.connect(
    boost::bind(
      &ribi::QtTestDialMainDialog::DisplayDialValue,
      this));

  DisplayDialColor();
  DisplayDialValue();
}

ribi::QtTestDialMainDialog::~QtTestDialMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestDialMainDialog::DisplayDialColor() noexcept
{
  //Check
  const unsigned char r = ui->dial->GetWidget()->GetDial()->GetRed();
  const unsigned char g = ui->dial->GetWidget()->GetDial()->GetGreen();
  const unsigned char b = ui->dial->GetWidget()->GetDial()->GetBlue();

  const std::string text
    = std::string("Color: (")
    + boost::lexical_cast<std::string>(boost::numeric_cast<int>(r))
    + std::string(",")
    + boost::lexical_cast<std::string>(boost::numeric_cast<int>(g))
    + std::string(",")
    + boost::lexical_cast<std::string>(boost::numeric_cast<int>(b))
    + std::string(") (RGB)");
  ui->label_color->setText(text.c_str());
}

void ribi::QtTestDialMainDialog::DisplayDialValue() noexcept
{
  const std::string s
    = std::string("Dial angle: ")
    + boost::lexical_cast<std::string>(ui->dial->GetWidget()->GetDial()->GetPosition());
  ui->label_angle->setText(s.c_str());
}

void ribi::QtTestDialMainDialog::on_dial_color_valueChanged(int /* value */) noexcept
{
  //Set the color
  const double min = boost::numeric_cast<double>(ui->dial_color->minimum());
  const double max = boost::numeric_cast<double>(ui->dial_color->maximum());
  const double pos = boost::numeric_cast<double>(ui->dial_color->value());
  const double x = (pos - min) / (max - min);

  double r,g,b;
  Rainbow::GetRgb(x,r,g,b);

  //const_cast because the non-const version of DialWidget::GetDial
  //is not detected by the compiler somehow?
  this->ui->dial->GetWidget()->GetDial()->SetColor(
    boost::numeric_cast<int>(r * 255.0),
    boost::numeric_cast<int>(g * 255.0),
    boost::numeric_cast<int>(b * 255.0));

}
