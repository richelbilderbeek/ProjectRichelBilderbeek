//---------------------------------------------------------------------------
/*
Dial, dial class
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
//From http://www.richelbilderbeek.nl/CppDial.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "dial.h"

#include <cassert>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "geometry.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::Dial::Dial(
  const double position,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  :
    m_signal_color_changed{},
    m_signal_position_changed{},
    m_blue{blue},
    m_green{green},
    m_position{position},
    m_red{red}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_position >= 0.0);
  assert(m_position <= 1.0);
}

std::string ribi::Dial::GetVersion() noexcept
{
  return "3.3";
}

std::vector<std::string> ribi::Dial::GetVersionHistory() noexcept
{
  return {
    "2011-04-11: Version 1.0: initial version",
    "2011-06-03: Version 2.0: moved widget logic to DialWidget class",
    "2011-08-07: Version 3.0: conformized architure for MysteryMachine",
    "2011-08-20: Version 3.1: added operator<<",
    "2011-08-31: Version 3.2: allow changing the dial its color",
    "2013-04-30: Version 3.3: added testing, fixed bug in GetAngle"
  };
}

void ribi::Dial::SetBlue(const int b) noexcept
{
  assert(b >=   0);
  assert(b  < 256);

  if (m_blue != boost::numeric_cast<unsigned char>(b))
  {
    m_blue = boost::numeric_cast<unsigned char>(b);
    m_signal_color_changed();
  }
}

void ribi::Dial::SetColor(const int r,const int g,const int b) noexcept
{
  SetRed(r);
  SetGreen(g);
  SetBlue(b);
}

void ribi::Dial::SetGreen(const int g) noexcept
{
  assert(g >=   0);
  assert(g  < 256);

  if (m_green != boost::numeric_cast<unsigned char>(g))
  {
    m_green = boost::numeric_cast<unsigned char>(g);
    m_signal_color_changed();
  }
}

void ribi::Dial::SetRed(const int r) noexcept
{
  assert(r >=   0);
  assert(r  < 256);

  if (m_red != boost::numeric_cast<unsigned char>(r))
  {
    m_red = boost::numeric_cast<unsigned char>(r);
    m_signal_color_changed();
  }
}

void ribi::Dial::SetPosition(const double position) noexcept
{
  assert(position >= 0.0);
  assert(position <= 1.0);
  if (m_position != position)
  {
    m_position = position;
    m_signal_position_changed();
  }
}

#ifndef NDEBUG
void ribi::Dial::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const double pi = boost::math::constants::pi<double>();
  const Geometry g;
  //GetAngle
  {
    const double angle =  g.GetAngle(0.0,-1.0); //North
    const double expected = 0.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(1.0,-1.0); //North-East
    const double expected = 0.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(1.0,0.0); //East
    const double expected = 0.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(1.0,1.0); //South-East
    const double expected = 0.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(0.0,1.0); //South
    const double expected = 1.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(-1.0,1.0); //South-West
    const double expected = 1.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(-1.0,0.0); //West
    const double expected = 1.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(-1.0,-1.0); //North-West
    const double expected = 1.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  //GetDistance
  {
    const double distance = g.GetDistance(3.0,4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = g.GetDistance(-3.0,4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = g.GetDistance(3.0,-4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = g.GetDistance(-3.0,-4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const Dial& dial)
{
  os
    << "<Dial>"
    << "<blue>"
    <<   static_cast<int>(dial.m_blue)
    << "</blue>"
    << "<green>"
    <<   static_cast<int>(dial.m_green)
    << "</green>"
    << "<position>"
    <<   dial.m_position
    << "</position>"
    << "<red>"
    <<   static_cast<int>(dial.m_red)
    << "</red>"
    << "</Dial>";
  return os;
}
