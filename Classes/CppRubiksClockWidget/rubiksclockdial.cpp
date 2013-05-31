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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "rubiksclockdial.h"

#include <cassert>
#include <cmath>
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include "dial.h"
#include "rectangle.h"
#include "trace.h"
//---------------------------------------------------------------------------
RubiksClockDial::RubiksClockDial(
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
//---------------------------------------------------------------------------
const std::string RubiksClockDial::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> RubiksClockDial::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-09-08: Version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void RubiksClockDial::Turn(const int n_positions_clockwise)
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
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const RubiksClockDial& widget)
{
  os
    << "<RubiksClockDial>"
    << *widget.m_dial
    << widget.GetGeometry()
    << "</RubiksClockDial>";
  return os;
}
//---------------------------------------------------------------------------

