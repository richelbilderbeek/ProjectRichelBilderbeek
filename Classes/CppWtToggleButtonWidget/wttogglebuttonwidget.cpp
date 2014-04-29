//---------------------------------------------------------------------------
/*
WtToggleButtonWidget, Wt widget for displaying the ToggleButton class
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
//From http://www.richelbilderbeek.nl/CppWtToggleButtonWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "wttogglebuttonwidget.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBrush>
#include <Wt/WEvent>
#include <Wt/WPainter>
#include <Wt/WPen>

#include "geometry.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#pragma GCC diagnostic pop

ribi::WtToggleButtonWidget::WtToggleButtonWidget(
  const bool toggled,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_widget(new ToggleButtonWidget(toggled,red,green,blue))
{
  assert(m_widget);

  m_widget->GetToggleButton()->m_signal_color_changed.connect(
    boost::bind(
      &ribi::WtToggleButtonWidget::DoRepaint,
      this));

  m_widget->GetToggleButton()->m_signal_toggled.connect(
    boost::bind(
      &ribi::WtToggleButtonWidget::DoRepaint,
      this));

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::WtToggleButtonWidget::OnResize,
      this));

  this->clicked().connect(this,&ribi::WtToggleButtonWidget::OnClicked);
}

void ribi::WtToggleButtonWidget::DoRepaint()
{
  this->update();
}

void ribi::WtToggleButtonWidget::DrawToggleButton(
  Wt::WPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const ToggleButton * const button)
{
  {
    Wt::WPen pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(Wt::WColor(0,0,0));
    painter.setPen(pen);
  }
  painter.setBrush(Wt::WColor(
    button->GetRed(),
    button->GetGreen(),
    button->GetBlue()));
  //Draw base
  painter.drawArc(
    left + 0,
    top + (height * 1 / 3),
    width,
    height * 2 / 3,
    180 * 16,
    180 * 16);
  //Draw top
  painter.drawEllipse(
    left + 0,
    top + (button->IsPressed() ? (height * 1 / 3) - 2 : 0.0),
    width,
    height * 2 / 3);
  painter.drawLine(
    left + 1,
    top + (button->IsPressed() ? (height * 2 / 3) - 2 : (height * 1 / 3)),
    left + 1,
    top + (height * 2 / 3));
  painter.drawLine(
    left + (width - 1),
    top + (button->IsPressed() ? (height * 2 / 3) - 2 : (height * 1 / 3)),
    left + width - 1,
    top + (height * 2 / 3));
}

void ribi::WtToggleButtonWidget::DrawToggleButton(
  Wt::WPainter& painter,
  const ToggleButtonWidget * const widget)
{
  DrawToggleButton(
    painter,
    Geometry().GetLeft(widget->GetGeometry()),
    Geometry().GetTop(widget->GetGeometry()),
    Geometry().GetWidth(widget->GetGeometry()),
    Geometry().GetHeight(widget->GetGeometry()),
    widget->GetToggleButton()
  );
}

std::string ribi::WtToggleButtonWidget::GetVersion()
{
  return "1.1";
}

std::vector<std::string> ribi::WtToggleButtonWidget::GetVersionHistory()
{
  return {
    "2011-06-16: version 1.0: initial version",
    "2011-08-31: Version 1.1: added setting the color of a ToggleButton"
  };
}

void ribi::WtToggleButtonWidget::OnClicked(const Wt::WMouseEvent&)
{
  m_widget->GetToggleButton()->Toggle();
}

void ribi::WtToggleButtonWidget::OnResize()
{
  resize(
    Geometry().GetWidth(m_widget->GetGeometry()),
    Geometry().GetHeight(m_widget->GetGeometry())
  );
}

void ribi::WtToggleButtonWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  DrawToggleButton(painter,m_widget.get());
}

void ribi::WtToggleButtonWidget::resize(const Wt::WLength& width, const Wt::WLength& height)
{
  Wt::WPaintedWidget::resize(width,height);
}

