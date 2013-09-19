#include <cassert>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

//Returns date in YYYY-MM-DD format
//From http://www.richelbilderbeek.nl/CppGetDateIso8601.htm
const std::string GetDateIso8601Boost()
{
  const boost::gregorian::date today
    = boost::gregorian::day_clock::local_day();
  const std::string s
    = boost::gregorian::to_iso_extended_string(today);
  assert(s.size()==10);
  assert(s[4]=='-');
  assert(s[7]=='-');
  return s;
}

//Returns date in YYYY-MM-DD format
//From http://www.richelbilderbeek.nl/CppGetDateIso8601.htm
const std::string GetDateIso8601Stl()
{
  const boost::gregorian::date today
    = boost::gregorian::day_clock::local_day();
  const std::string s
    = boost::gregorian::to_iso_extended_string(today);
  assert(s.size()==10);
  assert(s[4]=='-');
  assert(s[7]=='-');
  return s;
}

int main()
{
  assert(GetDateIso8601Boost() == GetDateIso8601Stl());
  std::cout << GetDateIso8601Boost() << '\n';
}
