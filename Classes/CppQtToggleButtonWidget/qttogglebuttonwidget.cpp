//---------------------------------------------------------------------------
/*
QtToggleButtonWidget, Qt widget for displaying the ToggleButtonWidget class
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
//From http://www.richelbilderbeek.nl/CppQtToggleButtonWidget.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttogglebuttonwidget.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <QBrush>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
//---------------------------------------------------------------------------
#include "togglebutton.h"
#include "togglebuttonwidget.h"
//---------------------------------------------------------------------------
QtToggleButtonWidget::QtToggleButtonWidget(
  const bool toggled,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_widget(new ToggleButtonWidget(toggled,red,green,blue))
{
  assert(m_widget);
  m_widget->GetToggleButton()->m_signal_toggled.connect(
    boost::bind(
      &QtToggleButtonWidget::DoRepaint,
      this));
  m_widget->GetToggleButton()->m_signal_color_changed.connect(
    boost::bind(
      &QtToggleButtonWidget::DoRepaint,
      this));

  this->resize(200,100);
  this->update();
}
//---------------------------------------------------------------------------
void QtToggleButtonWidget::DoRepaint()
{
  this->update();
  m_signal_toggled();
}
//---------------------------------------------------------------------------
void QtToggleButtonWidget::DrawToggleButton(
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
//---------------------------------------------------------------------------
void QtToggleButtonWidget::DrawToggleButton(
  QPainter& painter,
  const ToggleButtonWidget * const widget)
{
  DrawToggleButton(
    painter,
    widget->GetGeometry().GetX(),
    widget->GetGeometry().GetY(),
    widget->GetGeometry().GetWidth(),
    widget->GetGeometry().GetHeight(),
    widget->GetToggleButton());
}
//---------------------------------------------------------------------------
const std::string QtToggleButtonWidget::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> QtToggleButtonWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-06-16: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void QtToggleButtonWidget::mousePressEvent(QMouseEvent * e)
{
  //m_widget its observers for a repaint
  m_widget->Click(e->x(),e->y());
}
//---------------------------------------------------------------------------
void QtToggleButtonWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  DrawToggleButton(painter,m_widget.get());
}
//---------------------------------------------------------------------------
void QtToggleButtonWidget::resizeEvent(QResizeEvent *)
{
  this->m_widget->SetGeometry(Rect(0,0,this->width(),this->height()));
  repaint();
}
//---------------------------------------------------------------------------
