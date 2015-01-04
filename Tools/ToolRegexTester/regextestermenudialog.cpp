//---------------------------------------------------------------------------
/*
RegexTester, regular expression tester
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
//From http://www.richelbilderbeek.nl/ToolRegexTester.htm
//---------------------------------------------------------------------------
#include "regextestermenudialog.h"

#include <cassert>
#include <iostream>

#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"

int ribi::RegexTesterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::RegexTesterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "RegexTester",
    "regular expression tester",
    "the 16th of July 2013",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolRegexTester.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}

ribi::Help ribi::RegexTesterMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::RegexTesterMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramRegexTester
  };
  assert(p);
  return p;
}

std::string ribi::RegexTesterMenuDialog::GetVersion() const noexcept
{
  return "1.7";
}

std::vector<std::string> ribi::RegexTesterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-08-19: Version 1.3: Qt GUI application",
    "2012-01-07: Version 1.4: port to Wt and console application",
    "2012-09-24: Version 1.5: added Qt and C++11 versions",
    "2013-03-20: Version 1.6: added TR1 version, added replace",
    "2013-07-16: Version 1.7: added Boost.Xpressive"
  };
}

#ifndef NDEBUG
void ribi::RegexTesterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
