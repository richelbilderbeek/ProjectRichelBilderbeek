//---------------------------------------------------------------------------
/*
RubiksClockDialWidget, class for displaying a RubiksClockDial
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
//From http://www.richelbilderbeek.nl/CppRubiksClockDialWidget.htm
//---------------------------------------------------------------------------
#ifndef RUBIKSCLOCKDIALWIDGET_H
#define RUBIKSCLOCKDIALWIDGET_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/signals2.hpp>
#include "rubiksclockfwd.h"
#include "widget.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace ruco {

///RubiksClockDialWidget is a class to display a RubiksClockDial
struct ClockDialWidget : public ::ribi::Widget
{
  explicit ClockDialWidget(
    const double position,
    const int x,
    const int y,
    const int width,
    const int height,
    const unsigned char red,
    const unsigned char green,
    const unsigned char blue);

        ClockDial * GetRubiksClockDial()       noexcept { return m_dial.get(); }
  const ClockDial * GetRubiksClockDial() const noexcept { return m_dial.get(); }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Is the dial clicked?
  bool IsClicked(const int x, const int y) const;

  private:
  //RubiksClockDialWidget can only be deleted by Boost smart pointers
  virtual ~ClockDialWidget() noexcept {}
  friend void boost::checked_delete<>(ClockDialWidget*);

  boost::scoped_ptr<ClockDial> m_dial;

  static double GetDistance(const double dX, const double dY);


  friend std::ostream& operator<<(std::ostream& os, const ClockDialWidget& widget);
};

std::ostream& operator<<(std::ostream& os, const ClockDialWidget& widget);

} //~namespace ruco
} //~namespace ribi

#endif // RUBIKSCLOCKDIALWIDGET_H
