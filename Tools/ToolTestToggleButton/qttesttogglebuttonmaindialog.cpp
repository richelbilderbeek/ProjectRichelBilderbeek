//---------------------------------------------------------------------------
/*
TestToggleButton, tool to test the ToggleButton class
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
//From http://www.richelbilderbeek.nl/ToolTestToggleButton.htm
//---------------------------------------------------------------------------


#include "qttesttogglebuttonmaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

#include "qtaboutdialog.h"
#include "rainbow.h"
#include "testtogglebuttonmenudialog.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "ui_qttesttogglebuttonmaindialog.h"

ribi::QtTestToggleButtonMainDialog::QtTestToggleButtonMainDialog(QWidget *parent)
 : QDialog(parent),
   ui(new Ui::QtTestToggleButtonMainDialog)
{
  ui->setupUi(this);

  ui->toggle_button->m_signal_toggled.connect(
    boost::bind(
      &ribi::QtTestToggleButtonMainDialog::DisplayToggleButtonValue,
      this));
  ui->toggle_button->GetWidget()->Click(1,1);
}

ribi::QtTestToggleButtonMainDialog::~QtTestToggleButtonMainDialog()
{
  delete ui;
}

void ribi::QtTestToggleButtonMainDialog::DisplayToggleButtonValue()
{
  ui->label_is_pressed->setText(
    (std::string("Is pressed: ")
    + (ui->toggle_button->GetWidget()->GetToggleButton()->IsPressed()
      ? std::string("yes")
      : std::string("no"))).c_str());
  ui->label_color->setText(
    (std::string("Color: (")
    + boost::lexical_cast<std::string>(static_cast<int>(ui->toggle_button->GetWidget()->GetToggleButton()->GetRed()))
    + std::string(",")
    + boost::lexical_cast<std::string>(static_cast<int>(ui->toggle_button->GetWidget()->GetToggleButton()->GetGreen()))
    + std::string(",")
    + boost::lexical_cast<std::string>(static_cast<int>(ui->toggle_button->GetWidget()->GetToggleButton()->GetBlue()))
    + std::string(") (RGB)")).c_str());

}

void ribi::QtTestToggleButtonMainDialog::on_dial_dialMoved(int)
{
  OnDial();
}

void ribi::QtTestToggleButtonMainDialog::OnDial()
{
  const double x
    = static_cast<double>(ui->dial->value())
    / static_cast<double>(ui->dial->maximum());
  double r = 0.0, g = 0.0,b = 0.0;
  Rainbow::GetRgb(x,r,g,b);

  ui->toggle_button->GetWidget()->GetToggleButton()->SetColor(
    static_cast<unsigned char>(r * 255.0),
    static_cast<unsigned char>(g * 255.0),
    static_cast<unsigned char>(b * 255.0));

}

void ribi::QtTestToggleButtonMainDialog::on_dial_sliderPressed()
{
  OnDial();
}

