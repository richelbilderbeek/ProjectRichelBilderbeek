//---------------------------------------------------------------------------
/*
Rasper, Raspberry Pi GPIO web application controller
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
//From http://www.richelbilderbeek.nl/ToolRasper.htm
//---------------------------------------------------------------------------
#include "about.h"
#include "raspermenudialog.h"

namespace ToolRasper {

const About MenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "Rasper",
    "Raspberry Pi GPIO web application controller",
    "the 9th of February 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolRasper.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("IpAddress version: " + IpAddress::GetVersion());

  return a;
}

const std::string MenuDialog::GetVersion()
{
  return "0.3";
}

const std::vector<std::string> MenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-01-23: Version 0.1: initial version");
  v.push_back("2013-02-06: Version 0.2: progress on GUI");
  v.push_back("2013-02-09: Version 0.3: initial GUI");
  return v;
}

} //~namespace ToolRasper

