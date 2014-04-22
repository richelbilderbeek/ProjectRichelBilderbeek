//---------------------------------------------------------------------------
/*
WtMysteryMachineWidget, Wt widget for displaying the MysteryMachine class
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
//From http://www.richelbilderbeek.nl/CppWtMysteryMachineWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "wtmysterymachinewidget.h"

#include <iostream>

#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBrush>
#include <Wt/WEvent>
#include <Wt/WPainter>
#include <Wt/WPen>

#include "dial.h"
#include "dialwidget.h"
#include "led.h"
#include "ledwidget.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
//#include "trace.h"
#include "mysterymachine.h"
#include "mysterymachinewidget.h"
#include "wtdialwidget.h"
#include "wtledwidget.h"
#include "wttogglebuttonwidget.h"
#pragma GCC diagnostic pop

ribi::WtMysteryMachineWidget::WtMysteryMachineWidget(
  const int width, const int height)
  : m_signal_changed{},
    m_widget(new MysteryMachineWidget(
      Rect(0,0,width-1,height-1)))

{
  assert(m_widget);

  m_widget->GetMachine()->GetDialBack()->GetDial()->m_signal_position_changed.connect(boost::bind(
    &ribi::WtMysteryMachineWidget::DoRepaint,this));
  m_widget->GetMachine()->GetDialFront()->GetDial()->m_signal_position_changed.connect(boost::bind(
    &ribi::WtMysteryMachineWidget::DoRepaint,this));
  m_widget->GetMachine()->GetToggleButton()->GetToggleButton()->m_signal_toggled.connect(boost::bind(
    &ribi::WtMysteryMachineWidget::DoRepaint,this));

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::WtMysteryMachineWidget::OnResize,
      this));

  this->clicked().connect(this,&ribi::WtMysteryMachineWidget::OnClicked);

  this->m_widget->SetGeometry(Rect(0,0,width,height));
}

void ribi::WtMysteryMachineWidget::DoRepaint()
{
  this->update();
}

void ribi::WtMysteryMachineWidget::OnResize()
{
  ribi::WtMysteryMachineWidget::resize(m_widget->GetGeometry().GetWidth(),m_widget->GetGeometry().GetHeight());
}

const std::string ribi::WtMysteryMachineWidget::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::WtMysteryMachineWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-06-16: version 1.0: initial version");
  v.push_back("2011-08-20: Version 1.1: added operator<<");
  return v;
}

void ribi::WtMysteryMachineWidget::OnClicked(const Wt::WMouseEvent& e)
{
  const int x = e.widget().x;
  const int y = e.widget().y;
  m_widget->Click(x,y);
}

void ribi::WtMysteryMachineWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  painter.drawRect(0,0,width().toPixels(),height().toPixels());
  WtDialWidget::DrawDial(painter,GetWidget()->GetMachine()->GetDialBack());
  WtDialWidget::DrawDial(painter,GetWidget()->GetMachine()->GetDialFront());
  WtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedBack1());
  WtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedBack2());
  WtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedBack3());
  WtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedFront1());
  WtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedFront2());
  WtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedFront3());
  WtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedTopBack());
  WtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedTopFront());
  WtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedTopMiddle());
  WtToggleButtonWidget::DrawToggleButton(painter,GetWidget()->GetMachine()->GetToggleButton());
}

void ribi::WtMysteryMachineWidget::resize(const Wt::WLength& width, const Wt::WLength& height)
{
  Wt::WPaintedWidget::resize(width,height);
}

std::ostream& ribi::operator<<(std::ostream& os, const WtMysteryMachineWidget& widget)
{
  os
    << "<WtMysteryMachineWidget>"
    << *widget.m_widget
    << "</WtMysteryMachineWidget>";
  return os;
}

