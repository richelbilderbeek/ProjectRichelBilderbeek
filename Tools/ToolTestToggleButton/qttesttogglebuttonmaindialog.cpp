//---------------------------------------------------------------------------
/*
TestToggleButton, tool to test the ToggleButton class
Copyright (C) 2011-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttesttogglebuttonmaindialog.h"

#include <boost/lexical_cast.hpp>


#include "drawcanvas.h"
#include "qtaboutdialog.h"
#include "rainbow.h"
#include "testtogglebuttonmenudialog.h"
#include "togglebutton.h"
#include "testtimer.h"
#include "togglebuttonwidget.h"
#include "trace.h"
#include "ui_qttesttogglebuttonmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestToggleButtonMainDialog::QtTestToggleButtonMainDialog(QWidget *parent)
 : QtHideAndShowDialog(parent),
   ui(new Ui::QtTestToggleButtonMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  ui->toggle_button->m_signal_toggled.connect(
    boost::bind(
      &ribi::QtTestToggleButtonMainDialog::DisplayToggleButtonValue,
      this));
  ui->toggle_button->GetWidget()->Click(1,1);
}

ribi::QtTestToggleButtonMainDialog::~QtTestToggleButtonMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestToggleButtonMainDialog::DisplayToggleButtonValue()
{
  ui->label_is_pressed->setText(
    (
      std::string("Is pressed: ")
      + (
        ui->toggle_button->GetWidget()->GetToggleButton()->IsPressed()
        ? "yes"
        : "no"
        )
    ).c_str()
  );
  ui->label_color->setText(
    ("Color: ("
    + boost::lexical_cast<std::string>(static_cast<int>(ui->toggle_button->GetWidget()->GetToggleButton()->GetRed()))
    + ","
    + boost::lexical_cast<std::string>(static_cast<int>(ui->toggle_button->GetWidget()->GetToggleButton()->GetGreen()))
    + ","
    + boost::lexical_cast<std::string>(static_cast<int>(ui->toggle_button->GetWidget()->GetToggleButton()->GetBlue()))
    + ") (RGB)").c_str());

  std::string text;
  for (const std::string& s: ui->toggle_button->GetWidget()->ToDrawCanvas(30,10)->ToStrings())
  {
    text += s + '\n';
  }
  ui->text->setPlainText(text.c_str());
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

#ifndef NDEBUG
void ribi::QtTestToggleButtonMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
