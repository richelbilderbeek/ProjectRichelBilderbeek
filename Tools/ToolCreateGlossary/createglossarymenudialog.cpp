//---------------------------------------------------------------------------
/*
CreateGlossary, tool to create my glossaries
Copyright (C) 2011-2014 Richel Bilderbeek

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

#include "createglossarymaindialog.h"
#include "htmlpage.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"

ribi::CreateGlossaryMenuDialog::CreateGlossaryMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::CreateGlossaryMenuDialog::ExecuteSpecific(const std::vector<std::string>&) noexcept
{
  //Just create the glossaries, whatever the input was
  CreateGlossaryMainDialog();
  return 0;
}

ribi::About ribi::CreateGlossaryMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "CreateGlossary",
    "tool for creating my site's glossaries",
    "the 11th of August 2012",
    "2012-2014",
    "http://www.richelbilderbeek.nl/ToolCreateGlossary.htm",
    GetVersion(),
    GetVersionHistory()
  );

  a.AddLibrary("HtmlPage version: " + HtmlPage::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::CreateGlossaryMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      //Options
    },
    {
      //Example uses
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::CreateGlossaryMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramCreateGlossary
  };
  assert(p);
  return p;
}

std::string ribi::CreateGlossaryMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::CreateGlossaryMenuDialog::GetVersionHistory() const noexcept
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
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  CreateGlossaryMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
