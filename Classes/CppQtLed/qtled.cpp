//---------------------------------------------------------------------------
/*
QtLed, Qt widget for displaying the Led class
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtLed.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtled.h"

#include <cassert>
//#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

//#include <QResizeEvent>
#include <QPainter>

#include "led.h"
//#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtLed::QtLed(
  const double intensity,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue,
  QWidget *parent
)
  : QWidget(parent),
    m_led(new Led(intensity,red,green,blue))
{
  assert(m_led);
  m_led->m_signal_color_changed.connect(
    boost::bind(
      &ribi::QtLed::repaint,
      this));

  m_led->m_signal_intensity_changed.connect(
    boost::bind(
      &ribi::QtLed::repaint,
      this));

  GetLed()->SetColor(red,green,blue);
  GetLed()->SetIntensity(intensity);
}

///Draw a Led from a Led
void ribi::QtLed::DrawLed(
  QPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const Led& led
) noexcept
{
  assert(width  > 0);
  assert(height > 0);
  const int red   = boost::numeric_cast<int>(led.GetRed());
  const int green = boost::numeric_cast<int>(led.GetGreen());
  const int blue  = boost::numeric_cast<int>(led.GetBlue());
  const double intensity = led.GetIntensity();
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
    assert(pen_width > 0);
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
      width  - (4 * pen_width),
      height - (4 * pen_width)
    );
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
    //Draw bottomright smaller darker surface
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

std::string ribi::QtLed::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtLed::GetVersionHistory() noexcept
{
  return {
    "2014-06-20: Version 1.0: initial version"
  };
}

void ribi::QtLed::paintEvent(QPaintEvent *)
{
  QPainter p(this);
  DrawLed(
    p,
    this->geometry().left(),
    this->geometry().top(),
    this->geometry().width(),
    this->geometry().height(),
    *m_led
  );
}
