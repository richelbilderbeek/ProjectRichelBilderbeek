#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <string>
#include <boost/lexical_cast.hpp>
#include "apfloat.h"
#pragma GCC diagnostic pop

//Uses C++98
std::string ToStr(const apfloat& a)
{
  std::stringstream s;
  s << a;
  return s.str();
}

//Uses apfloat and C++98
std::string ToStrApfloat(const apfloat& a)
{
  std::stringstream s;
  s << pretty << a;
  return s.str();
}

int main()
{
  const double x{12.34};
  const apfloat y(x);
  const std::string a{ToStr(y)};
  const std::string b{ToStrApfloat(y)};
  std::cout
     << a << '\n'
     << b << '\n'
   ;
}

/* Screen output:

0.000000012339999999999999880e9
12.339999999999999880

*/
