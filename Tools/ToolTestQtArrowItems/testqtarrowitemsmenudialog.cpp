// ---------------------------------------------------------------------------
/*
TestQtArrowItems, tool to test Qt arrow QGraphicsItems
Copyright (C) 2012-2013  Richel Bilderbeek

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
// ---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestQtArrowItems.htm
// ---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testqtarrowitemsmenudialog.h"

#include "trace.h"

const About TestQtArrowItemsMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestQtArrowItems",
    "tool to test Qt arrow QGraphicsItems",
    "the 1st of Januari 2013",
    "2012-2013",
    "http://www.richelbilderbeek.nl/ToolTestQtArrowItems.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string TestQtArrowItemsMenuDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> TestQtArrowItemsMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-07: version 0.1: initial version");
  v.push_back("2013-01-01: version 1.0: added menu");
  return v;
}

