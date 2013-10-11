#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "dotmatrixstring.h"
#include "tooldotmatrixmenudialog.h"

#pragma GCC diagnostic pop


//From http://www.richelbilderbeek.nl/CppAskUserForString.htm
const std::string AskUserForString()
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout
      << "Please supply a single input argument,\n"
      << "\n"
      << "for example:\n"
      << "\n"
      << "  " << argv[0] << " \"Hello World\"\n"
      << "\n"
      << std::endl;
    return 1;
  }

  const std::string s = argv[1];
  const int spacing = 1;

  boost::shared_ptr<ribi::DotMatrixString> m {
    new ribi::DotMatrixString(s,spacing)
  };
  std::cout << *m << '\n';
}

/* Example screen output:

100010000000011000011000000000
100010000000001000001000000000
100010011100001000001000011100
111110100010001000001000100010
100010111110001000001000100010
100010100000001000001000100010
100010011100011100011100011100
000000000000000000000000000000

*/
