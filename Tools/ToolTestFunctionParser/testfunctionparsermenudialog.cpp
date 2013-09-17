//---------------------------------------------------------------------------
/*
TestFunctionParser, tool to demonstrate Warp's FunctionParser class
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestFunctionParser.htm
//---------------------------------------------------------------------------
#include "testfunctionparsermenudialog.h"

const ribi::About ribi::TestFunctionParserMenuDialog::GetAbout() noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestFunctionParser",
    "tool to demonstrate Warp's FunctionParser class",
    "the 22nd of April 2013",
    "2010-2013",
    "http://www.richelbilderbeek.nl/ToolTestFunctionParser.htm",
    GetVersion(),
    GetVersionHistory());
  #ifdef _WIN32
  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  #else
  a.AddLibrary("Warp's FunctionParser version: 4.5.1");
  #endif
  return a;
}

const std::string ribi::TestFunctionParserMenuDialog::GetVersion() noexcept
{
  return "2.3";
}

const std::vector<std::string> ribi::TestFunctionParserMenuDialog::GetVersionHistory() noexcept
{
  return {
    "2010-02-02: Version 1.0: initial C++ Builder desktop version",
    "2011-06-24: Version 2.0: port to Qt Creator desktop version",
    "2011-06-24: Version 2.1: added web version",
    "2011-08-31: Version 2.2: added image to Welcome to web version",
    "2013-04-22: Version 2.3: added image to Welcome to desktop version"
  };
}
