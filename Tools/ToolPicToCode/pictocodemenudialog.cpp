//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------


#include "pictocodemenudialog.h"
//---------------------------------------------------------------------------
const ribi::About ribi::PicToCodeMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "PicToCode",
    "tool to convert a picture to C++ code",
    "the 18th of April 2011",
    "2010-2011",
    "http://www.richelbilderbeek.nl/ToolPicToCode.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("PicToCode version: " + PicToCode::GetVersion());
  return a;
}
//---------------------------------------------------------------------------
const std::string ribi::PicToCodeMenuDialog::GetVersion()
{
  return "1.3";
}
//---------------------------------------------------------------------------
const std::vector<std::string> ribi::PicToCodeMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-10-10: version 1.0: initial version");
  v.push_back("2010-10-11: version 1.1: added tranparency support");
  v.push_back("2011-04-18: version 1.2: added support for QPixmap");
  v.push_back("2011-04-18: version 1.3: added menu, added web application");
  return v;
}
//---------------------------------------------------------------------------
