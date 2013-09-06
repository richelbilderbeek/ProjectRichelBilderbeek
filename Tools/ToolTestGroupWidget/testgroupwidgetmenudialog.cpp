//---------------------------------------------------------------------------
/*
TestGroupWidget, tool to test the GroupWidget class
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
//From http://www.richelbilderbeek.nl/ToolTestGroupWidget.htm
//---------------------------------------------------------------------------
#include "testgroupwidgetmenudialog.h"
#include "about.h"
//---------------------------------------------------------------------------
const ribi::About ribi::TestGroupWidgetMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestGroupWidget",
    "tool to test the (Wt)GroupWidget class",
    "the 8th of September 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolTestGroupWidget.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}
//---------------------------------------------------------------------------
const std::string ribi::TestGroupWidgetMenuDialog::GetVersion()
{
  return "1.3";
}
//---------------------------------------------------------------------------
const std::vector<std::string> ribi::TestGroupWidgetMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-16: Version 1.0: initial version");
  v.push_back("2011-06-26: Version 1.1: replaced Wt::WTimer by WtSafeTimer");
  v.push_back("2011-06-30: Version 1.2: replaced WtSafeTimer by Wt::WPushButton");
  v.push_back("2011-09-08: Version 1.3: added edit in website version");
  return v;
}
//---------------------------------------------------------------------------
