//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
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
//From http://www.richelbilderbeek.nl/ToolTestDial.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WPushButton>

//#include "about.h"
#include "dial.h"
#include "dialwidget.h"
#include "geometry.h"
#include "rainbow.h"
#include "wtaboutdialog.h"
#include "wtdialwidget.h"
#include "wttestdialmaindialog.h"
#pragma GCC diagnostic pop

ribi::WtTestDialMainDialog::WtTestDialMainDialog()
  : ui{}
{
  this->setContentAlignment(Wt::AlignCenter);
  Show();
}

void ribi::WtTestDialMainDialog::OnDialPositionChange()
{
  const double position = ui.m_dial->GetWidget()->GetDial()->GetPosition();

  const std::string text
    = std::string("Dial angle: ")
    + boost::lexical_cast<std::string>(position);
  ui.m_label_position->setText(text);
}

void ribi::WtTestDialMainDialog::OnDialColorChange()
{
  //Set the color
  {
    const double x = ui.m_dial_color->GetWidget()->GetDial()->GetPosition();

    double r,g,b;
    Rainbow::GetRgb(x,r,g,b);

    ui.m_dial->GetWidget()->GetDial()->SetColor(
      boost::numeric_cast<int>(r * 255.0),
      boost::numeric_cast<int>(g * 255.0),
      boost::numeric_cast<int>(b * 255.0));
  }

  //Check
  {
    const unsigned char r = ui.m_dial->GetWidget()->GetDial()->GetRed();
    const unsigned char g = ui.m_dial->GetWidget()->GetDial()->GetGreen();
    const unsigned char b = ui.m_dial->GetWidget()->GetDial()->GetBlue();

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
}

void ribi::WtTestDialMainDialog::Show()
{
  this->clear();
  {
    ui.m_dial = new WtDialWidget(0.0,255,255,255);
    this->addWidget(ui.m_dial);
    ui.m_dial->GetWidget()->SetGeometry(0,0,100,100);
    ui.m_dial->GetWidget()->GetDial()->m_signal_color_changed.connect(
      boost::bind(
        &ribi::WtTestDialMainDialog::OnDialColorChange,
        this));
    ui.m_dial->GetWidget()->GetDial()->m_signal_position_changed.connect(
      boost::bind(
        &ribi::WtTestDialMainDialog::OnDialPositionChange,
        this));
  }
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  {
    ui.m_label_position = new Wt::WLabel;
    this->addWidget(ui.m_label_position);
  }
  this->addWidget(new Wt::WBreak);
  {
    ui.m_label_color = new Wt::WLabel;
    this->addWidget(ui.m_label_color);
  }
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  new Wt::WLabel("Color:",this);
  this->addWidget(new Wt::WBreak);
  {
    ui.m_dial_color = new WtDialWidget;
    ui.m_dial_color->GetWidget()->SetGeometry(0,0,50,50);
    ui.m_dial_color->GetWidget()->GetDial()->m_signal_position_changed.connect(
      boost::bind(
        &ribi::WtTestDialMainDialog::OnDialColorChange,
        this));
    this->addWidget(ui.m_dial_color);
  }
  this->addWidget(new Wt::WBreak);
  OnDialColorChange();
  OnDialPositionChange();
}

