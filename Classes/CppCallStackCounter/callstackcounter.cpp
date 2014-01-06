//---------------------------------------------------------------------------
/*
CallStackCounter, C++ class to track the size of the call stack
Copyright (C) 2009-2014 Richel Bilderbeek

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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCallStackCounter.htm
//---------------------------------------------------------------------------
#include "callstackcounter.h"

#include <algorithm>
#include "callstackcounter.h"

int CallStackCounter::cnt = 0;
int CallStackHistoryCounter::cnt = 0;
std::vector<int> CallStackHistoryCounter::history = std::vector<int>();

int CallStackHistoryCounter::Max()
{
  return *std::max_element(history.begin(),history.end());
}
