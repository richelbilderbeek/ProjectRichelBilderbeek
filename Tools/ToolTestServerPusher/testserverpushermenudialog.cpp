//---------------------------------------------------------------------------
/*
TestServerPusher, tool to test WtServerPusher
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
//From http://www.richelbilderbeek.nl/ToolTestServerPusher.htm
//---------------------------------------------------------------------------
#include "about.h"
#include "testserverpushermenudialog.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
const ribi::About ribi::ToolTestServerPusher::MenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestServerPusher",
    "tool to test WtServerPusher",
    "the 5th of August 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolTestServerPusher.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}
//---------------------------------------------------------------------------
const std::string ribi::ToolTestServerPusher::MenuDialog::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> ribi::ToolTestServerPusher::MenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-08-05: Version 1.0: initial version, derived from TestWtBroadcastServer");
  return v;
}
//---------------------------------------------------------------------------
