/*
  Gnuplot Interface, a C++ class interface with Gnuplot.
  Copyright (C) 2005  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//
//  Gnuplot - a C++ class interface with Gnuplot
//  V4.0
//
//  Created by Richel Bilderbeek on Fri Jun 10 2005.
//  Open source.
//
//  Richel Bilderbeek
//  Website: http://www.richelbilderbeek.nl
//
//  V4.0: 19th March 2008: Conformized code
//  V3.0: 23th September 2006: Implemented suggestion by Christoph Schmalz.
//                             According to Christoph it should work under Windows now.
//                             Made the code 100% Standard C++.
//  V2.0: 12th September 2005: Got program to compile under Windows environment.
//                             Program is found NOT to run under Windows.
//                             Somebody has an idea how to open Gnuplot.exe ???
//  V1.0: 10th June 2005: first version developed on Macintosh
//
//
//  This class functions well at a Macintosh. Under Windows, the pipe to the
//  Gnuplot executable (either MS-DOS or Windows executable) will not open.
//  If you have an idea to solve this, please E-mail me.
//
//
//  Feel free to contact me when:
//  - YOU can get the program to run under Windows (and normally it wouldn't)
//  - you encounter a compile error
//  - you have made additional functionality
//  - you have outsmarted me on this interface.
//

#include <iostream>
#include <vector>
#include <cmath>

//Yes, this #include is non-standard
//But it enables you to compile-and-run
//To do it correctly, add the file 'Gnuplot.cpp' to your project,
//  and #include 'Gnuplot.h' instead.
#include "UnitGnuplotInterface.cpp"

int main()
{
  Gnuplot myPlot;

  std::vector<double> data1(1000);
  std::vector<double> data2(1000);
  for (int j=0; j!=1000; ++j)
  {
    const double jD = static_cast<double>(j);
    data1[j]= std::sin(jD/100.0);
    data2[j]= std::sin(jD/100.0);
  }

  for (int i=0; i!=10; ++i)
  {
    myPlot.ChangeWindow(i);
    const double iD = static_cast<double>(i);
    for (int j=0; j!=1000; ++j)
    {
      const double jD = static_cast<double>(j);
      data1[j]*= std::sin(jD/(20.0-iD));
      data2[j]*= std::sin(jD/(21.0-iD));
    }
    myPlot.Plot(data1);
    myPlot.Plot(data2);
  }

  std::cin.get();
}

