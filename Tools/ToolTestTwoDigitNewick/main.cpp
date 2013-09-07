//---------------------------------------------------------------------------
/*
TestTwoDigitNewick, tool to test the two-digit-Newick architecture
Copyright (C) 2010-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick.htm
//---------------------------------------------------------------------------
#include <iomanip>
#include <iostream>

#include "newick.h"
#include "twodigitnewick.h"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout
      << "Incorrect number of arguments:\n"
      << '\n'
      << "No arguments: start GUI version:\n"
      << "  " << argv[0] << '\n'
      << "Two arguments: start command-line version:\n"
      << "  - newick\n"
      << "  - theta\n"
      << "  \'" << argv[0] << " (2,(2,2)) " << (5.0 / 2.0) << "\'\n";
    return 1;
  }
  const std::string newick = argv[1];
  if (!ribi::Newick::IsNewick(newick))
  {
    std::cout
      << "Invalid Newick format. Use for example:\n"
      << "  \'" << argv[0] << " (2,(2,2)) " << (5.0 / 2.0) << "\'\n";
    return 1;
  }
  try
  {
    boost::lexical_cast<double>(argv[2]);
  }
  catch (boost::bad_lexical_cast&)
  {
    std::cout
      << "Invalid theta format. Use for example:\n"
      << "  \'" << argv[0] << " (2,(2,2)) " << (5.0 / 2.0) << "\'\n";
    return 1;

  }
  const double theta = boost::lexical_cast<double>(argv[2]);
  const double p = ribi::TwoDigitNewick::CalculateProbability(newick,theta);
  std::cout << std::setprecision(99) << p << '\n';
}
