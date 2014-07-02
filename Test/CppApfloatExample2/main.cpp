#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "apfloat.h"
#pragma GCC diagnostic pop

double ToDouble(const apfloat& a)
{
  std::stringstream s;
  s << a;
  double x = boost::lexical_cast<double>(s.str());
  return x;
}

int main()
{
  const apfloat x = 1.0;
  const double y = ToDouble(x);
  const apfloat z = x;
  assert(y == z);
  std::cout
    << x << '\n'
    << y << '\n'
    << z << '\n'
  ;
}

/* Screen output

0.000000001e9
1
0.000000001e9
Press <RETURN> to close this window...

*/
