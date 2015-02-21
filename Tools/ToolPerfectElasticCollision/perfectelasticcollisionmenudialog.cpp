//---------------------------------------------------------------------------
/*
PerfectElasticCollision, tool to investigate a perfect elastic collision
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
//From hhtp://www.richelbilderbeek.nl/ToolPerfectElasticCollision.htm
//---------------------------------------------------------------------------
#include "perfectelasticcollisionmenudialog.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

int ribi::PerfectElasticCollisionMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << this->GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::PerfectElasticCollisionMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PerfectElasticCollision",
    "tool to investigate a perfect elastic collision",
    "the 7th of March 2012",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolPerfectElasticCollision.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::PerfectElasticCollisionMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::PerfectElasticCollisionMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramPerfectElasticCollision
  };
  assert(p);
  return p;
}

std::string ribi::PerfectElasticCollisionMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::PerfectElasticCollisionMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-08-14: version 1.0: initial version",
    "2012-03-07: version 1.1: added versioning. Added menu screen",
    "2013-11-04: version 1.2: conformized to ProjectRichelBilderbeekConsole",
  };
}


#ifndef NDEBUG
void ribi::PerfectElasticCollisionMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
