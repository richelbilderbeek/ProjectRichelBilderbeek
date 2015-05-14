#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <iostream>
#include <limits>

#include <boost/numeric/conversion/bounds.hpp>
#pragma GCC diagnostic pop

///GetSmallestFloat returns the smallest possible value of a float.
///From http://www.richelbilderbeek.nl/CppGetSmallestFloat.htm
float GetSmallestFloatStl()
{
  return std::numeric_limits<float>::min();
}

///GetSmallestFloat returns the smallest possible value of a float.
///From http://www.richelbilderbeek.nl/CppGetSmallestFloat.htm
float GetSmallestFloatBoost()
{
  return boost::numeric::bounds<float>::smallest();
}

int main()
{
  assert(GetSmallestFloatStl() == GetSmallestFloatBoost());
  std::cout
    << GetSmallestFloatBoost() << '\n'
    << GetSmallestFloatStl() << std::endl
  ;
}

/*

1.17549e-38
1.17549e-38
Press <RETURN> to close this window...

*/
