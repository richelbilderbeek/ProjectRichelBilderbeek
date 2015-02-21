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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "quadraticsolvermaindialog.h"

#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::QuadraticSolverMainDialog::QuadraticSolverMainDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::QuadraticSolverMainDialog::AskUserForString() noexcept
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}

double ribi::QuadraticSolverMainDialog::AskUserForDouble() noexcept
{
  while (1)
  {
    const std::string s = AskUserForString();
    if (IsDouble(s)==false) continue;
    return boost::lexical_cast<double>(s);
  }
}

void ribi::QuadraticSolverMainDialog::Execute() const noexcept
{
  while (1)
  {
    std::cout << "Please enter a value for a" << std::endl;
    const double a = AskUserForDouble();
    std::cout << "Please enter a value for b" << std::endl;
    const double b = AskUserForDouble();
    std::cout << "Please enter a value for c" << std::endl;
    const double c = AskUserForDouble();
    std::cout << "Solutions of this quadratic equations are:" << std::endl;
    const std::vector<double> v = ribi::QuadraticSolverMainDialog::SolveQuadratic(a,b,c);
    std::copy(v.begin(),v.end(),std::ostream_iterator<double>(std::cout," "));
    if (v.empty()==true)
      std::cout << "None..." << std::endl;
    else
      std::cout << std::endl;
    std::cout << "Type 'q' to quit, anything else to continue." << std::endl;
    const std::string quit = AskUserForString();
    if (quit == "q" || quit == "Q") break;
  }
}

bool ribi::QuadraticSolverMainDialog::IsDouble(const std::string& s) noexcept
{
  std::istringstream i(s);
  double temp;
  return ( (i >> temp) ? true : false );
}

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

#ifndef NDEBUG
void ribi::QuadraticSolverMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
