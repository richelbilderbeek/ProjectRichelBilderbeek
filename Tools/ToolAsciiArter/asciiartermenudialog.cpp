//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------


#include "asciiartermenudialog.h"

#include "asciiarter.h"

const ribi::About ribi::AsciiArterMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "AsciiArter",
    "tool to create ASCII art",
    "the 12th of July 2013",
    "2006-2013",
    "http://www.richelbilderbeek.nl/ToolAsciiArter.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("AsciiArter version: " + AsciiArter::GetVersion());
  return a;
}

const std::string ribi::AsciiArterMenuDialog::GetVersion()
{
  return "5.2";
}

const std::vector<std::string> ribi::AsciiArterMenuDialog::GetVersionHistory()
{
  return {
    "2006-12-13: Version 1.0: initial C++ Builder version, called 'AsciiArter'",
    "2006-12-16: Version 2.0: renamed 'AsciiArter' to 'TestAsciiArter', minor improvements",
    "2008-06-21: Version 3.0: minor improvements",
    "2011-03-23: Version 4.0: port to Qt4",
    "2011-03-27: Version 4.1: added web application version",
    "2011-04-04: Version 4.2: fix bug under the web application its Convert button",
    "2011-04-25: Version 4.3: removed website version\'s Close button, use of Wt::WMenu in website version",
    "2011-08-31: Version 4.4: added Welcome picture to website version",
    "2012-07-30: Version 5.0: renamed 'TestAsciiArter' to 'AsciiArter', added menu to desktop version",
    "2012-12-24: Version 5.1: slickened desktop application looks",
    "2013-07-12: Version 5.2: transitioned to Qt5 and Boost 1.54.0"
  };
}

