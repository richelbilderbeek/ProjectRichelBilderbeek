//---------------------------------------------------------------------------
/*
Dial, dial class
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
//From http://www.richelbilderbeek.nl/CppDial.htm
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "dial.h"

#include <cmath>

//Terrible #define, but my crosscompiler cannot find the definition of M_PI in cmath.h :-(
#ifndef M_PI
# define M_PI		3.14159265358979323846	/* pi */
#endif

#include <cassert>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "trace.h"

#pragma GCC diagnostic pop

Dial::Dial(
  const double position,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_red(red), m_green(green), m_blue(blue)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(position >= 0.0);
  assert(position <= 1.0);
  SetPosition(position);
}

const std::string Dial::GetVersion()
{
  return "3.3";
}

const std::vector<std::string> Dial::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-04-11: Version 1.0: initial version");
  v.push_back("2011-06-03: Version 2.0: moved widget logic to DialWidget class");
  v.push_back("2011-08-07: Version 3.0: conformized architure for MysteryMachine");
  v.push_back("2011-08-20: Version 3.1: added operator<<");
  v.push_back("2011-08-31: Version 3.2: allow changing the dial its color");
  v.push_back("2013-04-30: Version 3.3: added testing, fixed bug in GetAngle");
  return v;
}

void Dial::SetBlue(const int b)
{
  assert(b >=   0);
  assert(b  < 256);

  if (m_blue != boost::numeric_cast<unsigned char>(b))
  {
    m_blue = boost::numeric_cast<unsigned char>(b);
    m_signal_color_changed();
  }
}

void Dial::SetColor(const int r,const int g,const int b)
{
  SetRed(r);
  SetGreen(g);
  SetBlue(b);
}

void Dial::SetGreen(const int g)
{
  assert(g >=   0);
  assert(g  < 256);

  if (m_green != boost::numeric_cast<unsigned char>(g))
  {
    m_green = boost::numeric_cast<unsigned char>(g);
    m_signal_color_changed();
  }
}

void Dial::SetRed(const int r)
{
  assert(r >=   0);
  assert(r  < 256);

  if (m_red != boost::numeric_cast<unsigned char>(r))
  {
    m_red = boost::numeric_cast<unsigned char>(r);
    m_signal_color_changed();
  }
}

void Dial::SetPosition(const double position)
{
  assert(position >= 0.0);
  assert(position <= 1.0);
  if (m_position != position)
  {
    m_position = position;
    m_signal_position_changed();
  }
}

double Dial::GetAngle(const double dx, const double dy)
{
  return M_PI - (std::atan2(dx,dy));
}

double Dial::GetDistance(const double dX, const double dY)
{
  return std::sqrt( (dX * dX) + (dY * dY) );
}

#ifndef NDEBUG
void Dial::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test GetAngle
  {
    const double angle =  GetAngle(0.0,-1.0); //North
    const double expected = 0.0 * M_PI;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(1.0,-1.0); //North-East
    const double expected = 0.25 * M_PI;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(1.0,0.0); //East
    const double expected = 0.5 * M_PI;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(1.0,1.0); //South-East
    const double expected = 0.75 * M_PI;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(0.0,1.0); //South
    const double expected = 1.0 * M_PI;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(-1.0,1.0); //South-West
    const double expected = 1.25 * M_PI;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(-1.0,0.0); //West
    const double expected = 1.5 * M_PI;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(-1.0,-1.0); //North-West
    const double expected = 1.75 * M_PI;
    assert(std::abs(angle-expected) < 0.01);
  }
  //GetDistance
  {
    const double distance = GetDistance(3.0,4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = GetDistance(-3.0,4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = GetDistance(3.0,-4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = GetDistance(-3.0,-4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
}
#endif

std::ostream& operator<<(std::ostream& os, const Dial& dial)
{
  os
    << "<Dial>"
    << "<blue>"
      << static_cast<int>(dial.m_blue)
    << "</blue>"
    << "<green>"
    << static_cast<int>(dial.m_green)
    << "</green>"
    << "<position>"
    << dial.m_position
    << "</position>"
    << "<red>"
    << static_cast<int>(dial.m_red)
    << "</red>"
    << "</Dial>";
  return os;
}
