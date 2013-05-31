//---------------------------------------------------------------------------
/*
TimePoll, time polling server
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
//From http://www.richelbilderbeek.nl/ToolTimePoll.htm
//---------------------------------------------------------------------------
#include "about.h"
#include "stopwatch.h"
#include "timepollmenudialog.h"
//---------------------------------------------------------------------------
namespace ToolTimePoll {
//---------------------------------------------------------------------------
const About TimePollMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TimePoll",
    "time poll web application",
    "the 1th of August 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolTimePoll.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Stopwatch version: " + Stopwatch::GetVersion());
  return a;
}
//---------------------------------------------------------------------------
const std::string TimePollMenuDialog::GetVersion()
{
  return "4.2";
}
//---------------------------------------------------------------------------
const std::vector<std::string> TimePollMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-04-13: Version 0.1: initial version, the as-simple-as-possible version");
  v.push_back("2011-04-13: Version 0.2: added About screen, added that when a new user logs in, he/she has the correct initial index");
  v.push_back("2011-04-13: Version 1.0: displays which fraction of the time each option is chosen");
  v.push_back("2011-04-13: Version 1.1: minor changes for WtWebsite");
  v.push_back("2011-04-25: Version 1.2: removed Close button");
  v.push_back("2011-06-11: Version 2.0: use Wt::WTimer in WtTimePollDialog");
  v.push_back("2011-06-26: Version 2.1: use of WtSafeWTimer in WtTimePollDialog");
  v.push_back("2011-07-26: Version 3.0: use of Wt::WServer::post as described in http://richelbilderbeek.nl/CppWtExample3.htm");
  v.push_back("2011-07-27: Version 4.0: use of WtBroadcastServer");
  v.push_back("2011-07-29: Version 4.1: fixed bug in WtBroadcastServer");
  v.push_back("2011-08-01: Version 4.2: use of thread-safe data getting in WtBroadcastServer");
  v.push_back("2011-08-05: Version 5.0: use of WtServerPusher and WtTimedServerPusher");
  return v;
}
//---------------------------------------------------------------------------
} //~namespace ToolTimePoll
//---------------------------------------------------------------------------
