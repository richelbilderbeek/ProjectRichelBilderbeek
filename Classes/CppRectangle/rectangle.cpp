//---------------------------------------------------------------------------
/*
Rectangle, rectangle class
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
//From http://www.richelbilderbeek.nl/CppRectangle.htm
//---------------------------------------------------------------------------
#ifdef REALLY_USE_RECTANGLE

#include "rectangle.h"

#include <iostream>
#include <stdexcept>

#include "trace.h"

ribi::Rect::Rect(
    const int any_x,
    const int any_y,
    const int any_w,
    const int any_h)
  : m_x(any_x),
    m_y(any_y),
    m_w(any_w),
    m_h(any_h)
{
  if (any_w < 0.0) throw std::logic_error("Cannot create Rect with negative width");
  if (any_h < 0.0) throw std::logic_error("Cannot create Rect with negative height");
}

std::string ribi::Rect::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::Rect::GetVersionHistory() noexcept
{
  return {
    "2011-08-20: Version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::Rect::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::Rect::Translate(const int dx, const int dy) noexcept
{
  this->m_x += dx;
  this->m_y += dy;
}

std::ostream& ribi::operator<<(std::ostream& os,const Rect& rect) noexcept
{
  os
    << "<Rect>"
    << "<x>"
      << rect.m_x
    << "</x>"
    << "<y>"
      << rect.m_y
    << "</y>"
    << "<w>"
      << rect.m_w
    << "</w>"
    << "<h>"
      << rect.m_h
    << "</h>"
    << "</Rect>";
  return os;
}

bool ribi::operator==(const Rect& lhs, const Rect& rhs) noexcept
{
  return
       lhs.m_x == rhs.m_x
    && lhs.m_y == rhs.m_y
    && lhs.m_w == rhs.m_w
    && lhs.m_h == rhs.m_h;
}

bool ribi::operator!=(const Rect& lhs, const Rect& rhs) noexcept
{
  return !(lhs==rhs);
}


#endif //#ifdef REALLY_USE_RECTANGLE
