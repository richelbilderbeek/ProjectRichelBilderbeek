//---------------------------------------------------------------------------
/*
WtShapeWidget, Wt class for displaying a ShapeWidget
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
//From http://www.richelbilderbeek.nl/CppWtShapeWidget.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <cmath>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WColor>
#include <Wt/WPainter>
#include <Wt/WPolygonArea>

#include "geometry.h"
#include "shape.h"
#include "shapewidget.h"
#include "wtshapewidget.h"
//#include "trace.h"
#pragma GCC diagnostic pop

ribi::WtShapeWidget::WtShapeWidget(
  boost::shared_ptr<ShapeWidget> widget)
  : m_widget(widget)
{
  assert(widget);
  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::WtShapeWidget::OnResize,
      this));

  this->OnResize();
}

///Create a deep copy of WtShapeWidget for use with Wt
ribi::WtShapeWidget * ribi::WtShapeWidget::Clone() const
{
  assert(m_widget);
  boost::shared_ptr<ShapeWidget> widget(m_widget->Clone());
  WtShapeWidget * wtwidget(new WtShapeWidget(widget));
  assert(*wtwidget == *this);
  return wtwidget;
}

void ribi::WtShapeWidget::DrawShape(
  Wt::WPainter& painter,
  const ShapeWidget * const widget)
{
  assert(widget);
  DrawShape(
    painter,
    Geometry().GetLeft(widget->GetGeometry()),
    Geometry().GetTop(widget->GetGeometry()),
    Geometry().GetWidth(widget->GetGeometry()),
    Geometry().GetHeight(widget->GetGeometry()),
    widget->GetShape()
  );
}

void ribi::WtShapeWidget::DrawShape(
  Wt::WPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const Shape * const shape)
{
  const unsigned char red = shape->GetRed();
  const unsigned char green = shape->GetGreen();
  const unsigned char blue = shape->GetBlue();
  painter.setBrush(Wt::WColor(red,green,blue));

  const int n_corners = shape->GetNumberOfCorners();

  if (n_corners == 0)
  {
    //Draw a circle
    painter.drawEllipse(left,top,width-1,height-1);
    return;
  }

  const double rotation = shape->GetRotation();
  const double midx = boost::numeric_cast<double>(width) / 2.0;
  const double midy = boost::numeric_cast<double>(height) / 2.0;

  if (n_corners == 1)
  {
    //Draw a line
    const int x1 = boost::numeric_cast<int>(
      midx - (std::cos(rotation) * midx));
    const int y1 = boost::numeric_cast<int>(
      midy + (std::sin(rotation) * midy));
    const int x2 = boost::numeric_cast<int>(
      midx - (std::cos(rotation + boost::math::constants::pi<double>()) * midx));
    const int y2 = boost::numeric_cast<int>(
      midy + (std::sin(rotation + boost::math::constants::pi<double>()) * midy));
    painter.drawLine(left+x1,top+y1,left+x2,top+y2);
    return;
  }

  const double d_angle = 2.0 * boost::math::constants::pi<double>() / boost::numeric_cast<double>(n_corners);

  std::vector<Wt::WPointF> polygon;

  for (int i=0; i!=n_corners; ++i)
  {
    const double angle
      = rotation + (boost::numeric_cast<double>(i) * d_angle);
    const int x = left + boost::numeric_cast<int>(
      midx - (std::cos(angle) * midx));
    const int y = top + boost::numeric_cast<int>(
      midy + (std::sin(angle) * midy));
    polygon.push_back(Wt::WPointF(x,y));
  }
  painter.drawPolygon(&(polygon[0]),n_corners);

}

std::string ribi::WtShapeWidget::GetVersion()
{
  return "2.0";
}

std::vector<std::string> ribi::WtShapeWidget::GetVersionHistory()
{
  return {
    "2011-07-15: Version 1.0: initial version",
    "2011-08-08: Version 2.0: conformized architecture to MysteryMachineWidget"
  };
}

void ribi::WtShapeWidget::OnResize()
{
  resize(
    Geometry().GetWidth(m_widget->GetGeometry()),
    Geometry().GetHeight(m_widget->GetGeometry())
  );
}

void ribi::WtShapeWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  DrawShape(
    painter,
    0,0,width().toPixels(),height().toPixels(),
    this->m_widget->GetShape()
  );
}

void ribi::WtShapeWidget::resize(const Wt::WLength& width, const Wt::WLength& height)
{
  Wt::WPaintedWidget::resize(width,height);
}

bool ribi::operator==(const WtShapeWidget& lhs, const WtShapeWidget& rhs)
{
  return *lhs.m_widget == *rhs.m_widget;
}

