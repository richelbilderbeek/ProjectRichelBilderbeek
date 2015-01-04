//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#include "testpylosmenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::TestPylosMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestPylosMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestPylos",
    "tool to test the Pylos board classes",
    "the 29th of April 2012",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolTestPylos.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

ribi::Help ribi::TestPylosMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestPylosMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestPylos
  };
  assert(p);
  return p;
}

std::string ribi::TestPylosMenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::TestPylosMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-09-19: version 0.1: initial version: cannot move marbles, cannot switch to advanced game, winner can be requested clumsily (by clicking next to the Pylos widget)",
    "2010-09-21: version 0.2: major architectural rewrite, PylosWidget now sends custom signals, due to which TestPylos can show more state",
    "2010-09-21: version 0.3: user can switch between basic and advanced play, user can now move marbles to a higher level",
    "2010-09-22: version 1.0: initial release version, allow PylosWidget resizing, allow visual random play, play many random virtual games at startup, keep track of move history",
    "2010-09-22: version 1.1: modified PylosWidget to not display selector when somewon has won, added extra test",
    "2010-09-22: version 1.2: if a marble is selected for movement to a higher layer, the left mouse button must be pressed. When a marble is selected for movement, no marble will be placed by clicking the left mouse button"
    "2012-04-29: version 2.0: major architectural change. Seperated PylosGame from PylosBoard",
    "2013-11-05: version 2.1: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::TestPylosMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
