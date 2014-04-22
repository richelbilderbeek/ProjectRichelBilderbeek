#include <cassert>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/regex.hpp>
#pragma GCC diagnostic pop

int main()
{
  const std::string s = "(1) 1234 AB (2) 2345 BC (3)";
  const boost::regex r("\\d{4} [A-Z]{2}");

  boost::sregex_iterator i(s.begin(),s.end(),r);
  assert(i != boost::sregex_iterator());
  assert(i->str()=="1234 AB");
  ++i;
  assert(i != boost::sregex_iterator());
  assert(i->str()=="2345 BC");
  ++i;
  assert(i == boost::sregex_iterator());
}
