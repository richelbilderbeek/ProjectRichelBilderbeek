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
#include "createglossarymenudialog.h"

#include <cassert>

#include "htmlpage.h"
#include "trace.h"

const ribi::About ribi::CreateGlossaryMenuDialog::GetAbout() noexcept
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

const std::string ribi::CreateGlossaryMenuDialog::GetVersion() noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::CreateGlossaryMenuDialog::GetVersionHistory() noexcept
{
  return {
    "2011-xx-xx: version 1.0: initial version",
    "2012-08-06: version 1.1: added the creation of more type of glossaries",
    "2012-08-11: version 1.2: add desktop version"
  };
}

#ifndef NDEBUG
void ribi::CreateGlossaryMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::CreateGlossaryMenuDialog::Test()");
  CreateGlossaryMenuDialog().Execute( { "Hometrainer", "-e" } );
  const CreateGlossaryMainDialog d(HometrainerResources().GetExerciseClouds());
  assert(d.GetNumberCorrect() == 0);
  TRACE("Finished ribi::CreateGlossaryMenuDialog::Test()");
}
#endif
