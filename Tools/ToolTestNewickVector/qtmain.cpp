//---------------------------------------------------------------------------
/*
TestNewickVector, GUI tool to test NewickVector
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestNewickVector.htm
//---------------------------------------------------------------------------

/// \mainpage TestNewickVector documentation
///
/// TestNewickVector, GUI tool to test NewickVector
///
/// Copyright (C) 2010 Richel Bilderbeek\n
/// programmed at the 4th September of 2010\n
/// From http://www.richelbilderbeek.nl/ToolTestTwoNewickVector.htm\n
/// Licenced under GPL 3.0\n
///
/// \author  Richel Bilderbeek
/// \version 2.0
/// \date    2011-02-21
///

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <iomanip>
#include <QApplication>
#include "qttestnewickvectordialog.h"
#include "newick.h"
#include "newickvector.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    QApplication a(argc, argv);
    ribi::QtTestNewickVectorDialog w;
    w.show();
    return a.exec();
  }
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
      << "  \'" << argv[0] << " (2,(2,2)) " << (5.0 / 2.0) << "\'";
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
  const double p = ribi::NewickVector::CalculateProbability(newick,theta);
  std::cout << std::setprecision(99) << p << '\n';
  return 0; //To satisfy the compiler
}
