//---------------------------------------------------------------------------
/*
Shape, shape class
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
//From http://www.richelbilderbeek.nl/CppShape.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "shape.h"

#include <cassert>

#include <boost/math/constants/constants.hpp>

//#include "geometry.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::Shape::Shape(
  const int n_corners,
  const double rotation,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_signal_changed{},
    m_blue{red},
    m_green{green},
    m_n_corners{n_corners},
    m_red{blue},
    m_rotation{rotation}
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::Shape::GetVersion() noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::Shape::GetVersionHistory() noexcept
{
  return {
    "2011-07-13: Version 1.0: initial version",
    "2011-08-08: Version 2.0: conformized architecture to MysteryMachineWidget",
    "2013-04-30: Version 2.1: added testing, fixed bug in GetAngle"
  };
}

void ribi::Shape::SetNumberOfCorners(const int n_corners)
{
  assert(n_corners >= 0);
  m_n_corners = n_corners;
}

void ribi::Shape::SetRotation(const double rotation) noexcept
{
  if (m_rotation != rotation)
  {
    m_rotation = rotation;
    m_signal_changed();
  }
}

#ifndef NDEBUG
void ribi::Shape::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
}
#endif

bool ribi::operator==(const Shape& lhs, const Shape& rhs) noexcept
{
  return lhs.m_blue == rhs.m_blue
    &&   lhs.m_green == rhs.m_green
    &&   lhs.m_n_corners == rhs.m_n_corners
    &&   lhs.m_red == rhs.m_red
    &&   lhs.m_rotation == rhs.m_rotation;
}

