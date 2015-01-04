//---------------------------------------------------------------------------
/*
QtMysteryMachineWidget, Wt widget for displaying the MysteryMachine class
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
//From http://www.richelbilderbeek.nl/CppQtMysteryMachineWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtmysterymachinewidget.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QMouseEvent>
#include <QPainter>

#include "dial.h"
#include "dialwidget.h"
#include "led.h"
#include "ledwidget.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
//#include "trace.h"
#include "mysterymachine.h"
#include "mysterymachinewidget.h"
#include "qtdialwidget.h"
#include "qtledwidget.h"
#include "qttogglebuttonwidget.h"

#pragma GCC diagnostic pop

ribi::QtMysteryMachineWidget::QtMysteryMachineWidget(QWidget *parent)
  : QWidget(parent),
    m_signal_changed{},
    m_widget(new MysteryMachineWidget(
    Widget::CreateRect(0,0,200,400)))
{
  assert(m_widget);

  m_widget->GetMachine()->GetDialBack()->GetDial()->m_signal_position_changed.connect(boost::bind(
    &ribi::QtMysteryMachineWidget::DoRepaint,this));
  m_widget->GetMachine()->GetDialFront()->GetDial()->m_signal_position_changed.connect(boost::bind(
    &ribi::QtMysteryMachineWidget::DoRepaint,this));
  m_widget->GetMachine()->GetToggleButton()->GetToggleButton()->m_signal_toggled.connect(boost::bind(
    &ribi::QtMysteryMachineWidget::DoRepaint,this));
  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::QtMysteryMachineWidget::DoRepaint,
      this));

  resize(200,400);
}

ribi::QtMysteryMachineWidget::QtMysteryMachineWidget(
  const int width, const int height,
  QWidget *parent)
  : QWidget(parent),
    m_signal_changed{},
    m_widget{new MysteryMachineWidget(
      Widget::CreateRect(0,0,width,height))
    }
{
  assert(m_widget);

  m_widget->GetMachine()->GetDialBack()->GetDial()->m_signal_position_changed.connect(boost::bind(
    &ribi::QtMysteryMachineWidget::DoRepaint,this));
  m_widget->GetMachine()->GetDialFront()->GetDial()->m_signal_position_changed.connect(boost::bind(
    &ribi::QtMysteryMachineWidget::DoRepaint,this));
  m_widget->GetMachine()->GetToggleButton()->GetToggleButton()->m_signal_toggled.connect(boost::bind(
    &ribi::QtMysteryMachineWidget::DoRepaint,this));
  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::QtMysteryMachineWidget::DoRepaint,
      this));

  resize(width,height);
}

void ribi::QtMysteryMachineWidget::DoRepaint()
{
  this->repaint();
}

std::string ribi::QtMysteryMachineWidget::GetVersion() noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::QtMysteryMachineWidget::GetVersionHistory() noexcept
{
  return {
    "2011-07-04: version 1.0: initial version",
    "2011-09-15: version 2.0: made QtMysteryMachineWidget same as WtMysteryMachineWidget",
    "2014-03-28: version 2.1: replaced Rect by Boost.Geometry its box class"
  };
}

void ribi::QtMysteryMachineWidget::mousePressEvent(QMouseEvent * e)
{
  m_widget->Click(e->x(),e->y());
  this->m_signal_changed();
}

void ribi::QtMysteryMachineWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  QtDialWidget::DrawDial(painter,GetWidget()->GetMachine()->GetDialBack());
  QtDialWidget::DrawDial(painter,GetWidget()->GetMachine()->GetDialFront());
  QtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedBack1());
  QtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedBack2());
  QtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedBack3());
  QtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedFront1());
  QtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedFront2());
  QtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedFront3());
  QtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedTopBack());
  QtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedTopFront());
  QtLedWidget::DrawLed(painter,GetWidget()->GetMachine()->GetLedTopMiddle());
  QtToggleButtonWidget::DrawToggleButton(painter,GetWidget()->GetMachine()->GetToggleButton());
}

void ribi::QtMysteryMachineWidget::resizeEvent(QResizeEvent *)
{
  m_widget->SetGeometry(0,0,width(),height());
}

