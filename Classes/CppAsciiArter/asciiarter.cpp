//---------------------------------------------------------------------------
/*
AsciiArter, class to convert greyscale to ASCII art
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
//From http://www.richelbilderbeek.nl/CppAsciiArter.htm
//---------------------------------------------------------------------------
#include "asciiarter.h"

#warning AsciiArter is obsolete, use DrawCanvas instead

const std::string ribi::AsciiArter::GetVersion() noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::AsciiArter::GetVersionHistory() noexcept
{
  return {
    "2011-03-23: Version 1.0: initial version",
    "2014-01-07: Version 2.0: add conversion to Canvas",
    "2014-02-26: Version 2.1: superseded by DrawCanvas"
  };
}
