//---------------------------------------------------------------------------
/*
TestShinyButton, tool to test the ShinyButton class
Copyright (C) 2011-2015 Richel Bilderbeek

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
#include "testshinybuttonmenudialog.h"

#include <cassert>
#include <iostream>

#include "rainbow.h"
#include "richelbilderbeekprogram.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "testtimer.h"
#include "trace.h"

int ribi::TestShinyButtonMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::TestShinyButtonMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestShinyButton",
    "tool to test the ShinyButton class",
    "the 13th of February 2012",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestShinyButton.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  a.AddLibrary("ShinyButton version: " + ShinyButton::GetVersion());
  a.AddLibrary("ShinyButtonWidget version: " + ShinyButtonWidget::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}

ribi::Help ribi::TestShinyButtonMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestShinyButtonMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestShinyButton
  };
  assert(p);
  return p;
}

std::string ribi::TestShinyButtonMenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::TestShinyButtonMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-06-16: Version 1.0: initial version, desktop version not yet working",
    "2011-06-31: Version 1.1: added more tests and an image to the Welcome screen in website version",
    "2012-02-13: Version 2.0: created a desktop version of TestShinyButton",
    "2013-11-05: version 2.1: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::TestShinyButtonMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
