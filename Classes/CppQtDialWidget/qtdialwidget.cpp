//---------------------------------------------------------------------------
/*
QtDialWidget, Qt class for displaying a DialWidget
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
//From http://www.richelbilderbeek.nl/CppQtDialWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtdialwidget.h"

#include <cassert>

#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QMouseEvent>
#include <QPainter>

#include "dial.h"
#pragma GCC diagnostic pop

ribi::QtDialWidget::QtDialWidget(QWidget *parent)
  : QWidget(parent),
    m_widget(new DialWidget)
{

  m_widget->GetDial()->m_signal_color_changed.connect(
    boost::bind(
      &ribi::QtDialWidget::OnDialChanged,
      this));

  m_widget->GetDial()->m_signal_position_changed.connect(
    boost::bind(
      &ribi::QtDialWidget::OnDialChanged,
      this));
}

void ribi::QtDialWidget::DrawDial(
  QPainter& painter,
  const boost::shared_ptr<const DialWidget> widget)
{
  DrawDial(
    painter,
    widget->GetLeft(),
    widget->GetTop(),
    widget->GetWidth(),
    widget->GetHeight(),
    widget->GetDial()
  );
}

void ribi::QtDialWidget::DrawDial(
  QPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const Dial * const dial)
{
  const QPen initial_pen = painter.pen();
  const double position = dial->GetPosition();
  const unsigned char red = dial->GetRed();
  const unsigned char green = dial->GetGreen();
  const unsigned char blue = dial->GetBlue();

  //Draw knob
  {
    QPen pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(QColor(0,0,0));
    painter.setPen(pen);
  }
  painter.setBrush(QColor(red,green,blue));
  painter.drawEllipse(left+1,top+1,width-2,height-2);

  //Draw pointer
  const int midx = width / 2;
  const int midy = height / 2;
  const double ray_x = static_cast<double>(midx);
  const double ray_y = static_cast<double>(midy);
  const double pi = boost::math::constants::pi<double>();
  const double angle = position * 2.0 * pi;
  const int pointerX
    = static_cast<int>( static_cast<double>(midx) + (std::sin(angle) * ray_x) );
  const int pointerY
    = static_cast<int>( static_cast<double>(midy) - (std::cos(angle) * ray_y) );

  {
    QPen pen = painter.pen();
    pen.setWidth(4);
    painter.setPen(pen);
  }
  painter.drawLine(left+midx,top+midy,left+pointerX,top+pointerY);
  painter.setPen(initial_pen);
}

std::string ribi::QtDialWidget::GetVersion() noexcept
{
  return "2.2";
}

std::vector<std::string> ribi::QtDialWidget::GetVersionHistory() noexcept
{
  return {
    "2011-04-11: Version 1.0: initial version",
    "2011-06-27: Version 1.1: fixed minor bug in displaying the dial its pointer",
    "2011-08-07: Version 2.0: conformized architure for MysteryMachine",
    "2011-08-31: Version 2.1: removed bloat, fixed bugs",
    "2014-03-28: Version 2.2: replaced custom Rect class by Boost.Geometry"
  };
}

void ribi::QtDialWidget::mousePressEvent(QMouseEvent * e)
{
  assert(e);
  m_widget->Click(e->x(),e->y());
}

void ribi::QtDialWidget::OnDialChanged()
{
  this->repaint();
}

void ribi::QtDialWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  DrawDial(painter,0,0,width(),height(),this->m_widget->GetDial());
}

void ribi::QtDialWidget::resizeEvent(QResizeEvent *)
{
  m_widget->SetGeometry(0,0,width(),height());
}
