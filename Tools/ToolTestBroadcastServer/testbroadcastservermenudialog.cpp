//---------------------------------------------------------------------------
/*
TestBroadcastServer, tool to test WtBroadcastServer
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
//From http://www.richelbilderbeek.nl/ToolTestBroadcastServer.htm
//---------------------------------------------------------------------------
#include "about.h"
#include "testbroadcastservermenudialog.h"
//---------------------------------------------------------------------------
namespace ToolTestBroadcastServer {
//---------------------------------------------------------------------------
const About MenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestBroadcastServer",
    "tool to test WtBroadcastServer",
    "the 1th of August 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolTestBroadcastServer.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}
//---------------------------------------------------------------------------
const std::string MenuDialog::GetVersion()
{
  return "2.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> MenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-07-27: Version 1.0: initial version");
  v.push_back("2011-07-28: Version 1.1: adapted ToolTestBroadcastServer to fit within WtWebsite");
  v.push_back("2011-08-01: Version 1.2: adapted ToolTestBroadcastServer to fit within WtWebsite");
  return v;
}
//---------------------------------------------------------------------------
} //~namespace ToolTestBroadcastServer
//---------------------------------------------------------------------------
