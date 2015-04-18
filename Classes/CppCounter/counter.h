//---------------------------------------------------------------------------
/*
Counter, an incrementing counter
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppCounter.htm
//---------------------------------------------------------------------------
#ifndef COUNTER_H
#define COUNTER_H

#include <string>
#include <vector>

namespace ribi {

///Counter is a counter
struct Counter
{
  ///Counter is constructed with an initial count, which is initialized to
  ///zero by default
  explicit Counter(const int initial_count = 0) noexcept;

  ///Increments count
  void Inc() noexcept { ++m_count; }

  //Prefix
  Counter& operator++()
  {
    Inc();
    return *this;
  }

  ///Get the count
  int Get() const noexcept { return m_count; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  ///The count
  int m_count;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // COUNTER_H
