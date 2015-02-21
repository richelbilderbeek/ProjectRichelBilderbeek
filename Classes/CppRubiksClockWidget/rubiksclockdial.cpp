//---------------------------------------------------------------------------
/*
ClockDial, class for displaying a Rubik's Clock Dial
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "rubiksclockdial.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include "dial.h"

#include "trace.h"

#pragma GCC diagnostic pop

ribi::ruco::ClockDial::ClockDial(
  const int time,
  const int x,
  const int y,
  const int width,
  const int height,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_dial(new Dial(0.0,red,green,blue)),
    m_time(time + 1)
{
  assert(m_dial);
  SetGeometry(x,y,width,height);
  Turn(-1);
}

std::string ribi::ruco::ClockDial::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::ruco::ClockDial::GetVersionHistory() noexcept
{
  return {
    "2011-09-08: Version 1.0: initial version, called RubiksClockDial",
    "2014-01-23: Version 1.1: renamed to ClockDial",
    "2014-03-28: version 1.2: replaced Rect by Boost.Geometry its box class"
  };
}

void ribi::ruco::ClockDial::Turn(const int n_positions_clockwise) noexcept
{
  if (n_positions_clockwise % 12 != 0)
  {
    m_time += n_positions_clockwise;
    m_time %= 12;
    m_time += 12;
    m_time %= 12;
    assert(m_time >= 0);
    assert(m_time < 12);
    m_dial->SetPosition(boost::numeric_cast<double>(m_time) / 12.0);
  }
}

std::ostream& ribi::ruco::operator<<(std::ostream& os, const ClockDial& widget) noexcept
{
  os
    << "<ClockDial>"
    << *widget.m_dial
    //<< widget.GetGeometry()
    << "</ClockDial>";
  return os;
}


