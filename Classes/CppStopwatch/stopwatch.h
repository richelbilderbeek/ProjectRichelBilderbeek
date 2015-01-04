//---------------------------------------------------------------------------
/*
Stopwatch, stopwatch class
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppStopwatch.htm
//---------------------------------------------------------------------------
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>
#include <string>
#include <vector>

namespace ribi {

struct Stopwatch
{
  Stopwatch() noexcept : m_time_start(std::time(0)) {}
  const std::time_t m_time_start;
  int elapsed() const noexcept
  {
    return std::difftime(std::time(0),m_time_start);
  }
  static std::string GetVersion() noexcept
  {
    return "1.1";
  }
  static std::vector<std::string> GetVersionHistory() noexcept
  {
    return {
      "2010-10-08: version 1.0: initial version",
      "2011-05-30: version 1.1: added version history"
    };
  }
};

} //~namespace ribi

#endif // STOPWATCH_H
