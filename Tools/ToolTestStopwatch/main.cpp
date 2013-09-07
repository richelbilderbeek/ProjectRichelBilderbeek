//---------------------------------------------------------------------------
/*
TestStopwatch, tool to test the Stopwatch class
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
//From http://www.richelbilderbeek.nl/ToolTestStopwatch.htm
//---------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>

#include <boost/timer.hpp>

#include "stopwatch.h"

int main()
{
  ribi::Stopwatch s;
  boost::timer t;
  std::system("./../ToolPause-build-desktop/Pause 5");
  std::cout
    << "Elapsed time (should be 5 seconds):\n"
    << "Stopwatch: " << s.elapsed() << " seconds\n"
    << "boost::timer: " << t.elapsed() << " milliseconds\n";
}
