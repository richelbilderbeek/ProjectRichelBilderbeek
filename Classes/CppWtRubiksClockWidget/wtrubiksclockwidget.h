//---------------------------------------------------------------------------
/*
WtClockWidget, Wt widget for displaying the Clock class
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
//From http://www.richelbilderbeek.nl/CppWtClockWidget.htm
//---------------------------------------------------------------------------
#ifndef WTRUBIKSCLOCKWIDGET_H
#define WTRUBIKSCLOCKWIDGET_H

#include <string>
#include <vector>

#include <boost/signals2.hpp>

#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>

#include "rubiksclockfwd.h"

namespace Wt { struct WMouseEventEvent; }

namespace ribi {
namespace ruco {
//struct Clock;
//struct ClockWidget;

///WtClockWidget displays a Clock
struct WtClockWidget : public Wt::WPaintedWidget
{
  ///A WtClockWidget is created by its toggle state and its color
  explicit WtClockWidget(
    const bool toggled = false,
    const unsigned char red = 255,
    const unsigned char green = 255,
    const unsigned char blue = 255);

  ///Obtain a read-only pointer to the ClockWidget
  const ClockWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the ClockWidget
  ClockWidget * GetWidget() { return m_widget.get(); }

  ///Obtain the WtClockWidget its version
  static const std::string GetVersion();

  ///Obtain the WtClockWidget its version history
  static const std::vector<std::string> GetVersionHistory();

  ///\brief
  ///Draw the Clock
  ///
  ///Because a Rubik's Clock has two sides, the parameter
  ///front_size determines whether to draw the front side or the back side
  static void DrawClock(
    Wt::WPainter& painter,
    const int x, const int y,
    const int width, const int height,
    const Clock * const clock,
    const bool front_size);

  ///Draw the Clock
  static void DrawClock(
    Wt::WPainter& painter,
    const ClockWidget * const widget);

  protected:
  ///Paint the WtClockWidget
  void paintEvent(Wt::WPaintDevice *paintDevice);

  private:
  ///The ClockWidget
  boost::scoped_ptr<ClockWidget> m_widget;

  ///Do not let this be called by the client
  void resize(const Wt::WLength& width, const Wt::WLength& height);

  ///Repaint the WtClockWidget
  void DoRepaint();

  ///Respond to mouse click
  void OnClicked(const Wt::WMouseEvent& e);

  ///Respond to the widget resizing
  void OnResize();
};

} //~namespace ruco
} //~namespace ribi

#endif // WTRUBIKSCLOCKWIDGET_H
