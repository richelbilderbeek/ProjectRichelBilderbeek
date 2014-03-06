//---------------------------------------------------------------------------
/*
QtRubiksClockWidget, Wt widget for displaying the RubiksClock class
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
//From http://www.richelbilderbeek.nl/CppQtRubiksClockWidget.htm
//---------------------------------------------------------------------------
#ifndef QTRUBIKSCLOCKWIDGET_H
#define QTRUBIKSCLOCKWIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>

#include <QWidget>

#include "rubiksclock.h"       //Required by MOC
#include "rubiksclockfwd.h"
#include "rubiksclockwidget.h" //Required by MOC
#pragma GCC diagnostic pop

namespace Wt { struct WMouseEventEvent; }
struct QPainter;

namespace ribi {
namespace ruco {

///QtRubiksClockWidget displays a RubiksClock
class QtRubiksClockWidget : public QWidget
{
  Q_OBJECT

public:
  ///A QtRubiksClockWidget is created by its toggle state and its color
  QtRubiksClockWidget(
    const bool toggled = false,
    const unsigned char red = 255,
    const unsigned char green = 255,
    const unsigned char blue = 255);

  ///Obtain a read-only pointer to the RubiksClockWidget
  const ClockWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the RubiksClockWidget
  ClockWidget * GetWidget() { return m_widget.get(); }

  ///Obtain the QtRubiksClockWidget its version
  static const std::string GetVersion() noexcept;

  ///Obtain the QtRubiksClockWidget its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///\brief
  ///Draw the RubiksClock
  ///
  ///Because a Rubik's Clock has two sides, the parameter
  ///front_size determines whether to draw the front side or the back side
  static void DrawRubiksClock(
    QPainter& painter,
    const int x, const int y,
    const int width, const int height,
    const Clock * const clock,
    const bool front_size);

  ///Draw the RubiksClock
  static void DrawRubiksClock(
    QPainter& painter,
    const ClockWidget * const widget);

  protected:
  ///Paint the QtRubiksClockWidget
  void paintEvent(QPaintEvent *);
  //void paintEvent(Wt::WPaintDevice *paintDevice);
  void mousePressEvent(QMouseEvent *);

  private:
  ///The RubiksClockWidget
  boost::scoped_ptr<ClockWidget> m_widget;

  ///Do not let this be called by the client
  void resize(const int width, const int height);

  ///Repaint the QtRubiksClockWidget
  void DoRepaint();

  ///Respond to the widget resizing
  void OnResize();
};

} //~namespace ruco
} //~namespace ribi

#endif // QTRUBIKSCLOCKWIDGET_H
