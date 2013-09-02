//---------------------------------------------------------------------------
/*
Shape, shape class
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
//From http://www.richelbilderbeek.nl/CppShape.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "shape.h"

#include <cassert>

#ifdef __STRICT_ANSI__
#include <boost/math/constants/constants.hpp>
#else
#include <cmath>
#endif

//#include "trace.h"

#pragma GCC diagnostic pop

Shape::Shape(
  const int n_corners,
  const double rotation,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_red(red),
    m_green(green),
    m_blue(blue)
{
  #ifndef NDEBUG
  Test();
  #endif
  SetNumberOfCorners(n_corners);
  SetRotation(rotation);
}

const std::string Shape::GetVersion()
{
  return "2.1";
}

const std::vector<std::string> Shape::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-07-13: Version 1.0: initial version");
  v.push_back("2011-08-08: Version 2.0: conformized architecture to MysteryMachineWidget");
  v.push_back("2013-04-30: Version 2.1: added testing, fixed bug in GetAngle");
  return v;
}

void Shape::SetNumberOfCorners(const int n_corners)
{
  assert(n_corners >= 0);
  m_n_corners = n_corners;
}

void Shape::SetRotation(const double rotation)
{
  if (m_rotation != rotation)
  {
    m_rotation = rotation;
    m_signal_changed();
  }
}

double Shape::GetAngle(const double dx, const double dy)
{
  #ifdef __STRICT_ANSI__
  const double pi = boost::math::constants::pi<double>();
  #else
  const double pi = M_PI;
  #endif
  return pi - std::atan2(dx,dy);
}

double Shape::GetDistance(const double dX, const double dY)
{
  return std::sqrt( (dX * dX) + (dY * dY) );
}

#ifndef NDEBUG
void Shape::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test GetAngle
  #ifdef __STRICT_ANSI__
  const double pi = boost::math::constants::pi<double>();
  #else
  const double pi = M_PI;
  #endif

  {
    const double angle =  GetAngle(0.0,-1.0); //North
    const double expected = 0.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(1.0,-1.0); //North-East
    const double expected = 0.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(1.0,0.0); //East
    const double expected = 0.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(1.0,1.0); //South-East
    const double expected = 0.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(0.0,1.0); //South
    const double expected = 1.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(-1.0,1.0); //South-West
    const double expected = 1.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(-1.0,0.0); //West
    const double expected = 1.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  GetAngle(-1.0,-1.0); //North-West
    const double expected = 1.75 * pi;
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

bool operator==(const Shape& lhs, const Shape& rhs)
{
  return lhs.m_blue == rhs.m_blue
    &&   lhs.m_green == rhs.m_green
    &&   lhs.m_n_corners == rhs.m_n_corners
    &&   lhs.m_red == rhs.m_red
    &&   lhs.m_rotation == rhs.m_rotation;
}

