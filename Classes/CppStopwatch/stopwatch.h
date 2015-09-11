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

#include <chrono>
#include <string>
#include <vector>

namespace ribi {

struct Stopwatch
{
  Stopwatch() noexcept;
  double GetElapsedSecs() const noexcept;
  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;
  private:
  std::chrono::system_clock::time_point m_time_start;
};

} //~namespace ribi

#endif // STOPWATCH_H
