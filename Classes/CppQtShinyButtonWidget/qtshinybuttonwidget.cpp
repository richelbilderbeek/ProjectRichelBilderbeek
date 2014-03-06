//---------------------------------------------------------------------------
/*
QtShinyButtonWidget, Wt widget for displaying the ShinyButton class
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
//From http://www.richelbilderbeek.nl/CppQtShinyButtonWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtshinybuttonwidget.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QMouseEvent>
#include <QPainter>

#include "rainbow.h"
//#include "trace.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"

#pragma GCC diagnostic pop

ribi::QtShinyButtonWidget::QtShinyButtonWidget(QWidget *parent)
  : QWidget(parent),
    m_signal_changed{},
    m_widget(new ShinyButtonWidget(0.5,0.5))
{
  assert(m_widget);

  m_widget->GetShinyButton()->m_signal_color_changed.connect(boost::bind(
    &ribi::QtShinyButtonWidget::DoRepaint,this));
  m_widget->GetShinyButton()->m_signal_text_changed.connect(boost::bind(
    &ribi::QtShinyButtonWidget::DoRepaint,this));
  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::QtShinyButtonWidget::DoRepaint,
      this));

  resize(200,400);
}

ribi::QtShinyButtonWidget::QtShinyButtonWidget(
  const double color,
  const double gradient,
  const std::string& text,
  const Rect rect,
  QWidget *parent)
  : QWidget(parent),
    m_signal_changed{},
    m_widget(new ShinyButtonWidget(color,gradient,text,rect))
{
  assert(m_widget);

  m_widget->GetShinyButton()->m_signal_color_changed.connect(boost::bind(
    &ribi::QtShinyButtonWidget::DoRepaint,this));
  m_widget->GetShinyButton()->m_signal_text_changed.connect(boost::bind(
    &ribi::QtShinyButtonWidget::DoRepaint,this));
  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::QtShinyButtonWidget::DoRepaint,
      this));

  resize(rect.GetWidth(),rect.GetHeight());
}

void ribi::QtShinyButtonWidget::DrawShinyButton(
  QPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const ShinyButton * const button)
{
  const double from = button->GetColor() - (0.5 * button->GetGradient());
  const double to   = button->GetColor() + (0.5 * button->GetGradient());
  const double dc   = (to - from) / boost::numeric_cast<double>(width);

  const int right = left + width;
  double c = from;

  const QPen old_pen = painter.pen();
  QPen pen = painter.pen();

  for (int x=left; x!=right; ++x,c+=dc)
  {
    double r,g,b;
    Rainbow::GetRgb(c,r,g,b);
    pen.setColor(QColor(
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
  QRectF r(left,top,width,height);
  painter.drawText(r,Qt::AlignCenter | Qt::AlignVCenter,button->GetText().c_str());
}

void ribi::QtShinyButtonWidget::DrawShinyButton(
  QPainter& painter,
  const ShinyButtonWidget * const widget)
{
  DrawShinyButton(
    painter,
    widget->GetGeometry().GetX(),
    widget->GetGeometry().GetY(),
    widget->GetGeometry().GetWidth(),
    widget->GetGeometry().GetHeight(),
    widget->GetShinyButton());
}

void ribi::QtShinyButtonWidget::DoRepaint()
{
  this->repaint();
  m_signal_changed();
}

std::string ribi::QtShinyButtonWidget::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtShinyButtonWidget::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-07-04: version 1.0: initial version");
  v.push_back("2011-09-15: version 2.0: made QtShinyButtonWidget same as WtShinyButtonWidget");
  return v;
}

void ribi::QtShinyButtonWidget::mousePressEvent(QMouseEvent *)
{
  m_widget->Click();
}

void ribi::QtShinyButtonWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  DrawShinyButton(painter,m_widget.get());
}

void ribi::QtShinyButtonWidget::resizeEvent(QResizeEvent *)
{
  m_widget->SetGeometry(Rect(0,0,width(),height()));
}

