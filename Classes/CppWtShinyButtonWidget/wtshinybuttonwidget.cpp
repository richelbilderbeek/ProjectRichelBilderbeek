//---------------------------------------------------------------------------
/*
WtShinyButtonWidget, Wt widget for displaying the ShinyButton class
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
//From http://www.richelbilderbeek.nl/CppWtShinyButtonWidget.htm
//---------------------------------------------------------------------------
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBrush>
#include <Wt/WEvent>
#include <Wt/WPainter>
#include <Wt/WPen>

#include "geometry.h"
#include "rainbow.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "wtshinybuttonwidget.h"
#pragma GCC diagnostic pop

ribi::WtShinyButtonWidget::WtShinyButtonWidget(
  const double color,
  const double gradient,
  const std::string& text)
  : m_widget(new ShinyButtonWidget(color,gradient,text))
{
  assert(m_widget);
  this->setInline(true);

  m_widget->GetShinyButton()->m_signal_color_changed.connect(
    boost::bind(
      &ribi::WtShinyButtonWidget::DoRepaint,
      this));

  m_widget->GetShinyButton()->m_signal_text_changed.connect(
    boost::bind(
      &ribi::WtShinyButtonWidget::DoRepaint,
      this));

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::WtShinyButtonWidget::OnResize,
      this));

  this->clicked().connect(this,&ribi::WtShinyButtonWidget::OnClicked);
}

void ribi::WtShinyButtonWidget::DoRepaint()
{
  this->update();
}

void ribi::WtShinyButtonWidget::DrawShinyButton(
  Wt::WPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const ShinyButton * const button)
{
  const double from = button->GetColor() - (0.5 * button->GetGradient());
  const double to   = button->GetColor() + (0.5 * button->GetGradient());
  const double dc   = (to - from) / boost::numeric_cast<double>(width);

  const int right = left + width;
  double c = from;

  const Wt::WPen old_pen = painter.pen();
  Wt::WPen pen = painter.pen();

  for (int x=left; x!=right; ++x,c+=dc)
  {
    double r,g,b;
    Rainbow::GetRgb(c,r,g,b);
    pen.setColor(Wt::WColor(
      r * 255.0,
      g * 255.0,
      b * 255.0));
    painter.setPen(pen);
    painter.drawLine(
      x,
      top,
      x,
      top + height);
  }
  painter.setPen(old_pen);
  Wt::WRectF r(left,top,width,height);
  painter.drawText(r,Wt::AlignCenter | Wt::AlignMiddle,button->GetText().c_str());
}

void ribi::WtShinyButtonWidget::DrawShinyButton(
  Wt::WPainter& painter,
  const ShinyButtonWidget * const widget)
{
  DrawShinyButton(
    painter,
    Geometry().GetLeft(widget->GetGeometry()),
    Geometry().GetTop(widget->GetGeometry()),
    Geometry().GetWidth(widget->GetGeometry()),
    Geometry().GetHeight(widget->GetGeometry()),
    widget->GetShinyButton()
  );
}

const std::string ribi::WtShinyButtonWidget::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::WtShinyButtonWidget::GetVersionHistory()
{
  return {
    "2011-09-21: version 1.0: initial version",
    "2011-10-29: version 1.1: added OnClicked method"
  };
}

void ribi::WtShinyButtonWidget::OnClicked(const Wt::WMouseEvent&)
{
  m_widget->Click();
}

void ribi::WtShinyButtonWidget::OnResize()
{
  resize(
    Geometry().GetWidth(m_widget->GetGeometry()),
    Geometry().GetHeight(m_widget->GetGeometry())
  );
}

void ribi::WtShinyButtonWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  DrawShinyButton(painter,m_widget.get());
}

void ribi::WtShinyButtonWidget::resize(const Wt::WLength& width, const Wt::WLength& height)
{
  Wt::WPaintedWidget::resize(width,height);
}

