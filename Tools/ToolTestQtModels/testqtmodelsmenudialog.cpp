//---------------------------------------------------------------------------
/*
TestQtModels, tool to test the QtModel classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtModels.htm
//---------------------------------------------------------------------------
#include "testqtmodelsmenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

ribi::ToolTestQtModelsMenuDialog::ToolTestQtModelsMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::ToolTestQtModelsMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::ToolTestQtModelsMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestQtModels",
    "tool to test the QtModel classes",
    "the 27th of June 2013",
    "2013-2015",
    "http://www.richelbilderbeek.nl/ToolTestQtModels.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::ToolTestQtModelsMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::ToolTestQtModelsMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestQtModels
  };
  assert(p);
  return p;
}

std::string ribi::ToolTestQtModelsMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::ToolTestQtModelsMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-05-15: version 1.0: initial version",
    "2013-06-27: version 1.1: added QtUblasVectorIntModel",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::ToolTestQtModelsMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
