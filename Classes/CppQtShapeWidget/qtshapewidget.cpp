//---------------------------------------------------------------------------
/*
QtShapeWidget, Qt class for displaying a ShapeWidget
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
//From http://www.richelbilderbeek.nl/CppQtShapeWidget.htm
//---------------------------------------------------------------------------


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtshapewidget.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QMouseEvent>
#include <QPainter>
#include <QPolygon>

#include "shape.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::QtShapeWidget::QtShapeWidget(QWidget *parent)
  : QWidget(parent),
    m_widget(new ShapeWidget(0,0.0))
{
  //m_widget->m_signal_position_changed.connect(
  //  boost::bind(
  //    &ribi::QtShapeWidget::repaint,
  //    this));
}

ribi::QtShapeWidget::QtShapeWidget(
  boost::shared_ptr<ShapeWidget> widget,
  QWidget *parent)
  : QWidget(parent),
    m_widget(widget)
{
  //m_widget->m_signal_position_changed.connect(
  //  boost::bind(
  //    &ribi::QtShapeWidget::repaint,
  //    this));
}

void ribi::QtShapeWidget::DrawShape(
  QPainter& painter,
  const ShapeWidget * const widget)
{
  DrawShape(
    painter,
    widget->GetGeometry().GetX(),
    widget->GetGeometry().GetY(),
    widget->GetGeometry().GetWidth(),
    widget->GetGeometry().GetHeight(),
    widget->GetShape());
}

void ribi::QtShapeWidget::DrawShape(
  QPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const Shape * const shape)
{
  const double pi = boost::math::constants::pi<double>();

  const unsigned char red = shape->GetRed();
  const unsigned char green = shape->GetGreen();
  const unsigned char blue = shape->GetBlue();
  painter.setBrush(QColor(red,green,blue));

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
      midx - (std::cos(rotation + pi) * midx));
    const int y2 = boost::numeric_cast<int>(
      midy + (std::sin(rotation + pi) * midy));
    painter.drawLine(x1,y1,x2,y2);
    return;
  }

  const double d_angle = 2.0 * pi / boost::numeric_cast<double>(n_corners);

  QPolygon polygon;

  for (int i=0; i!=n_corners; ++i)
  {
    const double angle
      = rotation + (boost::numeric_cast<double>(i) * d_angle);
    const int x = boost::numeric_cast<int>(
      midx - (std::cos(angle) * midx));
    const int y = boost::numeric_cast<int>(
      midy + (std::sin(angle) * midy));
    polygon.append(QPoint(x,y));
  }
  painter.drawConvexPolygon(polygon);
}

const std::string ribi::QtShapeWidget::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> ribi::QtShapeWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-07-13: Version 1.0: initial version");
  v.push_back("2011-08-08: Version 2.0: conformized architecture to MysteryMachineWidget");
  return v;
}

void ribi::QtShapeWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  DrawShape(
    painter,
    0,0,width(),height(),
    this->m_widget->GetShape());
}

