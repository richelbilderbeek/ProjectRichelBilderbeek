//---------------------------------------------------------------------------
/*
KTouchLectureCreator, create KTouch lecture for C++ programmers
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolKTouchLectureCreator.htm
//---------------------------------------------------------------------------
#include "ktouchlecture.h"

#include <fstream>
#include <iterator>

#include "trace.h"

#include <cstdlib>
#include <ctime>

//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer()
{
  std::srand(std::time(0));
}

//Version:
//YYYY-MM-DD: Vx.y: [description]
//2013-02-18: V1.0: initial version

int main()
{
  //Guidelines:
  // - a line must have about 60 chars
  // - level = number_of_chars / 2
  // - word length = 2 + (level / 3)
  // - a level must have about 10 lines
  // - every level must have about two new characters
  // - I do not care if words exist
  // - if a C++ construct exists, add it
  // - use all keys in the final level
  START_TRACE();
  RandomizeTimer();

  const auto v = KTouchLecture().ToXml();
  std::ofstream f("cpp.ktouch.xml");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
}
