//---------------------------------------------------------------------------
/*
WtLedWidget, Wt widget for displaying the Led class
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
//From http://www.richelbilderbeek.nl/CppWtLedWidget.htm
//---------------------------------------------------------------------------
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WPainter>
#include <Wt/WPen>
#include <Wt/WBrush>
//---------------------------------------------------------------------------
#include "rectangle.h"
#include "led.h"
#include "ledwidget.h"
#include "wtledwidget.h"
//---------------------------------------------------------------------------
WtLedWidget::WtLedWidget(
  const double intensity,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_widget(new LedWidget(0,0,99,99,intensity,red,green,blue))
{
  assert(m_widget);
  m_widget->GetLed()->m_signal_color_changed.connect(
    boost::bind(
      &WtLedWidget::DoRepaint,
      this));

  m_widget->GetLed()->m_signal_intensity_changed.connect(
    boost::bind(
      &WtLedWidget::DoRepaint,
      this));

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &WtLedWidget::OnResize,
      this));

  m_widget->SetGeometry(Rect(0,0,100,100));
  m_widget->GetLed()->SetColor(254,254,254);
  m_widget->GetLed()->SetIntensity(0.98);
}
//---------------------------------------------------------------------------
void WtLedWidget::DoRepaint()
{
  this->update();
}
//---------------------------------------------------------------------------
void WtLedWidget::DrawLed(
  Wt::WPainter& painter,
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
      Wt::WPen pen = painter.pen();
      pen.setWidth(pen_width);
      pen.setColor(Wt::WColor(0,0,0));
      painter.setPen(pen);
    }
    painter.setBrush(Wt::WBrush(Wt::WColor(r,g,b)));
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
    const int x = (width  / 2) - (0.707 * static_cast<double>(width ) * 0.5);
    const int y = (height / 2) - (0.707 * static_cast<double>(height) * 0.5);
    const int w = (0.707 * static_cast<double>(width ) * 0.5);
    const int h = (0.707 * static_cast<double>(height) * 0.5);
    {
      Wt::WPen pen = painter.pen();
      pen.setWidth(1);
      pen.setColor(Wt::WColor(r,g,b));
      painter.setPen(pen);
    }
    painter.setBrush(Wt::WBrush(Wt::WColor(r,g,b)));
    painter.drawEllipse(left + x,top + y,w,h);
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
    const int x = (width  / 2) - 1;
    const int y = (height / 2) - 1;
    const int w = (0.707 * static_cast<double>(width ) * 0.5);
    const int h = (0.707 * static_cast<double>(height) * 0.5);

    {
      Wt::WPen pen = painter.pen();
      pen.setWidth(1);
      pen.setColor(Wt::WColor(r,g,b));
      painter.setPen(pen);
    }
    painter.setBrush(Wt::WBrush(Wt::WColor(r,g,b)));
    painter.drawEllipse(left + x,top + y,w,h);
  }

}
//---------------------------------------------------------------------------
void WtLedWidget::DrawLed(
  Wt::WPainter& painter,
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
//---------------------------------------------------------------------------
const std::string WtLedWidget::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtLedWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-01-06: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void WtLedWidget::OnResize()
{
  resize(m_widget->GetGeometry().GetWidth(),m_widget->GetGeometry().GetHeight());
}
//---------------------------------------------------------------------------
void WtLedWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  DrawLed(painter,m_widget.get());
}
//---------------------------------------------------------------------------
void WtLedWidget::resize(const Wt::WLength& width, const Wt::WLength& height)
{
  Wt::WPaintedWidget::resize(width,height);
}
//---------------------------------------------------------------------------
