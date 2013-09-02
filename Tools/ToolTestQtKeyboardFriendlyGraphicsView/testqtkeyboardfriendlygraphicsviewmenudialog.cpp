//---------------------------------------------------------------------------
/*
TestKeyboardFriendlyGraphicsView, tests QtKeyboardFriendlyGraphicsView
Copyright (C) 2012  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestKeyboardFriendlyGraphicsView.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testqtkeyboardfriendlygraphicsviewmenudialog.h"

#include "trace.h"

const About TestKeyboardFriendlyGraphicsViewMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestKeyboardFriendlyGraphicsView",
    "tests QtKeyboardFriendlyGraphicsView",
    "the 19th of December 2012",
    "2012",
    "http://www.richelbilderbeek.nl/ToolTestKeyboardFriendlyGraphicsView.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string TestKeyboardFriendlyGraphicsViewMenuDialog::GetVersion()
{
  return "0.3";
}

const std::vector<std::string> TestKeyboardFriendlyGraphicsViewMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-13: version 0.1: initial version");
  v.push_back("2012-12-17: version 0.2: initial release, added about sceen, adding items, showing help");
  v.push_back("2012-12-19: version 0.3: improved looks, added QtArrowItem, QtPathArrowItem, QtRoundedTextRect");
  return v;
}

