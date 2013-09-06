//---------------------------------------------------------------------------
/*
TestEntrance, tool to test WtEntrance
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestEntrance.htm
//---------------------------------------------------------------------------
#include "about.h"
#include "ipaddress.h"
#include "testentrancemenudialog.h"

const ribi::About ribi::ToolTestEntrance::MenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestEntrance",
    "tool to test WtEntrance",
    "the 19th of September 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolTestEntrance.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("IpAddress version: " + IpAddress::GetVersion());

  return a;
}

const std::string ribi::ToolTestEntrance::MenuDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::ToolTestEntrance::MenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-09-19: Version 1.0: initial version");
  return v;
}
