#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <iostream>
#include <limits>

#include <boost/numeric/conversion/bounds.hpp>
#pragma GCC diagnostic pop

///GetMaxFloat returns the highest possible value of a float.
///From http://www.richelbilderbeek.nl/CppGetMaxFloat.htm
float GetMaxFloatStl()
{
  return std::numeric_limits<float>::max();
}

///GetMaxFloat returns the highest possible value of a float.
///From http://www.richelbilderbeek.nl/CppGetMaxFloat.htm
float GetMaxFloatBoost()
{
  return boost::numeric::bounds<float>::highest();
}

int main()
{
  assert(GetMaxFloatStl() == GetMaxFloatBoost());
  std::cout
    << GetMaxFloatBoost() << '\n'
    << GetMaxFloatStl() << std::endl
  ;
}

/*

3.40282e+38
3.40282e+38
Press <RETURN> to close this window...

*/
