//---------------------------------------------------------------------------
/*
RubiksClockDial, class for displaying a Rubik's Clock Dial
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
//From http://www.richelbilderbeek.nl/CppRubiksClockWidget.htm
//---------------------------------------------------------------------------
#ifndef RUBIKSCLOCKDIAL_H
#define RUBIKSCLOCKDIAL_H

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

struct Dial;

namespace ruco {

///ClockDial is a class to display a Rubik's Clock Dial
struct ClockDial : public Widget
{
  explicit ClockDial(
    const int time,
    const int x,
    const int y,
    const int width,
    const int height,
    const unsigned char red,
    const unsigned char green,
    const unsigned char blue);

  const Dial * GetDial() const noexcept { return m_dial.get(); }

  int GetTime() const noexcept { return m_time % 12; }

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Turn the dials n_positions_clockwise clockwise,
  ///negative values are also allowed
  void Turn(const int n_positions_clockwise) noexcept;

  private:
  //DialWidget can only be deleted by Boost smart pointers
  virtual ~ClockDial() noexcept {}
  friend void boost::checked_delete<>(ClockDial*);

  boost::scoped_ptr<Dial> m_dial;

  ///Denotes the time shown by the dial as in a clock
  int m_time;

  friend std::ostream& operator<<(std::ostream& os, const ClockDial& widget) noexcept;

  public:

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  //static double GetAngle(const double dX, const double dY);

  //From www.richelbilderbeek.nl/CppGetDistance.htm
  static double GetDistance(const double dX, const double dY) noexcept;
};

std::ostream& operator<<(std::ostream& os, const ClockDial& widget) noexcept;

} //~namespace ruco
} //~namespace ribi

#endif // RUBIKSCLOCKDIAL_H
