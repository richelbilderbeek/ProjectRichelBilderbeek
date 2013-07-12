//---------------------------------------------------------------------------
/*
QtRubiksClockWidget, Wt widget for displaying the RubiksClock class
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
//From http://www.richelbilderbeek.nl/CppQtRubiksClockWidget.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtrubiksclockwidget.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QMouseEvent>
#include <QPainter>

#include "dial.h"
#include "rubiksclock.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"
#include "rubiksclockwidget.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
//#include "trace.h"
#include "qtdialwidget.h"
#include "qttogglebuttonwidget.h"

QtRubiksClockWidget::QtRubiksClockWidget(
  const bool toggled,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_widget(new RubiksClockWidget(toggled,red,green,blue))
{
  assert(m_widget);

  m_widget->m_signal_widget_flipped.connect(
    boost::bind(
      &QtRubiksClockWidget::DoRepaint,
      this));

  m_widget->GetRubiksClock()->m_signal_clock_changed.connect(
    boost::bind(
      &QtRubiksClockWidget::DoRepaint,
      this));

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &QtRubiksClockWidget::OnResize,
      this));

  m_widget->SetGeometry(Rect(0,0,200,200));
}

void QtRubiksClockWidget::DoRepaint()
{
  this->update();
}

void QtRubiksClockWidget::DrawRubiksClock(
  QPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const RubiksClock * const clock,
  const bool front_side)
{
  //Draw main clock ring
  {
    QPen pen = painter.pen();
    pen.setColor(Qt::black);
    painter.setPen(pen);
  }
  {
    painter.setBrush(
      QBrush(
        QColor(
          front_side ? 127 : 96,
          front_side ? 127 : 96,
          196)));
  }
  painter.drawEllipse(
    static_cast<double>(left),
    static_cast<double>(top),
    static_cast<double>(width),
    static_cast<double>(height));



  //Draw the clocks and pegs
  {
    for (int y=0; y!=3; ++y)
    {
      for (int x=0; x!=3; ++x)
      {
        const boost::shared_ptr<RubiksClockDialWidget> w
          = (front_side ? clock->GetFrontTimes() : clock->GetBackTimes()).times[x][y];
        QtDialWidget::DrawDial(
          painter,
          w->GetGeometry().GetX(),
          w->GetGeometry().GetY(),
          w->GetGeometry().GetWidth(),
          w->GetGeometry().GetHeight(),
          w->GetRubiksClockDial()->GetDial());
      }
    }
    //Draw the pegs
    for (int y=0; y!=2; ++y)
    {
      for (int x=0; x!=2; ++x)
      {
        QtToggleButtonWidget::DrawToggleButton(
          painter,
          (front_side
            ? clock->GetFrontPegs()
            : clock->GetBackPegs()).pegs[x][y].get());
      }
    }
  }
}

void QtRubiksClockWidget::DrawRubiksClock(
  QPainter& painter,
  const RubiksClockWidget * const widget)
{
  DrawRubiksClock(
    painter,
    widget->GetGeometry().GetX(),
    widget->GetGeometry().GetY(),
    widget->GetGeometry().GetWidth(),
    widget->GetGeometry().GetHeight(),
    widget->GetRubiksClock(),
    widget->GetDisplayFront());
}

const std::string QtRubiksClockWidget::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QtRubiksClockWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-12-22: version 1.0: initial version");
  return v;
}

void QtRubiksClockWidget::mousePressEvent(QMouseEvent * e)
{
  const int x = e->x();
  const int y = e->y();

  const bool is_left_button = e->button() == Qt::LeftButton;
  m_widget->Click(x,y,is_left_button);
}

void QtRubiksClockWidget::OnResize()
{
  resize(m_widget->GetGeometry().GetWidth(),m_widget->GetGeometry().GetHeight());
}

void QtRubiksClockWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  DrawRubiksClock(painter,m_widget.get());
}

void QtRubiksClockWidget::resize(const int width, const int height)
{
  QWidget::resize(width,height);
}

