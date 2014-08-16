#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <iostream>
#include <limits>

#include <boost/numeric/conversion/bounds.hpp>
#pragma GCC diagnostic pop

///GetMaxInt returns the highest possible value of a int.
///From http://www.richelbilderbeek.nl/CppGetMaxInt.htm
int GetMaxIntStl()
{
  return std::numeric_limits<int>::max();
}

///GetMaxInt returns the highest possible value of a int.
///From http://www.richelbilderbeek.nl/CppGetMaxInt.htm
int GetMaxIntBoost()
{
  return boost::numeric::bounds<int>::highest();
}

int main()
{
  assert(GetMaxIntStl() == GetMaxIntBoost());
  std::cout
    << GetMaxIntBoost() << '\n'
    << GetMaxIntStl() << std::endl
  ;
}

/*

2147483647
2147483647
Press <RETURN> to close this window...

*/
