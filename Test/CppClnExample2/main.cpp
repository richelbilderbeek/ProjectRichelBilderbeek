//---------------------------------------------------------------------------
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
#include <cln/cln.h>
//---------------------------------------------------------------------------
///IntToStrWithSep converts an integer to std::string
///and adds thousands seperators.
///From http://www.richelbilderbeek.nl/CppIntToStrWithSep.htm
const std::string IntToStrWithSep(cln::cl_I i)
{
  std::string s
    = boost::lexical_cast<std::string>(cln::mod(i,10));
  i = cln::floor1(i,10);
  int d = 1;
  while (!cln::zerop(i))
  {
    s = boost::lexical_cast<std::string>(cln::mod(i,10))
      + (d % 3 == 0 ? "," : "")
      + s;
    i = cln::floor1(i,10);
    ++d;
  }
  return s;
}
//---------------------------------------------------------------------------
int main()
{
  const cln::cl_I i("123456789012345678901234567890");
  std::cout << "i without seperators: " << i << '\n';
  const std::string s = IntToStrWithSep(i);
  std::cout << "i with seperators: " << s << '\n';
}
//---------------------------------------------------------------------------
