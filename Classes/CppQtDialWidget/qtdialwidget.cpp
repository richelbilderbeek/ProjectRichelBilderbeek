//---------------------------------------------------------------------------
/*
QtDialWidget, Qt class for displaying a DialWidget
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
//From http://www.richelbilderbeek.nl/CppQtDialWidget.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtdialwidget.h"

#include <cassert>
#include <cmath>

//Terrible #define, but my crosscompiler cannot find the definition of M_PI in cmath.h :-(
#ifndef M_PI
# define M_PI		3.14159265358979323846	/* pi */
#endif
//---------------------------------------------------------------------------
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <QMouseEvent>
#include <QPainter>
//---------------------------------------------------------------------------
#include "dial.h"
//---------------------------------------------------------------------------
QtDialWidget::QtDialWidget(QWidget *parent)
  : QWidget(parent),
    m_widget(new DialWidget)
{

  m_widget->GetDial()->m_signal_color_changed.connect(
    boost::bind(
      &QtDialWidget::OnDialChanged,
      this));

  m_widget->GetDial()->m_signal_position_changed.connect(
    boost::bind(
      &QtDialWidget::OnDialChanged,
      this));
}
//---------------------------------------------------------------------------
void QtDialWidget::DrawDial(
  QPainter& painter,
  const DialWidget * const widget)
{
  DrawDial(
    painter,
    widget->GetGeometry().GetX(),
    widget->GetGeometry().GetY(),
    widget->GetGeometry().GetWidth(),
    widget->GetGeometry().GetHeight(),
    widget->GetDial());
}
//---------------------------------------------------------------------------
void QtDialWidget::DrawDial(
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
  const double angle = position * 2.0 * M_PI;
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
//---------------------------------------------------------------------------
const std::string QtDialWidget::GetVersion()
{
  return "2.1";
}
//---------------------------------------------------------------------------
const std::vector<std::string> QtDialWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-04-11: Version 1.0: initial version");
  v.push_back("2011-06-27: Version 1.1: fixed minor bug in displaying the dial its pointer");
  v.push_back("2011-08-07: Version 2.0: conformized architure for MysteryMachine");
  v.push_back("2011-08-31: Version 2.1: removed bloat, fixed bugs");
  return v;
}
//---------------------------------------------------------------------------
void QtDialWidget::mousePressEvent(QMouseEvent * e)
{
  assert(e);
  m_widget->Click(e->x(),e->y());
}
//---------------------------------------------------------------------------
void QtDialWidget::OnDialChanged()
{
  this->repaint();
}
//---------------------------------------------------------------------------
void QtDialWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  DrawDial(painter,0,0,width(),height(),this->m_widget->GetDial());
}
//---------------------------------------------------------------------------
void QtDialWidget::resizeEvent(QResizeEvent *)
{
  m_widget->SetGeometry(Rect(0,0,width(),height()));
}
//---------------------------------------------------------------------------
