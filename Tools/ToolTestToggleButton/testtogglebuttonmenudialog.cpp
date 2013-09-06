//---------------------------------------------------------------------------
/*
TestToggleButton, tool to test the ToggleButton class
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
//From http://www.richelbilderbeek.nl/ToolTestToggleButton.htm
//---------------------------------------------------------------------------


#include "testtogglebuttonmenudialog.h"

#include "rectangle.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"

const About TestToggleButtonMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestToggleButton",
    "tool to test the ToggleButton class",
    "the 11st of June 2012",
    "2011-2012",
    "http://www.richelbilderbeek.nl/ToolTestToggleButton.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Rectangle version: " + Rect::GetVersion());
  a.AddLibrary("ToggleButton version: " + ToggleButton::GetVersion());
  a.AddLibrary("ToggleButtonWidget version: " + ToggleButtonWidget::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}

const std::string TestToggleButtonMenuDialog::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> TestToggleButtonMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-16: Version 1.0: initial version, desktop version not yet working");
  v.push_back("2011-06-31: Version 1.1: added more tests and an image to the Welcome screen in website version");
  v.push_back("2012-06-21: Version 1.2: added desktop version");
  return v;
}

