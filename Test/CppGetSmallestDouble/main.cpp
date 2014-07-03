#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <iostream>
#include <limits>

#include <boost/numeric/conversion/bounds.hpp>
#pragma GCC diagnostic pop

///GetSmallestDouble returns the smallest possible value of a double.
///From http://www.richelbilderbeek.nl/CppGetSmallestDouble.htm
double GetSmallestDoubleStl()
{
  return std::numeric_limits<double>::min();
}

///GetSmallestDouble returns the smallest possible value of a double.
///From http://www.richelbilderbeek.nl/CppGetSmallestDouble.htm
double GetSmallestDoubleBoost()
{
  return boost::numeric::bounds<double>::smallest();
}

int main()
{
  assert(GetSmallestDoubleStl() == GetSmallestDoubleBoost());
  std::cout
    << GetSmallestDoubleBoost() << '\n'
    << GetSmallestDoubleStl() << std::endl
  ;
}

/*

2.22507e-308
2.22507e-308
Press <RETURN> to close this window...

*/
