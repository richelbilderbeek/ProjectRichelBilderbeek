//---------------------------------------------------------------------------
/*
WtClockWidget, Wt widget for displaying the Clock class
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
//From http://www.richelbilderbeek.nl/CppWtClockWidget.htm
//---------------------------------------------------------------------------
#include "wtrubiksclockwidget.h"

#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBrush>
#include <Wt/WEvent>
#include <Wt/WPainter>
#include <Wt/WPen>

#include "dial.h"
#include "geometry.h"
#include "rubiksclock.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"
#include "rubiksclocktimes.h"
#include "rubiksclockwidget.h"
#include "rubiksclockpegs.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
//#include "trace.h"
#include "wtdialwidget.h"
#include "wttogglebuttonwidget.h"
#pragma GCC diagnostic pop

ribi::ruco::WtClockWidget::WtClockWidget(
  const bool toggled,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_widget(new ClockWidget(toggled,red,green,blue))
{
  assert(m_widget);

  m_widget->m_signal_widget_flipped.connect(
    boost::bind(
      &ribi::ruco::WtClockWidget::DoRepaint,
      this));

  m_widget->GetRubiksClock()->m_signal_clock_changed.connect(
    boost::bind(
      &ribi::ruco::WtClockWidget::DoRepaint,
      this));

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::ruco::WtClockWidget::OnResize,
      this));

  this->clicked().connect(this,&ribi::ruco::WtClockWidget::OnClicked);

  m_widget->SetGeometry(0,0,200,200);
}

void ribi::ruco::WtClockWidget::DoRepaint()
{
  this->update();
}

void ribi::ruco::WtClockWidget::DrawClock(
  Wt::WPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const Clock * const clock,
  const bool front_side)
{
  //Draw main clock ring
  {
    Wt::WPen pen = painter.pen();
    pen.setColor(Wt::black);
    painter.setPen(pen);
  }
  {
    painter.setBrush(
      Wt::WBrush(
        Wt::WColor(
          front_side ? 127 : 96,
          front_side ? 127 : 96,
          196)));
  }
  painter.drawEllipse(
    static_cast<double>(left),
    static_cast<double>(top),
    static_cast<double>(width),
    static_cast<double>(height));



  //Draw the clocks and pegs
  {
    for (int y=0; y!=3; ++y)
    {
      for (int x=0; x!=3; ++x)
      {
        const boost::shared_ptr<ClockDialWidget> w
          = (front_side ? clock->GetFrontTimes() : clock->GetBackTimes())->times[x][y];
        WtDialWidget::DrawDial(
          painter,
          Geometry().GetLeft(w->GetGeometry()),
          Geometry().GetTop(w->GetGeometry()),
          Geometry().GetWidth(w->GetGeometry()),
          Geometry().GetHeight(w->GetGeometry()),
          w->GetRubiksClockDial()->GetDial()
        );
      }
    }
    //Draw the pegs
    for (int y=0; y!=2; ++y)
    {
      for (int x=0; x!=2; ++x)
      {
        WtToggleButtonWidget::DrawToggleButton(
          painter,
          (front_side
            ? clock->GetFrontPegs()
            : clock->GetBackPegs())->m_pegs[x][y].get());
      }
    }
  }
}

void ribi::ruco::WtClockWidget::DrawClock(
  Wt::WPainter& painter,
  const ClockWidget * const widget)
{
  DrawClock(
    painter,
    Geometry().GetLeft(widget->GetGeometry()),
    Geometry().GetTop(widget->GetGeometry()),
    Geometry().GetWidth(widget->GetGeometry()),
    Geometry().GetHeight(widget->GetGeometry()),
    widget->GetRubiksClock(),
    widget->GetDisplayFront()
  );
}

std::string ribi::ruco::WtClockWidget::GetVersion()
{
  return "1.2";
}

std::vector<std::string> ribi::ruco::WtClockWidget::GetVersionHistory()
{
  return {
    "2011-09-01: version 1.0: initial version",
    "2011-09-15: version 1.1: allow displaying both sides",
    "2014-02-08: version 1.2: put in namespace ruco"
  };
}

void ribi::ruco::WtClockWidget::OnClicked(const Wt::WMouseEvent& e)
{
  const int x = e.widget().x;
  const int y = e.widget().y;

  const bool is_left_button = e.button() == Wt::WMouseEvent::LeftButton
    || e.wheelDelta() > 0;
  m_widget->Click(x,y,is_left_button);
}

void ribi::ruco::WtClockWidget::OnResize()
{
  resize(
    Geometry().GetWidth(m_widget->GetGeometry()),
    Geometry().GetHeight(m_widget->GetGeometry())
  );
}

void ribi::ruco::WtClockWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  DrawClock(painter,m_widget.get());
}

void ribi::ruco::WtClockWidget::resize(const Wt::WLength& width, const Wt::WLength& height)
{
  Wt::WPaintedWidget::resize(width,height);
}

