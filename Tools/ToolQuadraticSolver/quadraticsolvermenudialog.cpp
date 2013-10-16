//---------------------------------------------------------------------------
/*
QuadraticSolver, solver of quadratic equations
Copyright (C) 2008-2013 Richel Bilderbeek

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

#include "trace.h"

const ribi::About ribi::QuadraticSolverMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "QuadraticSolver",
    "solver of quadratic equations",
    "the 1st of Oktober 2013",
    "2008-2013",
    "http://www.richelbilderbeek.nl/ToolQuadraticSolver.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::QuadraticSolverMenuDialog::GetVersion()
{
  return "2.1";
}

const std::vector<std::string> ribi::QuadraticSolverMenuDialog::GetVersionHistory()
{
  return {
    "2008-xx-xx: version 1.0: initial version in C++ Builder",
    "2013-08-26: version 2.0: port to Qt Creator, console version",
    "2013-10-01: version 2.1: added desktop version"
  };
}
