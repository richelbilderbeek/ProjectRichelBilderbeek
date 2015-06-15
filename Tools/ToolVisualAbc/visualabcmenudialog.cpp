//---------------------------------------------------------------------------
/*
Visual ABC, visual ABC editor
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolVisualAbc.htm
//---------------------------------------------------------------------------
#include "visualabcmenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::VisualAbcMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::VisualAbcMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Visual ABC",
    "visual ABC editor",
    "the 5th of May 2011",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolVisualAbc.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  //a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  return a;
}

ribi::Help ribi::VisualAbcMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::VisualAbcMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramVisualAbc
  };
  assert(p);
  return p;
}

std::string ribi::VisualAbcMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::VisualAbcMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-05-01: Version 1.0: initial version",
    "2011-05-01: Version 1.1: added button to save ABC text"
  };
}

#ifndef NDEBUG
void ribi::VisualAbcMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
