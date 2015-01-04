//---------------------------------------------------------------------------
/*
QuadraticSolver, solver of quadratic equations
Copyright (C) 2008-2015 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolQuadraticSolver.htm
//---------------------------------------------------------------------------
#include "quadraticsolvermenudialog.h"

#include "quadraticsolvermaindialog.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

int ribi::QuadraticSolverMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    QuadraticSolverMainDialog d;
    d.Execute();
    return 0;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::QuadraticSolverMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "QuadraticSolver",
    "solver of quadratic equations",
    "the 2nd of January 2015",
    "2008-2015",
    "http://www.richelbilderbeek.nl/ToolQuadraticSolver.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::QuadraticSolverMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::QuadraticSolverMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramQuadraticSolver
  };
  assert(p);
  return p;
}

std::string ribi::QuadraticSolverMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

std::vector<std::string> ribi::QuadraticSolverMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2008-xx-xx: version 1.0: initial version in C++ Builder",
    "2013-08-26: version 2.0: port to Qt Creator, console version",
    "2013-10-01: version 2.1: added desktop version",
    "2015-01-02: version 2.2: added picture of equation to desktop version"
  };
}

#ifndef NDEBUG
void ribi::QuadraticSolverMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
