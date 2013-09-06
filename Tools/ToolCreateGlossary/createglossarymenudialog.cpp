//---------------------------------------------------------------------------
/*
CreateGlossary, tool to create my glossaries
Copyright (C) 2011-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateGlossary.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "createglossarymenudialog.h"

#include "htmlpage.h"

const ribi::About ribi::CreateGlossaryMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "CreateGlossary",
    "tool for creating my site's glossaries",
    "the 11th of August 2012",
    "2012",
    "http://www.richelbilderbeek.nl/ToolCreateGlossary.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("HtmlPage version: " + HtmlPage::GetVersion());
  return a;
}

const std::string ribi::CreateGlossaryMenuDialog::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> ribi::CreateGlossaryMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-xx-xx: version 1.0: initial version");
  v.push_back("2012-08-06: version 1.1: added the creation of more type of glossaries");
  v.push_back("2012-08-11: version 1.2: add desktop version");
  return v;
}

