#include <string>

//From http://www.richelbilderbeek.nl/CppIntToStr.htm
std::string IntToStrCpp0x(const int x)
{
  return std::to_string(x);
}

#include <sstream>
#include <stdexcept>
#include <string>

//From http://www.richelbilderbeek.nl/CppIntToStr.htm
std::string IntToStrCpp98(const int x)
{
  std::ostringstream s;
  if (!(s << x)) throw std::logic_error("IntToStr failed");
  return s.str();
}

#include <string>
#include <boost/lexical_cast.hpp>

//From http://www.richelbilderbeek.nl/CppIntToStr.htm
std::string IntToStrBoost(const int x)
{
  return boost::lexical_cast<std::string>(x);
}

#include <cassert>

int main()
{
  assert(IntToStrCpp0x(123) == "123");
  assert(IntToStrBoost(123) == "123");
  assert(IntToStrCpp98(123) == "123");

  assert(IntToStrCpp0x(-123) == "-123");
  assert(IntToStrBoost(-123) == "-123");
  assert(IntToStrCpp98(-123) == "-123");

  assert(IntToStrCpp0x(0) == "0");
  assert(IntToStrBoost(0) == "0");
  assert(IntToStrCpp98(0) == "0");
}
