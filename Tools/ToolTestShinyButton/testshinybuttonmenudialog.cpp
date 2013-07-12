//---------------------------------------------------------------------------
/*
TestShinyButton, tool to test the ShinyButton class
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
//From http://www.richelbilderbeek.nl/ToolTestShinyButton.htm
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
#include "testshinybuttonmenudialog.h"

#include "rainbow.h"
#include "rectangle.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "trace.h"
//---------------------------------------------------------------------------
const About TestShinyButtonMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestShinyButton",
    "tool to test the ShinyButton class",
    "the 13th of February 2012",
    "2011-2012",
    "http://www.richelbilderbeek.nl/ToolTestShinyButton.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  a.AddLibrary("Rectangle version: " + Rect::GetVersion());
  a.AddLibrary("ShinyButton version: " + ShinyButton::GetVersion());
  a.AddLibrary("ShinyButtonWidget version: " + ShinyButtonWidget::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}
//---------------------------------------------------------------------------
const std::string TestShinyButtonMenuDialog::GetVersion()
{
  return "2.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> TestShinyButtonMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-16: Version 1.0: initial version, desktop version not yet working");
  v.push_back("2011-06-31: Version 1.1: added more tests and an image to the Welcome screen in website version");
  v.push_back("2012-02-13: Version 2.0: created a desktop version of TestShinyButton");
  return v;
}
//---------------------------------------------------------------------------
