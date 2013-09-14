//---------------------------------------------------------------------------
/*
TestQtRoundedTextRectItem, tool to test QtRoundedTextRectItem
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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedTextRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testqtroundedtextrectitemmenudialog.h"

#include "trace.h"
#pragma GCC diagnostic pop

const ribi::About ribi::TestQtRoundedTextRectItemMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestQtRoundedTextRectItemWidget",
    "tests QtRoundedTextRectItemWidget",
    "the 31st of December 2012",
    "2012",
    "http://www.richelbilderbeek.nl/ToolTestQtRoundedTextRectItemWidget.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::TestQtRoundedTextRectItemMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::TestQtRoundedTextRectItemMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-21: version 1.0: initial version");
  v.push_back("2012-12-31: version 1.1: added menu");
  return v;
}

