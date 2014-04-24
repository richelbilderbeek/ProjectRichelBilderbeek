//---------------------------------------------------------------------------
/*
WtDialWidget, Wt widget for displaying the Dial class
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
//From http://www.richelbilderbeek.nl/CppWtDialWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "wtdialwidget.h"

#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBrush>
#include <Wt/WEvent>
#include <Wt/WPainter>
#include <Wt/WPen>

#include "dial.h"
#include "dialwidget.h"
#include "geometry.h"
#pragma GCC diagnostic pop

ribi::WtDialWidget::WtDialWidget(
  const double intensity,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_widget(new DialWidget(intensity,red,green,blue))
{
  assert(m_widget);

  m_widget->GetDial()->m_signal_color_changed.connect(
    boost::bind(
      &ribi::WtDialWidget::DoRepaint,
      this));

  m_widget->GetDial()->m_signal_position_changed.connect(
    boost::bind(
      &ribi::WtDialWidget::DoRepaint,
      this));

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::WtDialWidget::OnResize,
      this));

  this->clicked().connect(this,&ribi::WtDialWidget::OnClicked);

  m_widget->SetGeometry(0,0,32,32);
}

void ribi::WtDialWidget::DoRepaint()
{
  this->update();
}

void ribi::WtDialWidget::DrawDial(
  Wt::WPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const Dial * const dial)
{
  const double position = dial->GetPosition();

  //Draw knob
  {
    Wt::WPen pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(Wt::WColor(0,0,0));
    painter.setPen(pen);
  }

  painter.setBrush(Wt::WColor(
    dial->GetRed(),
    dial->GetGreen(),
    dial->GetBlue()));

  painter.drawEllipse(left+1,top+1,width-2,height-2);

  //Draw pointer
  const int midx = width / 2;
  const int midy = height / 2;
  const double ray = static_cast<double>(std::min( midx, midy ));
  const double two_pi = boost::math::constants::two_pi<double>();
  const double angle = position * two_pi;
  const int pointerX
    = static_cast<int>( static_cast<double>(midx) + (std::sin(angle) * ray) );
  const int pointerY
    = static_cast<int>( static_cast<double>(midy) - (std::cos(angle) * ray) );

  {
    Wt::WPen pen = painter.pen();
    pen.setWidth(4);
    painter.setPen(pen);
  }
  painter.drawLine(left+midx,top+midy,left+pointerX,top+pointerY);
}

void ribi::WtDialWidget::DrawDial(
  Wt::WPainter& painter,
  const DialWidget * const widget)
{
  DrawDial(
    painter,
    Geometry().GetLeft(widget->GetGeometry()),
    Geometry().GetTop(widget->GetGeometry()),
    Geometry().GetWidth(widget->GetGeometry()),
    Geometry().GetHeight(widget->GetGeometry()),
    widget->GetDial());
}

const std::string ribi::WtDialWidget::GetVersion()
{
  return "3.1";
}

const std::vector<std::string> ribi::WtDialWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-04-10: version 1.0: initial version");
  v.push_back("2011-04-11: version 1.1: fixed #include guard, fixed initial date, made default dial white");
  v.push_back("2011-07-03: version 2.0: moved Dial its user interface logic to new class DialWidget");
  v.push_back("2011-08-07: Version 3.0: conformized architure for MysteryMachine");
  v.push_back("2011-08-31: Version 3.1: allow changing the dial its color");
  return v;
}

void ribi::WtDialWidget::OnClicked(const Wt::WMouseEvent& e)
{
  m_widget->Click(e.widget().x,e.widget().y);
}

void ribi::WtDialWidget::OnResize()
{
  resize(
    Geometry().GetWidth(m_widget->GetGeometry()),
    Geometry().GetHeight(m_widget->GetGeometry())
  );
}

void ribi::WtDialWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  this->DrawDial(painter,m_widget.get());
}

void ribi::WtDialWidget::resize(const Wt::WLength& width, const Wt::WLength& height)
{
  Wt::WPaintedWidget::resize(width,height);
}

