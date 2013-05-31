//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
Copyright (C) 2010-2012 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testpylosmenudialog.h"
//---------------------------------------------------------------------------
const About TestPylosMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestPylos",
    "tool to test the Pylos board classes",
    "the 29th of April 2012",
    "2010-2012",
    "http://www.richelbilderbeek.nl/ToolTestPylos.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}
//---------------------------------------------------------------------------
const std::string TestPylosMenuDialog::GetVersion()
{
  return "2.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> TestPylosMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-09-19: version 0.1: initial version: cannot move marbles, cannot switch to advanced game, winner can be requested clumsily (by clicking next to the Pylos widget)");
  v.push_back("2010-09-21: version 0.2: major architectural rewrite, PylosWidget now sends custom signals, due to which TestPylos can show more state");
  v.push_back("2010-09-21: version 0.3: user can switch between basic and advanced play, user can now move marbles to a higher level");
  v.push_back("2010-09-22: version 1.0: initial release version, allow PylosWidget resizing, allow visual random play, play many random virtual games at startup, keep track of move history");
  v.push_back("2010-09-22: version 1.1: modified PylosWidget to not display selector when somewon has won, added extra test");
  v.push_back("2010-09-22: version 1.2: if a marble is selected for movement to a higher layer, the left mouse button must be pressed. When a marble is selected for movement, no marble will be placed by clicking the left mouse button");
  v.push_back("2012-04-29: version 2.0: major architectural change. Seperated PylosGame from PylosBoard");
  return v;
}
//---------------------------------------------------------------------------

