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
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/ToolQuadraticSolver.htm
//---------------------------------------------------------------------------
#include "quadraticsolvermaindialog.h"

#include <cmath>

const std::vector<double> ribi::QuadraticSolverMainDialog::SolveQuadratic(
  const double a, const double b, const double c)
{
  if (a == 0.0)
  {
    if (b == 0.0)
      return std::vector<double>(1,0.0);
    else
      return std::vector<double>(1,c/b);
  }
  const double d = (b * b) - (4.0 * a * c);
  if (d < 0.0)
    return std::vector<double>();
  if (d == 0.0)
    return std::vector<double>(1,-b/(2.0*a));
  const double rD = std::sqrt(d);
  std::vector<double> solutions;
  solutions.reserve(2);
  solutions.push_back((-b + rD)/(2.0 * a));
  solutions.push_back((-b - rD)/(2.0 * a));
  return solutions;
}
