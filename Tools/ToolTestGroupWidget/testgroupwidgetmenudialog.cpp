//---------------------------------------------------------------------------
/*
TestGroupWidget, tool to test the GroupWidget class
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
//From http://www.richelbilderbeek.nl/ToolTestGroupWidget.htm
//---------------------------------------------------------------------------
#include "testgroupwidgetmenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::TestGroupWidgetMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestGroupWidgetMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestGroupWidget",
    "tool to test the (Wt)GroupWidget class",
    "the 8th of September 2011",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestGroupWidget.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}

ribi::Help ribi::TestGroupWidgetMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestGroupWidgetMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestGroupWidget
  };
  assert(p);
  return p;
}

std::string ribi::TestGroupWidgetMenuDialog::GetVersion() const noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::TestGroupWidgetMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-06-16: Version 1.0: initial version",
    "2011-06-26: Version 1.1: replaced Wt::WTimer by WtSafeTimer",
    "2011-06-30: Version 1.2: replaced WtSafeTimer by Wt::WPushButton",
    "2011-09-08: Version 1.3: added edit in website version",
    "2013-11-05: version 1.4: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::TestGroupWidgetMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
