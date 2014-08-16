//---------------------------------------------------------------------------
/*
  QuadraticSolver, solver of quadratic equations
  Copyright (C) 2008  Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppQuadraticSolver.htm
//---------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <cmath>
#include <string>
#include <iterator>

//Gives harmless warnings when you work with the Borland compiler
//BCC32.EXE version 6.0.10.157. When a more recent compiler is
//used, the warning will probably not occur anymore.
#pragma warn -8041
#include <boost/lexical_cast.hpp>
#pragma warn +8041

#pragma hdrstop
//---------------------------------------------------------------------------
#pragma argsused
//---------------------------------------------------------------------------
void ShowLicence()
{
  std::cout
    << "QuadraticSolver, solver of quadratic equations" << std::endl
    << "Copyright (C) 2008  Richel Bilderbeek" << std::endl
    << std::endl
    << "This program is free software: you can redistribute it and/or modify" << std::endl
    << "it under the terms of the GNU General Public License as published by" << std::endl
    << "the Free Software Foundation, either version 3 of the License, or" << std::endl
    << "(at your option) any later version." << std::endl
    << std::endl
    << "This program is distributed in the hope that it will be useful," << std::endl
    << "but WITHOUT ANY WARRANTY without even the implied warranty of" << std::endl
    << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl
    << "GNU General Public License for more details." << std::endl
    << "You should have received a copy of the GNU General Public License" << std::endl
    << "along with this program.  If not, see <http://www.gnu.org/licenses/>." << std::endl
    << std::endl
    << "Programmed at the 12th July of 2008 by Richel Bilderbeek" << std::endl
    << "From http://www.richelbilderbeek.nl" << std::endl
    << std::endl
    << std::endl;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppSolveQuadratic.htm
const std::vector<double> SolveQuadratic(const double a, const double b, const double c)
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppAskUserForString.htm
const std::string AskUserForString()
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppIsDouble.htm
const bool IsDouble(const std::string& s)
{
  std::istringstream i(s);
  double temp;
  return ( (i >> temp) ? true : false );
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppAskUserForDouble.htm
const double AskUserForDouble()
{
  while (1)
  {
    const std::string s = AskUserForString();
    if (IsDouble(s)==false) continue;
    return boost::lexical_cast<double>(s);
  }
}
//---------------------------------------------------------------------------
int main()
{
  ShowLicence();

  while (1)
  {
    std::cout << "Please enter a value for a" << std::endl;
    const double a = AskUserForDouble();
    std::cout << "Please enter a value for b" << std::endl;
    const double b = AskUserForDouble();
    std::cout << "Please enter a value for c" << std::endl;
    const double c = AskUserForDouble();
    std::cout << "Solutions of this quadratic equations are:" << std::endl;
    const std::vector<double> v = SolveQuadratic(a,b,c);
    std::copy(v.begin(),v.end(),std::ostream_iterator<double>(std::cout," "));
    if (v.empty()==true)
      std::cout << "None..." << std::endl;
    else
      std::cout << std::endl;
    std::cout << "Type 'q' to quit, anything else to continue." << std::endl;
    const std::string quit = AskUserForString();
    if (quit == "q" || quit == "Q") break;
  }

  ShowLicence();
}
//---------------------------------------------------------------------------
