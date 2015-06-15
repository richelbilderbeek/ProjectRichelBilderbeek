//---------------------------------------------------------------------------
/*
TestTicTacToe, test the TicTacToe classes
Copyright (C) 2008-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/ToolTestTicTacToe.htm
//---------------------------------------------------------------------------
#include "testtictactoemenudialog.h"

#include <iostream>

#include "testtimer.h"
#include "trace.h"

#include "richelbilderbeekprogram.h"

ribi::TestTicTacToeMenuDialog::TestTicTacToeMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestTicTacToeMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 0;
}

ribi::About ribi::TestTicTacToeMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestTicTacToe",
    "tool to test the TicTacToe class",
    "the 15th of Oktober 2013",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestTicTacToe.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestTicTacToeMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestTicTacToeMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestTicTacToe
  };
  assert(p);
  return p;
}

std::string ribi::TestTicTacToeMenuDialog::GetVersion() const noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::TestTicTacToeMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-09-17: version 1.0: initial version, use of QTable as board",
    "2010-09-22: version 1.1: use of TicTacToeWidget",
    "2011-01-06: version 1.2: merge with Wt application",
    "2011-01-06: version 1.3: moved TicTacToe and QtTicTacToeWidget to different folders",
    "2013-10-14: version 1.4: conformized to ProjectRichelBilderbeek"
  };
}

#ifndef NDEBUG
void ribi::TestTicTacToeMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
