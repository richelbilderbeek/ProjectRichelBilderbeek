//---------------------------------------------------------------------------
/*
Rectangle, rectangle class
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
//From http://www.richelbilderbeek.nl/CppRectangle.htm
//---------------------------------------------------------------------------


#include "rectangle.h"

#include <iostream>

#include "rectangle.h"

ribi::Rect::Rect(
    const int any_x,
    const int any_y,
    const int any_w,
    const int any_h)
  : x(any_x),
    y(any_y),
    w(any_w),
    h(any_h)
{
  if (any_w < 0.0) throw std::logic_error("Cannot create Rect with negative width");
  if (any_h < 0.0) throw std::logic_error("Cannot create Rect with negative height");
}

const std::string ribi::Rect::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::Rect::GetVersionHistory() noexcept
{
  return {
    "2011-08-20: Version 1.0: initial version"
  };
}

std::ostream& ribi::operator<<(std::ostream& os,const Rect& rect) noexcept
{
  os
    << "<Rect>"
    << "<x>"
      << rect.x
    << "</x>"
    << "<y>"
      << rect.y
    << "</y>"
    << "<w>"
      << rect.w
    << "</w>"
    << "<h>"
      << rect.h
    << "</h>"
    << "</Rect>";
  return os;
}

bool ribi::operator==(const Rect& lhs, const Rect& rhs) noexcept
{
  return
       lhs.x == rhs.x
    && lhs.y == rhs.y
    && lhs.w == rhs.w
    && lhs.h == rhs.h;
}

bool ribi::operator!=(const Rect& lhs, const Rect& rhs) noexcept
{
  return !(lhs==rhs);
}

