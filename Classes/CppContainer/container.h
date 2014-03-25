//---------------------------------------------------------------------------
/*
Container, class with container class helper functions
Copyright (C) 2013-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppContainer.htm
//---------------------------------------------------------------------------
#ifndef CONTAINER_H
#define CONTAINER_H

#include <set>
#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#pragma GCC diagnostic pop

namespace ribi {

///Class with container class helper functions
struct Container
{
  template <class T>
  static std::string ToStr(const std::set<T>& set) noexcept
  {
    std::string str;
    std::stringstream s;
    for (const auto t: set) { s << t << ","; }
    str = s.str();
    str.pop_back();
    str = "{" + str + "}";
    return str;
  }

  template <class T>
  static std::string ToStr(const std::vector<T>& v) noexcept
  {
    std::string str;
    std::stringstream s;
    for (const auto t: v) { s << t << ","; }
    str = s.str();
    str.pop_back();
    str = "{" + str + "}";
    return str;
  }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif
