#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <iostream>
#include <limits>

#include <boost/numeric/conversion/bounds.hpp>
#pragma GCC diagnostic pop

///GetMaxDouble returns the highest possible value of a double.
///From http://www.richelbilderbeek.nl/CppGetMaxDouble.htm
double GetMaxDoubleStl()
{
  return std::numeric_limits<double>::max();
}

///GetMaxDouble returns the highest possible value of a double.
///From http://www.richelbilderbeek.nl/CppGetMaxDouble.htm
double GetMaxDoubleBoost()
{
  return boost::numeric::bounds<double>::highest();
}

int main()
{
  assert(GetMaxDoubleStl() == GetMaxDoubleBoost());
  std::cout
    << GetMaxDoubleBoost() << '\n'
    << GetMaxDoubleStl() << std::endl
  ;
}

/*

1.79769e+308
1.79769e+308
Press <RETURN> to close this window...

*/
