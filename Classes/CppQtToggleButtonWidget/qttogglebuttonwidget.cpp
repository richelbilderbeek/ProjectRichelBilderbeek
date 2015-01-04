//---------------------------------------------------------------------------
/*
QtToggleButtonWidget, Qt widget for displaying the ToggleButtonWidget class
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
//From http://www.richelbilderbeek.nl/CppQtToggleButtonWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttogglebuttonwidget.h"

#include <cassert>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QBrush>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

#include "togglebutton.h"
#include "togglebuttonwidget.h"

#pragma GCC diagnostic pop

ribi::QtToggleButtonWidget::QtToggleButtonWidget(
  const bool toggled,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_signal_toggled{},
    m_widget(new ToggleButtonWidget(toggled,red,green,blue))
{
  assert(m_widget);
  m_widget->GetToggleButton()->m_signal_toggled.connect(
    boost::bind(
      &ribi::QtToggleButtonWidget::DoRepaint,
      this));
  m_widget->GetToggleButton()->m_signal_color_changed.connect(
    boost::bind(
      &ribi::QtToggleButtonWidget::DoRepaint,
      this));

  this->resize(200,100);
  this->update();
}

void ribi::QtToggleButtonWidget::DoRepaint()
{
  this->update();
  m_signal_toggled();
}

void ribi::QtToggleButtonWidget::DrawToggleButton(
  QPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const ToggleButton * const button)
{
  const int maxx = width - 1;
  const int maxy = height -1;
  painter.setBrush(QColor(
    button->GetRed(),
    button->GetGreen(),
    button->GetBlue()));
  //Draw base
  painter.drawArc(
    left + 0,
    top + (maxy * 1 / 3),
    maxx,
    maxy * 2 / 3,
    180 * 16,
    180 * 16);
  //Draw top
  painter.drawEllipse(
    left + 0,
    top + (button->IsPressed() ? (maxy * 1 / 3) - 2 : 0.0),
    maxx,
    maxy * 2 / 3);
  painter.drawLine(
    left,
    top + (button->IsPressed() ? (maxy * 2 / 3) - 2 : (maxy * 1 / 3)),
    left,
    top + (maxy * 2 / 3));
  painter.drawLine(
    left + maxx,
    top + (button->IsPressed() ? (maxy * 2 / 3) - 2 : (maxy * 1 / 3)),
    left + maxx,
    top + (maxy * 2 / 3));
}

void ribi::QtToggleButtonWidget::DrawToggleButton(
  QPainter& painter,
  const boost::shared_ptr<const ToggleButtonWidget> widget)
{
  DrawToggleButton(
    painter,
    widget->GetLeft(),
    widget->GetTop(),
    widget->GetWidth(),
    widget->GetHeight(),
    widget->GetToggleButton()
  );
}

std::string ribi::QtToggleButtonWidget::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::QtToggleButtonWidget::GetVersionHistory() noexcept
{
  return {
    "2011-06-16: version 1.0: initial version",
    "2014-03-28: Version 1.1: replaced custom Rect class by Boost.Geometry"
  };
}

void ribi::QtToggleButtonWidget::mousePressEvent(QMouseEvent * e)
{
  //m_widget signals its observers for a repaint
  m_widget->Click(e->x(),e->y());
}

void ribi::QtToggleButtonWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  DrawToggleButton(painter,m_widget);
}

void ribi::QtToggleButtonWidget::resizeEvent(QResizeEvent *)
{
  this->m_widget->SetGeometry(0,0,this->width(),this->height());
  repaint();
}

