#include <string>

//From http://www.richelbilderbeek.nl/CppStrToInt.htm
int StrToIntStl(const std::string& s)
{
  return std::atoi(s.c_str());
}

//From http://www.richelbilderbeek.nl/CppStrToInt.htm
int StrToIntCpp0x(const std::string& s)
{
  return std::stoi(s);
}

#include <boost/lexical_cast.hpp>

//From http://www.richelbilderbeek.nl/CppStrToInt.htm
int StrToIntBoost(const std::string& s)
{
  return boost::lexical_cast<int>(s);
}

bool CanStrToIntStl(const std::string& s)
{
  const int i = std::atoi(s.c_str());
  return i!=0 || s=="0";
}

int CanStrToIntCpp0x(const std::string& s)
{
  try { std::stoi(s); }
  catch (std::exception&) { return false; }
  return true;
}

int CanStrToIntBoost(const std::string& s)
{
  try { boost::lexical_cast<int>(s); }
  catch (boost::bad_lexical_cast&) { return false; }
  return true;

}

#include <cassert>

int main()
{
  assert(!CanStrToIntStl("a"));
  assert(!CanStrToIntCpp0x("a"));
  assert(!CanStrToIntBoost("a"));

  assert(CanStrToIntStl("0"));
  assert(CanStrToIntCpp0x("0"));
  assert(CanStrToIntBoost("0"));

  assert(CanStrToIntStl("123"));
  assert(CanStrToIntCpp0x("123"));
  assert(CanStrToIntBoost("123"));

  const std::string s = "123";
  assert(StrToIntStl(s) == StrToIntCpp0x(s));
  assert(StrToIntStl(s) == StrToIntBoost(s));
}
