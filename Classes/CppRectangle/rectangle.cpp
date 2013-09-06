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

const std::string ribi::Rect::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::Rect::GetVersionHistory()
{
  return {
    "2011-08-20: Version 1.0: initial version"
  };
}

std::ostream& ribi::operator<<(std::ostream& os,const Rect& rect)
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

bool ribi::operator==(const Rect& lhs, const Rect& rhs)
{
  return
       lhs.x == rhs.x
    && lhs.y == rhs.y
    && lhs.w == rhs.w
    && lhs.h == rhs.h;
}

bool ribi::operator!=(const Rect& lhs, const Rect& rhs)
{
  return !(lhs==rhs);
}

