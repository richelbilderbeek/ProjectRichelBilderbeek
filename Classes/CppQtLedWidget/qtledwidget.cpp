//---------------------------------------------------------------------------
/*
QtLedWidget, Qt widget for displaying the Led class
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
//From http://www.richelbilderbeek.nl/CppQtLedWidget.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtledwidget.h"

#include <cassert>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include <QPainter>

#include "led.h"
//#include "trace.h"

QtLedWidget::QtLedWidget(
  QWidget *parent,
  const double intensity,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : QWidget(parent),
    m_widget(new LedWidget(intensity,red,green,blue))
{
  assert(m_widget);
  m_widget->GetLed()->m_signal_color_changed.connect(
    boost::bind(
      &QtLedWidget::repaint,
      this));

  m_widget->GetLed()->m_signal_intensity_changed.connect(
    boost::bind(
      &QtLedWidget::repaint,
      this));

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &QtLedWidget::OnResize,
      this));

  this->GetWidget()->SetGeometry(Rect(0,0,100,100));
  this->GetWidget()->GetLed()->SetColor(255,124,0);
  this->GetWidget()->GetLed()->SetIntensity(0.99);
}

///Draw a Led from a Led
void QtLedWidget::DrawLed(
    QPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const Led * const led)
{
  const int red   = boost::numeric_cast<int>(led->GetRed());
  const int green = boost::numeric_cast<int>(led->GetGreen());
  const int blue  = boost::numeric_cast<int>(led->GetBlue());
  const double intensity = led->GetIntensity();
  //Fraction red/green/blue
  const double fR = static_cast<double>(red  ) / 255.0;
  const double fG = static_cast<double>(green) / 255.0;
  const double fB = static_cast<double>(blue ) / 255.0;

  {
    //Draw circle and major surface
    const double maxBrightness = 0.66 * 255.0;
    const double minBrightness = 0.25 * maxBrightness;
    const int r = static_cast<int>(
      minBrightness + (fR * intensity * (maxBrightness - minBrightness) ) );
    const int g = static_cast<int>(
      minBrightness + (fG * intensity * (maxBrightness - minBrightness) ) );
    const int b = static_cast<int>(
      minBrightness + (fB * intensity * (maxBrightness - minBrightness) ) );
    assert( r >= 0 ); assert( r < 256);
    assert( g >= 0 ); assert( g < 256);
    assert( b >= 0 ); assert( b < 256);
    const int pen_width = 1 + (std::min(width,height) / 25);
    {
      QPen pen = painter.pen();
      pen.setWidth(pen_width);
      pen.setColor(QColor(0,0,0));
      painter.setPen(pen);
    }
    painter.setBrush(QBrush(QColor(r,g,b)));
    painter.drawEllipse(
      left + pen_width,
      top + pen_width,
      width  - (2 * pen_width),
      height - (2 * pen_width));
  }
  {
    //Draw topleft smaller lighter surface
    const double maxBrightness = 1.00 * 255.0;
    const double minBrightness = 0.25 * maxBrightness;
    const int r = static_cast<int>(
      minBrightness + (fR * intensity * (maxBrightness - minBrightness) ) );
    const int g = static_cast<int>(
      minBrightness + (fG * intensity * (maxBrightness - minBrightness) ) );
    const int b = static_cast<int>(
      minBrightness + (fB * intensity * (maxBrightness - minBrightness) ) );
    assert( r >= 0 ); assert( r < 256);
    assert( g >= 0 ); assert( g < 256);
    assert( b >= 0 ); assert( b < 256);
    const int x = left + (width  / 2) - (0.707 * static_cast<double>(width ) * 0.5);
    const int y = top  + (height / 2) - (0.707 * static_cast<double>(height) * 0.5);
    const int w = (0.707 * static_cast<double>(width ) * 0.5);
    const int h = (0.707 * static_cast<double>(height) * 0.5);
    {
      QPen pen = painter.pen();
      pen.setWidth(1);
      pen.setColor(QColor(r,g,b));
      painter.setPen(pen);
    }
    painter.setBrush(QBrush(QColor(r,g,b)));
    painter.drawEllipse(x,y,w,h);
  }
  {
    //Draw bottomright smaller lighter surface
    const double maxBrightness = 0.33 * 255.0;
    const double minBrightness = 0.25 * maxBrightness;
    const int r = static_cast<int>(
      minBrightness + (fR * intensity * (maxBrightness - minBrightness) ) );
    const int g = static_cast<int>(
      minBrightness + (fG * intensity * (maxBrightness - minBrightness) ) );
    const int b = static_cast<int>(
      minBrightness + (fB * intensity * (maxBrightness - minBrightness) ) );
    assert( r >= 0 ); assert( r < 256);
    assert( g >= 0 ); assert( g < 256);
    assert( b >= 0 ); assert( b < 256);
    const int x = left + (width  / 2) - 1;
    const int y = top  + (height / 2) - 1;
    const int w = (0.707 * static_cast<double>(width ) * 0.5);
    const int h = (0.707 * static_cast<double>(height) * 0.5);

    {
      QPen pen = painter.pen();
      pen.setWidth(1);
      pen.setColor(QColor(r,g,b));
      painter.setPen(pen);
    }
    painter.setBrush(QBrush(QColor(r,g,b)));
    painter.drawEllipse(x,y,w,h);
  }
}

///Draw a Led from a LedWidget
void QtLedWidget::DrawLed(
  QPainter& painter,
  const LedWidget * const widget)
{
  DrawLed(
    painter,
    widget->GetGeometry().GetX(),
    widget->GetGeometry().GetY(),
    widget->GetGeometry().GetWidth(),
    widget->GetGeometry().GetHeight(),
    widget->GetLed());
}

const std::string QtLedWidget::GetVersion()
{
  return "1.4";
}

const std::vector<std::string> QtLedWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-04-10: Version 1.0: initial version");
  v.push_back("2011-04-11: Version 1.1: added About information");
  v.push_back("2011-09-08: Version 1.2: removed redundant signals");
  v.push_back("2012-07-07: Version 1.3: added resizeEvent");
  v.push_back("2012-08-26: Version 1.4: fixed bug in resizeEvent");
  return v;
}

void QtLedWidget::OnResize()
{
  this->setGeometry(
    this->GetWidget()->GetGeometry().GetX(),
    this->GetWidget()->GetGeometry().GetY(),
    this->GetWidget()->GetGeometry().GetWidth(),
    this->GetWidget()->GetGeometry().GetHeight());
  this->repaint();
}

void QtLedWidget::paintEvent(QPaintEvent *)
{
  QPainter p(this);
  DrawLed(p,m_widget.get());
}

void QtLedWidget::resizeEvent(QResizeEvent *)
{
  m_widget->SetGeometry(Rect(0,0,width(),height()));
}

