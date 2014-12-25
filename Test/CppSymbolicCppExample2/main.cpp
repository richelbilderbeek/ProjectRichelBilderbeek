#include <cassert>
#include <sstream>
#include "symbolicc++.h"

std::string ToStr(const Symbolic& s)
{
  std::stringstream str;
  str << s;
  return str.str();
}

int main()
{
   Symbolic x("x");
   std::stringstream s;
   const Symbolic f = (3*x*x) + (2 * x) + sin(x);
   const std::string f_str = ToStr(f);
   assert(f_str == "3*x^(2)+2*x+sin(x)");

   //Take the derivative of f
   const Symbolic g = df(f,x);
   const std::string g_str = ToStr(g);
   assert(g_str == "6*x+cos(x)+2");
}
