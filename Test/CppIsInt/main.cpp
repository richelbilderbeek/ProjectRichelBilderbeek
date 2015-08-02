#include <sstream>

///IsInt determines if std::string can be converted to integer.
///From http://www.richelbilderbeek.nl/CppIsInt.htm
bool IsIntStl(const std::string& s)
{
  std::istringstream i(s);
  int temp{0};
  i >> temp;
  if (!i) return false;
  char c{'\0'}; //Should be at end, if not, the string contained more than just a number
  i >> c;
  if (i) return false;
  return true;
}

#include <boost/lexical_cast.hpp>

///IsInt determines if std::string can be converted to integer.
///From http://www.richelbilderbeek.nl/CppIsInt.htm
bool IsIntBoost(const std::string& s) noexcept
{
  try
  {
    boost::lexical_cast<int>(s);
    return true;
  }
  catch (boost::bad_lexical_cast&)
  {
    return false;
  }
}

#include <cassert>

int main()
{
  assert(IsIntStl("3"));
  assert(IsIntStl("0"));
  assert(IsIntStl("-23"));
  assert(!IsIntStl("a"));
  assert(!IsIntStl("2+fire"));

  assert(IsIntBoost("3"));
  assert(IsIntBoost("0"));
  assert(IsIntBoost("-23"));
  assert(!IsIntBoost("a"));
  assert(!IsIntBoost("2+fire"));
}
