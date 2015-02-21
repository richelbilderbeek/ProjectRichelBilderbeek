//---------------------------------------------------------------------------
/*
RubiksClockWidget, class for displaying a RubiksClock
Copyright (C) 2011-2015 Richel Bilderbeek

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

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>
#include <boost/signals2.hpp>
#include "rubiksclockfwd.h"
#include "widget.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace ruco {

///RubiksClockWidget is a class to display a RubiksClock
struct ClockWidget : public Widget
{
  explicit ClockWidget(
    const int x = 0,
    const int y = 0,
    const int width = 192,
    const int height = 192
  ) noexcept;

  ///Click on the RubiksClock by the left mouse button or another
  void Click(const int x, const int y,const bool button_left) noexcept;

  ///Flip the Rubik's Clock and display the other side
  void Flip() noexcept;

  ///Does the widget display the front side?
  bool GetDisplayFront() const noexcept { return m_display_front; }

        Clock * GetRubiksClock()       noexcept { return m_clock.get(); }
  const Clock * GetRubiksClock() const noexcept { return m_clock.get(); }
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  ///Respond to a change in the clock
  mutable boost::signals2::signal<void ()> m_signal_widget_flipped;

  private:
  //RubiksClockWidget can only be deleted by Boost smart pointers
  virtual ~ClockWidget() noexcept {}
  friend void boost::checked_delete<>(ClockWidget*);

  ///The RubiksClock
  boost::scoped_ptr<Clock> m_clock;

  ///Does this widget display the front or the back side?
  bool m_display_front;

  ///Respond to a change in geometry
  void OnResize() noexcept;

  friend std::ostream& operator<<(std::ostream& os, const ClockWidget& widget) noexcept;
};

std::ostream& operator<<(std::ostream& os, const ClockWidget& widget) noexcept;

} //~namespace ruco
} //~namespace ribi

#endif // RUBIKSCLOCKWIDGET_H
