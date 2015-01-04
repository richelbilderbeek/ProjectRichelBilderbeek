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
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/ToolQuadraticSolver.htm
//---------------------------------------------------------------------------
#ifndef QUADRATICSOLVERMAINDIALOG_H
#define QUADRATICSOLVERMAINDIALOG_H

#include <string>
#include <vector>

namespace ribi {

struct QuadraticSolverMainDialog
{
  QuadraticSolverMainDialog();

  void Execute() const noexcept;

  ///Calculates all solutions from the quadratic equation,
  ///y = a.x.x + b.x + c
  ///From http://www.richelbilderbeek.nl/CppSolveQuadratic.htm
  static const std::vector<double> SolveQuadratic(
    const double a, const double b, const double c);

  private:
  //From http://www.richelbilderbeek.nl/CppAskUserForString.htm
  static std::string AskUserForString() noexcept;

  //From http://www.richelbilderbeek.nl/CppAskUserForDouble.htm
  static double AskUserForDouble() noexcept;

  //From http://www.richelbilderbeek.nl/CppIsDouble.htm
  static bool IsDouble(const std::string& s) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QUADRATICSOLVERMAINDIALOG_H
