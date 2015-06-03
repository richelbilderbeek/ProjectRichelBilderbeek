#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <string>
#include <iomanip>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "apfloat.h"
#pragma GCC diagnostic pop

//Uses C++98
double ToDoubleCpp98(const apfloat& a)
{
  std::stringstream s;
  s << a;
  double x;
  s >> x;
  return x;
}

//Uses apfloat and C++98
double ToDoubleApfloatCpp98(const apfloat& a)
{
  return ap2double(a.ap);
}

//Uses Boost and C++98
double ToDoubleBoostCpp98(const apfloat& a)
{
  std::stringstream s;
  s << a;
  return boost::lexical_cast<double>(s.str());
}

//Uses C++11
double ToDoubleCpp11(const apfloat& a)
{
  std::stringstream s;
  s << a;
  return std::stod(s.str());
}

int main()
{
  {
    const double x{12.34};
    const apfloat y(x);
    const double a{ToDoubleCpp98(y)};
    const double b{ToDoubleApfloatCpp98(y)};
    const double c{ToDoubleBoostCpp98(y)};
    const double d{ToDoubleCpp11(y)};
    assert(a == x);
    assert(b == x);
    assert(c == x);
    assert(d == x);
  }
  {
    const double x{4818656.433841671999999998};
    const apfloat y(x);
    const double a{ToDoubleCpp98(y)};
    const double b{ToDoubleApfloatCpp98(y)};
    const double c{ToDoubleBoostCpp98(y)};
    const double d{ToDoubleCpp11(y)};
    assert(a > 4818656.43384167 && a < 4818656.43384168);
    assert(b > 4818656.43384167 && b < 4818656.43384168);
    assert(c > 4818656.43384167 && c < 4818656.43384168);
    assert(d > 4818656.43384167 && d < 4818656.43384168);
  }
}
