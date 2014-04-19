//---------------------------------------------------------------------------
/*
Counter, an incrementing counter
Copyright (C) 2011-2014 Richel Bilderbeek

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
#include "counter.h"

std::string ribi::Counter::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::Counter::GetVersionHistory() noexcept
{
  return {
    "2011-08-20: Version 1.0: initial version"
  };
}
