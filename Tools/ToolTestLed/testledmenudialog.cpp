//---------------------------------------------------------------------------
/*
TestLed, tool to test the Led class
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
//From http://www.richelbilderbeek.nl/ToolTestLed.htm
//---------------------------------------------------------------------------


#include "testledmenudialog.h"

#include "led.h"
#include "ledwidget.h"

const About TestLedMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestLed",
    "tool to test the Led class",
    "the 8th of September 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolTestLed.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Led version: " + Led::GetVersion());
  a.AddLibrary("LedWidget version: " + LedWidget::GetVersion());
  return a;
}

const std::string TestLedMenuDialog::GetVersion()
{
  return "1.3";
}

const std::vector<std::string> TestLedMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-04-10: Version 1.0: initial version, web version not yet working");
  v.push_back("2011-04-11: Version 1.1: got web version to work, added more About info");
  v.push_back("2011-07-02: Version 1.2: added menu");
  v.push_back("2011-09-08: Version 1.3: added Welcome screen picture and increased testing in website version");
  return v;
}

