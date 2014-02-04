#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop


//Format a double to a std::string with one
//digit behind the comma
const std::string MyCustomFormat(const double x)
{
  std::stringstream s;
  s << std::setprecision(1) << std::fixed << x;
  const std::string t = s.str();
  return t;
}

int main()
{
  assert(MyCustomFormat( 123456.7890) == "123456.8");
  assert(MyCustomFormat(  12345.6789) ==  "12345.7");
  assert(MyCustomFormat(   1234.5678) ==   "1234.6");
  assert(MyCustomFormat(    123.4567) ==    "123.5");
  assert(MyCustomFormat(     12.3456) ==     "12.3");
  assert(MyCustomFormat(      1.2345) ==      "1.2");
  assert(MyCustomFormat(      0.1234) ==      "0.1");
  assert(MyCustomFormat(      0.0123) ==      "0.0");
  assert(MyCustomFormat(      0.0012) ==      "0.0");
  assert(MyCustomFormat(      0.0001) ==      "0.0");
  assert(MyCustomFormat(      0.0000) ==      "0.0");
  assert(MyCustomFormat(        0.99) ==      "1.0");

  assert(MyCustomFormat(-123456.7890) == "-123456.8");
  assert(MyCustomFormat( -12345.6789) ==  "-12345.7");
  assert(MyCustomFormat(  -1234.5678) ==   "-1234.6");
  assert(MyCustomFormat(   -123.4567) ==    "-123.5");
  assert(MyCustomFormat(    -12.3456) ==     "-12.3");
  assert(MyCustomFormat(     -1.2345) ==      "-1.2");
  assert(MyCustomFormat(     -0.1234) ==      "-0.1");
  assert(MyCustomFormat(     -0.0123) ==      "-0.0");
  assert(MyCustomFormat(     -0.0012) ==      "-0.0");
  assert(MyCustomFormat(     -0.0001) ==      "-0.0");
  assert(MyCustomFormat(     -0.0000) ==      "-0.0");
  assert(MyCustomFormat(       -0.99) ==      "-1.0");

  //Now do the same with boost::format...
  assert(!"TODO");
}
