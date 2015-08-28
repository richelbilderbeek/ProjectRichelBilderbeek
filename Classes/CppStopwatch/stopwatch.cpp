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
#include "stopwatch.h"

ribi::Stopwatch::Stopwatch() noexcept
  : m_time_start(std::chrono::system_clock::now())
{

}

double ribi::Stopwatch::GetElapsedSecs() const noexcept
{
  const std::chrono::system_clock::duration d = std::chrono::system_clock::now() - m_time_start;
  const long long int n_msecs_passed{std::chrono::duration_cast<std::chrono::milliseconds>(d).count()};
  const double secs_passed{static_cast<double>(n_msecs_passed) / 1000.0};
  return secs_passed;
}

std::string ribi::Stopwatch::GetVersion() const noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::Stopwatch::GetVersionHistory() const noexcept
{
  return {
    "2010-10-08: version 1.0: initial version",
    "2011-05-30: version 1.1: added version history",
    "2015-08-28: version 2.0: give time in floating point seconds, use C++11 chrono facilities"
  };
}
