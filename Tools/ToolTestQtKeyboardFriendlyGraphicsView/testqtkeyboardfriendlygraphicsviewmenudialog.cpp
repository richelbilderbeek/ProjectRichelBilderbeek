//---------------------------------------------------------------------------
/*
TestKeyboardFriendlyGraphicsView, tests QtKeyboardFriendlyGraphicsView
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestKeyboardFriendlyGraphicsView.htm
//---------------------------------------------------------------------------
#include "testqtkeyboardfriendlygraphicsviewmenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

int ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestKeyboardFriendlyGraphicsView",
    "tests QtKeyboardFriendlyGraphicsView",
    "the 5th of November 2013",
    "2012-2015",
    "http://www.richelbilderbeek.nl/ToolTestKeyboardFriendlyGraphicsView.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestQtKeyboardFriendlyGraphicsView
  };
  assert(p);
  return p;
}

std::string ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::GetVersion() const noexcept
{
  return "0.4";
}

std::vector<std::string> ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-12-13: version 0.1: initial version",
    "2012-12-17: version 0.2: initial release, added about sceen, adding items, showing help",
    "2012-12-19: version 0.3: improved looks, added QtArrowItem, QtPathArrowItem, QtRoundedTextRect",
    "2013-11-05: version 0.4: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::TestKeyboardFriendlyGraphicsViewMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
