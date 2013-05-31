//---------------------------------------------------------------------------
/*
WtToggleButtonWidget, Wt widget for displaying the ToggleButton class
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
//From http://www.richelbilderbeek.nl/CppWtToggleButtonWidget.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "wttogglebuttonwidget.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBrush>
#include <Wt/WEvent>
#include <Wt/WPainter>
#include <Wt/WPen>
//---------------------------------------------------------------------------
#include "togglebutton.h"
#include "togglebuttonwidget.h"
//---------------------------------------------------------------------------
WtToggleButtonWidget::WtToggleButtonWidget(
  const bool toggled,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_widget(new ToggleButtonWidget(toggled,red,green,blue))
{
  assert(m_widget);

  m_widget->GetToggleButton()->m_signal_color_changed.connect(
    boost::bind(
      &WtToggleButtonWidget::DoRepaint,
      this));

  m_widget->GetToggleButton()->m_signal_toggled.connect(
    boost::bind(
      &WtToggleButtonWidget::DoRepaint,
      this));

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &WtToggleButtonWidget::OnResize,
      this));

  this->clicked().connect(this,&WtToggleButtonWidget::OnClicked);
}
//---------------------------------------------------------------------------
void WtToggleButtonWidget::DoRepaint()
{
  this->update();
}
//---------------------------------------------------------------------------
void WtToggleButtonWidget::DrawToggleButton(
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
//---------------------------------------------------------------------------
void WtToggleButtonWidget::DrawToggleButton(
  Wt::WPainter& painter,
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
const std::string WtToggleButtonWidget::GetVersion()
{
  return "1.1";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtToggleButtonWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-06-16: version 1.0: initial version");
  v.push_back("2011-08-31: Version 1.1: added setting the color of a ToggleButton");
  return v;
}
//---------------------------------------------------------------------------
void WtToggleButtonWidget::OnClicked(const Wt::WMouseEvent&)
{
  m_widget->GetToggleButton()->Toggle();
}
//---------------------------------------------------------------------------
void WtToggleButtonWidget::OnResize()
{
  resize(m_widget->GetGeometry().GetWidth(),m_widget->GetGeometry().GetHeight());
}
//---------------------------------------------------------------------------
void WtToggleButtonWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  DrawToggleButton(painter,m_widget.get());
}
//---------------------------------------------------------------------------
void WtToggleButtonWidget::resize(const Wt::WLength& width, const Wt::WLength& height)
{
  Wt::WPaintedWidget::resize(width,height);
}
//---------------------------------------------------------------------------
