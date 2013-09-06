//---------------------------------------------------------------------------
/*
RubiksClockDial, class for displaying a Rubik's Clock Dial
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "rubiksclockdial.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include "dial.h"
#include "rectangle.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::RubiksClockDial::RubiksClockDial(
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
  this->SetGeometry(Rect(x,y,width,height));
  this->Turn(-1);
}

const std::string ribi::RubiksClockDial::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::RubiksClockDial::GetVersionHistory()
{
  return {
    "2011-09-08: Version 1.0: initial version"
  };
}

void ribi::RubiksClockDial::Turn(const int n_positions_clockwise)
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

std::ostream& ribi::operator<<(std::ostream& os, const RubiksClockDial& widget)
{
  os
    << "<RubiksClockDial>"
    << *widget.m_dial
    << widget.GetGeometry()
    << "</RubiksClockDial>";
  return os;
}


