//---------------------------------------------------------------------------
/*
RubiksClockWidget, class for displaying a RubiksClock
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
//From http://www.richelbilderbeek.nl/CppRubiksClockWidget.htm
//---------------------------------------------------------------------------
#ifndef RUBIKSCLOCKWIDGET_H
#define RUBIKSCLOCKWIDGET_H
//---------------------------------------------------------------------------
#include <iosfwd>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include "widget.h"
//---------------------------------------------------------------------------
struct RubiksClock;
//---------------------------------------------------------------------------
///RubiksClockWidget is a class to display a RubiksClock
struct RubiksClockWidget : public Widget
{
  explicit RubiksClockWidget(
    const int x = 0,
    const int y = 0,
    const int width = 192,
    const int height = 192);

  ///Click on the RubiksClock by the left mouse button or another
  void Click(const int x, const int y,const bool button_left);

  ///Flip the Rubik's Clock and display the other side
  void Flip();

  ///Does the widget display the front side?
  bool GetDisplayFront() const { return m_display_front; }

  ///Obtain a read-and-write pointert to the RubiksClock
  RubiksClock * GetRubiksClock() { return m_clock.get(); }

  ///Obtain a read-only pointert to the RubiksClock
  const RubiksClock * GetRubiksClock() const { return m_clock.get(); }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Respond to a change in the clock
  mutable boost::signals2::signal<void ()> m_signal_widget_flipped;

  private:
  //RubiksClockWidget can only be deleted by Boost smart pointers
  virtual ~RubiksClockWidget() {}
  friend void boost::checked_delete<>(RubiksClockWidget*);

  ///The RubiksClock
  boost::scoped_ptr<RubiksClock> m_clock;

  ///Does this widget display the front or the back side?
  bool m_display_front;

  ///Respond to a change in geometry
  void OnResize();

  friend std::ostream& operator<<(std::ostream& os, const RubiksClockWidget& widget);
};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const RubiksClockWidget& widget);
//---------------------------------------------------------------------------
#endif // RUBIKSCLOCKWIDGET_H
