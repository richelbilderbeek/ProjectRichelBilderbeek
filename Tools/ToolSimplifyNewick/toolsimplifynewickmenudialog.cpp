//---------------------------------------------------------------------------
/*
SimplifyNewick, tool to randomly simplify Newick phylogenies
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
//From http://www.richelbilderbeek.nl/ToolSimplifyNewick.htm
//---------------------------------------------------------------------------
#include "simplifynewickmenudialog.h"

#include <cassert>
#include <iostream>

#include "newickvector.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"

int ribi::ToolSimplifyNewickMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::ToolSimplifyNewickMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SimplifyNewick",
    "tool to randomly simplify Newick phylogenies",
    "the 19th of September 2013",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolSimplifyNewick.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("NewickVector version: " + NewickVector::GetVersion());
  return a;
}

ribi::Help ribi::ToolSimplifyNewickMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::ToolSimplifyNewickMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramSimplifyNewick
  };
  assert(p);
  return p;
}

std::string ribi::ToolSimplifyNewickMenuDialog::GetVersion() const noexcept
{
  return "3.1";
}

std::vector<std::string> ribi::ToolSimplifyNewickMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-09-12: version 1.0: initial version",
    "2010-09-16: version 1.1: use of BinaryNewickVector version 1.0, added library version numbers in About screen, added 'What's New?' dialog, added difference in debug and release version",
    "2010-09-16: version 1.2: simplification is frequency dependent. For example: (100,2) will be simplified to (99,2) 50x more often than to (100,1)",
    "2011-05-07: version 2.0: use NewickVector instead of BinaryNewickVector, replace custom about and whats new dialog by QtAboutDialog",
    "2013-09-19: version 3.0: conformized for ProjectRichelBilderbeek",
    "2013-11-05: version 3.1: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::ToolSimplifyNewickMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
