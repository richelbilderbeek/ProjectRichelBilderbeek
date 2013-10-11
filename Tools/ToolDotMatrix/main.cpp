#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include "dotmatrix.h"
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

  for (const char c: s)
  {
    ribi::DotMatrix m(c);
    std::cout << m << '\n';
  }
}

/* Example screen output:

10001
10001
10001
11111
10001
10001
10001
00000
00000
01110
10001
11111
10000
01110
01100
00100
00100
00100
00100
00100
01110
01100
00100
00100
00100
00100
00100
01110
00000
00000
01110
10001
10001
10001
01110

*/
