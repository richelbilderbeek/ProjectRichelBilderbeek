//---------------------------------------------------------------------------
/*
Stopwatch, stopwatch class
Copyright (C) 2010 Richel Bilderbeek

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
//---------------------------------------------------------------------------
#include <ctime>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
struct Stopwatch
{
  Stopwatch() : m_time_start(std::time(0)) {}
  const std::time_t m_time_start;
  int elapsed() const
  {
    return std::difftime(std::time(0),m_time_start);
  }
  static const std::string GetVersion()
  {
    return "1.1";
  }
  static const std::vector<std::string> GetVersionHistory()
  {
    std::vector<std::string> v;
    v.push_back("2010-10-08: version 1.0: initial version");
    v.push_back("2011-05-30: version 1.1: added version history");
    return v;
  }
};
//---------------------------------------------------------------------------
#endif // STOPWATCH_H
