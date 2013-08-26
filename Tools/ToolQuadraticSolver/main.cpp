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
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "quadraticsolvermaindialog.h"
#include "quadraticsolvermenudialog.h"

#pragma GCC diagnostic pop


//From http://www.richelbilderbeek.nl/CppAskUserForString.htm
const std::string AskUserForString()
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}

//From http://www.richelbilderbeek.nl/CppIsDouble.htm
bool IsDouble(const std::string& s)
{
  std::istringstream i(s);
  double temp;
  return ( (i >> temp) ? true : false );
}

//From http://www.richelbilderbeek.nl/CppAskUserForDouble.htm
double AskUserForDouble()
{
  while (1)
  {
    const std::string s = AskUserForString();
    if (IsDouble(s)==false) continue;
    return boost::lexical_cast<double>(s);
  }
}

int main()
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
    const std::vector<double> v = QuadraticSolverMainDialog::SolveQuadratic(a,b,c);
    std::copy(v.begin(),v.end(),std::ostream_iterator<double>(std::cout," "));
    if (v.empty()==true)
      std::cout << "None..." << std::endl;
    else
      std::cout << std::endl;
    std::cout << "Type 'q' to quit, anything else to continue." << std::endl;
    const std::string quit = AskUserForString();
    if (quit == "q" || quit == "Q") break;
  }

  for (const std::string& s: QuadraticSolverMenuDialog::GetAbout().CreateAboutText())
  {
    std::cout << s << '\n';
  }
  std::cout << std::endl;
  for (const std::string& s: QuadraticSolverMenuDialog::GetAbout().CreateLicenceText())
  {
    std::cout << s << '\n';
  }
}

