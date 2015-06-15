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
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WSlider>

#include "about.h"
#include "dial.h"
#include "dialwidget.h"
#include "rainbow.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "testtogglebuttonmenudialog.h"
#include "wtaboutdialog.h"
#include "wtdialwidget.h"
#include "wttogglebuttonwidget.h"
#include "wttesttogglebuttonmaindialog.h"
#pragma GCC diagnostic pop

ribi::WtTestToggleButtonMainDialog::WtTestToggleButtonMainDialog()
  : m_dialog(new TestToggleButtonMenuDialog),
    ui{}
{
  this->setContentAlignment(Wt::AlignCenter);
  ShowMain();
}

void ribi::WtTestToggleButtonMainDialog::OnAboutClick()
{
  ShowAbout();
}

void ribi::WtTestToggleButtonMainDialog::OnDialChanged()
{
  const double x = ui.m_dial->GetWidget()->GetDial()->GetPosition();

  double r,g,b;
  Rainbow::GetRgb(x,r,g,b);

  ui.m_toggle_button->GetWidget()->GetToggleButton()->SetColor(
    boost::numeric_cast<int>(r * 255.0),
    boost::numeric_cast<int>(g * 255.0),
    boost::numeric_cast<int>(b * 255.0));
}

void ribi::WtTestToggleButtonMainDialog::OnToggleButtonColorChanged()
{
  const unsigned char r = ui.m_toggle_button->GetWidget()->GetToggleButton()->GetRed();
  const unsigned char g = ui.m_toggle_button->GetWidget()->GetToggleButton()->GetGreen();
  const unsigned char b = ui.m_toggle_button->GetWidget()->GetToggleButton()->GetBlue();

  const std::string text
    = std::string("Color: (")
    + boost::lexical_cast<std::string>(boost::numeric_cast<int>(r))
    + std::string(",")
    + boost::lexical_cast<std::string>(boost::numeric_cast<int>(g))
    + std::string(",")
    + boost::lexical_cast<std::string>(boost::numeric_cast<int>(b))
    + std::string(") (RGB)");
  ui.m_label_color->setText(text);
}

void ribi::WtTestToggleButtonMainDialog::OnToggleButtonToggled()
{
  ui.m_label_toggle->setText(
      (std::string("Is pressed: ")
    + std::string(ui.m_toggle_button->GetWidget()->GetToggleButton()->IsPressed()
      ? "yes" : "no")).c_str());
}

void ribi::WtTestToggleButtonMainDialog::ShowAbout()
{
  About a = TestToggleButtonMenuDialog().GetAbout();
  WtAboutDialog * const d = new WtAboutDialog(a);
  d->m_signal_close.connect(
    boost::bind(
    &ribi::WtTestToggleButtonMainDialog::ShowMain,
    this));
  this->clear();
  this->addWidget(d);
}

void ribi::WtTestToggleButtonMainDialog::ShowMain()
{
  this->clear();
  this->addWidget(new Wt::WBreak);
  {
    ui.m_toggle_button = new WtToggleButtonWidget(false,127,127,127);
    this->addWidget(ui.m_toggle_button);
    ui.m_toggle_button->GetWidget()->GetToggleButton()->m_signal_color_changed.connect(
      boost::bind(
        &ribi::WtTestToggleButtonMainDialog::OnToggleButtonColorChanged,
        this));

    ui.m_toggle_button->GetWidget()->GetToggleButton()->m_signal_toggled.connect(
      boost::bind(
        &ribi::WtTestToggleButtonMainDialog::OnToggleButtonToggled,
      this));
    ui.m_toggle_button->GetWidget()->SetGeometry(0,0,200,100);
  }
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  {
    ui.m_label_toggle = new Wt::WLabel;
    this->addWidget(ui.m_label_toggle);
  }
  this->addWidget(new Wt::WBreak);
  {
    ui.m_label_color = new Wt::WLabel;
    this->addWidget(ui.m_label_color);
  }
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WLabel("Change the toggle button its color:"));
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  {
    ui.m_dial= new WtDialWidget;
    ui.m_dial->GetWidget()->GetDial()->m_signal_position_changed.connect(
      boost::bind(
        &ribi::WtTestToggleButtonMainDialog::OnDialChanged,
        this));
    this->addWidget(ui.m_dial);
  }

  OnToggleButtonToggled();
  OnToggleButtonColorChanged();
}

