//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
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
//From http://www.richelbilderbeek.nl/ToolTestDial.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testdialmenudialog.h"


#include "dial.h"

const About TestDialMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestDial",
    "tool to test the Dial and DialWidget classes",
    "the 31st of August 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolTestDial.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Dial version: " + Dial::GetVersion());
  return a;
}

const std::string TestDialMenuDialog::GetVersion()
{
  return "2.1";
}

const std::vector<std::string> TestDialMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-04-11: Version 1.0: initial version, web version not yet working");
  v.push_back("2011-04-11: Version 1.1: got the web version working");
  v.push_back("2011-06-27: Version 1.2: split up logic and graphics of user interfaces");
  v.push_back("2011-07-16: Version 1.3: updated to new Dial version");
  v.push_back("2011-08-07: Version 2.0: conformized architure for MysteryMachine");
  v.push_back("2011-08-31: Version 2.1: added more testing option, added image to Welcome page of website version");
  return v;
}

