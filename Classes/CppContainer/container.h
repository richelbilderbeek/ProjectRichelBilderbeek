//---------------------------------------------------------------------------
/*
Container, class with container class helper functions
Copyright (C) 2013-2015 Richel Bilderbeek

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
#ifndef RIBI_CONTAINER_H
#define RIBI_CONTAINER_H

#include <algorithm>
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
  Container();

  ///Concatenate concatenates the strings, with a certain seperator
  std::string Concatenate(const std::vector<std::string>& v, const std::string& seperator = "") const noexcept;

  ///std::count(t.begin(),t.end(),u
  template <class T, class U>
  static int Count(const T& t, const U& u) noexcept
  {
    return std::count(std::begin(t),std::end(t),u);
  }

  ///Obtain the version
  static std::string GetVersion() noexcept;

  ///Obtain the version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator) const noexcept;

  template <class T>
  static std::string ToStr(const std::set<T>& set) noexcept
  {
    std::stringstream s;
    for (const auto& t: set) { s << t << ","; }
    std::string str{s.str()};
    if (!str.empty()) { str.pop_back(); }
    str = "{" + str + "}";
    return str;
  }

  template <class T>
  static std::string ToStr(const std::vector<T>& v) noexcept
  {
    std::stringstream s;
    for (const auto& t: v) { s << t << ","; }
    std::string str{s.str()};
    if (!str.empty()) { str.pop_back(); }
    str = "{" + str + "}";
    return str;
  }


  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_CONTAINER_H
