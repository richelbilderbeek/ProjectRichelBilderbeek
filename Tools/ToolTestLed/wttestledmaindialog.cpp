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
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WPushButton>
//---------------------------------------------------------------------------
#include "about.h"
#include "dial.h"
#include "dialwidget.h"
#include "led.h"
#include "ledwidget.h"
#include "rainbow.h"
//#include "testledmenudialog.h"
#include "wtaboutdialog.h"
#include "wtdialwidget.h"
#include "wtledwidget.h"
#include "wttestledmaindialog.h"
//---------------------------------------------------------------------------
ribi::WtTestLedMainDialog::WtTestLedMainDialog()
  : ui{}
{
  ShowMain();
}
//---------------------------------------------------------------------------
void ribi::WtTestLedMainDialog::OnDialColorChange()
{
  double r_d,g_d,b_d;
  Rainbow::GetRgb(ui.m_dial_color->GetWidget()->GetDial()->GetPosition(),r_d,g_d,b_d);
  const unsigned char r = boost::numeric_cast<unsigned char>(r_d * 255.0);
  const unsigned char g = boost::numeric_cast<unsigned char>(g_d * 255.0);
  const unsigned char b = boost::numeric_cast<unsigned char>(b_d * 255.0);
  ui.m_led->GetWidget()->GetLed()->SetColor(r,g,b);
  ui.m_label_color->setText(
    (
      std::string("Color: (")
    + boost::lexical_cast<std::string>(boost::numeric_cast<int>(r))
    + std::string(",")
    + boost::lexical_cast<std::string>(boost::numeric_cast<int>(g))
    + std::string(",")
    + boost::lexical_cast<std::string>(boost::numeric_cast<int>(b))
    + std::string(") (RGB)")
    ).c_str()
  );

}
//---------------------------------------------------------------------------
void ribi::WtTestLedMainDialog::OnDialIntensityChange()
{
  const double intensity = ui.m_dial_intensity->GetWidget()->GetDial()->GetPosition();
  ui.m_led->GetWidget()->GetLed()->SetIntensity(intensity);
  ui.m_label_intensity->setText(
    (
      std::string("Intensity: ")
    + boost::lexical_cast<std::string>(intensity * 100.0)
    + std::string("%")
    ).c_str()
  );
}
//---------------------------------------------------------------------------
void ribi::WtTestLedMainDialog::OnDialSizeChange()
{
  const double intensity = ui.m_dial_size->GetWidget()->GetDial()->GetPosition();
  const int size = boost::numeric_cast<int>(500.0 * intensity);
  ui.m_label_size->setText(
    (
      std::string("Size: ")
    + boost::lexical_cast<std::string>(size)
    + std::string(" x ")
    + boost::lexical_cast<std::string>(size)
    + std::string(" (width x height)")
    ).c_str()
  );
  ui.m_led->GetWidget()->SetGeometry(Rect(0,0,size,size));
}
//---------------------------------------------------------------------------
void ribi::WtTestLedMainDialog::ShowMain()
{
  setContentAlignment(Wt::AlignCenter);
  this->clear();
  {
    ui.m_led = new WtLedWidget(0.5,255,255,255);
    ui.m_led->GetWidget()->SetGeometry(Rect(0,0,100,100));
    this->addWidget(ui.m_led);
  }
  {
    ui.m_label_color = new Wt::WLabel("Color: ?,?,? (RGB)");
    this->addWidget(ui.m_label_color);
  }
  {
    ui.m_dial_color = new WtDialWidget;
    ui.m_dial_color->GetWidget()->SetGeometry(Rect(0,0,100,100));
    ui.m_dial_color->GetWidget()->GetDial()->m_signal_position_changed.connect(
      boost::bind(
        &ribi::WtTestLedMainDialog::OnDialColorChange,
        this));
    this->addWidget(ui.m_dial_color);
  }
  {
    ui.m_label_intensity = new Wt::WLabel("Intensity: ?%");
    this->addWidget(ui.m_label_intensity);
  }
  {
    ui.m_dial_intensity= new WtDialWidget;
    ui.m_dial_intensity->GetWidget()->SetGeometry(Rect(0,0,100,100));
    ui.m_dial_intensity->GetWidget()->GetDial()->m_signal_position_changed.connect(
      boost::bind(
        &ribi::WtTestLedMainDialog::OnDialIntensityChange,
        this));
    this->addWidget(ui.m_dial_intensity);
  }
  {
    ui.m_label_size = new Wt::WLabel("Size: ?x? (width x height)");
    this->addWidget(ui.m_label_size);
  }
  {
    ui.m_dial_size = new WtDialWidget;
    ui.m_dial_size->GetWidget()->SetGeometry(Rect(0,0,100,100));
    ui.m_dial_size->GetWidget()->GetDial()->m_signal_position_changed.connect(
      boost::bind(
        &ribi::WtTestLedMainDialog::OnDialSizeChange,
        this));
    this->addWidget(ui.m_dial_size);
  }
  ui.m_dial_color->GetWidget()->GetDial()->SetPosition(0.1);
  ui.m_dial_intensity->GetWidget()->GetDial()->SetPosition(0.9);
  ui.m_dial_size->GetWidget()->GetDial()->SetPosition(0.2);
}
//---------------------------------------------------------------------------
