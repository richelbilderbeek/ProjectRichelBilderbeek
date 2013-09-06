//---------------------------------------------------------------------------
/*
RandomCode, tool to generate random C++ code
Copyright (C) 2007-2012  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------


#include "randomcode.h"

#include "randomcodemenudialog.h"

About RandomCodeMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "RandomCode",
    "tool to generate random C++ code",
    "the 25th of December 2012",
    "2007-2012",
    "http://www.richelbilderbeek.nl/ToolRandomCode.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("RandomCode version: " + RandomCode::GetVersion());
  return a;
}

const std::string RandomCodeMenuDialog::GetVersion()
{
  return "4.2";
}

const std::vector<std::string> RandomCodeMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2007-xx-xx: version 1.0: initial version in C++ Builder");
  v.push_back("2010-12-03: version 2.0: port to Qt Creator");
  v.push_back("2011-01-07: version 3.0: added menu, reworked file architecture");
  v.push_back("2011-04-24: version 4.0: major architectural change, created web version");
  v.push_back("2011-08-31: version 4.1: added Welcome picture for web version");
  v.push_back("2012-12-25: version 4.2: added menu for desktop version");
  return v;
}
