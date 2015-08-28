//---------------------------------------------------------------------------
/*
TestStopwatch, tool to test the Stopwatch class
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
//From http://www.richelbilderbeek.nl/ToolTestStopwatch.htm
//---------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/timer.hpp>

#include "stopwatch.h"
#pragma GCC diagnostic pop

void WaitStl(const double n_secs) noexcept
{
  const std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
  while (1)
  {
    const std::chrono::system_clock::duration d = std::chrono::system_clock::now() - t;
    const long long int n_msecs_passed{std::chrono::duration_cast<std::chrono::milliseconds>(d).count()};
    const double secs_passed{static_cast<double>(n_msecs_passed) / 1000.0};
    if (secs_passed > n_secs) return;
  }
}

void WaitBoost(const double n_secs) noexcept
{
  boost::timer t;
  while (t.elapsed() < n_secs) {}
}

int main()
{
  ribi::Stopwatch s;
  boost::timer t;

  WaitStl(2.5);
  WaitBoost(2.5);

  std::cout
    << "Elapsed time (should be 5 seconds):\n"
    << "Stopwatch: " << s.GetElapsedSecs() << " seconds\n"
    << "boost::timer: " << t.elapsed() << " milliseconds\n";
}
