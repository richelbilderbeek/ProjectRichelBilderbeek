#include <iostream>
#include <sstream>
#include <boost/date_time/gregorian/gregorian.hpp>

///Get today its date
//From http://www.richelbilderbeek.nl/CppGetToday.htm
//Sat Jan 3 2015
std::string GetTodayBoost() noexcept
{
  const boost::gregorian::date today
    = boost::gregorian::day_clock::local_day();
  std::stringstream s;
  s
    << today.day_of_week() << " "
    << today.month() << " "
    << today.day() << " "
    << today.year();
  return s.str();
}

///Get today its date
//From http://www.richelbilderbeek.nl/CppGetToday.htm
//Sat Jan  3 13:48:05 2015
std::string GetTodayStl() noexcept
{
  std::time_t my_time;
  std::time( &my_time );
  const std::tm * const time_and_date = std::localtime(&my_time);
  std::stringstream s;
  s << std::asctime(time_and_date);
  std::string str{s.str()};
  assert(str.back() == '\n');
  str.pop_back();
  return str;
}

///Get today its date
//From http://www.richelbilderbeek.nl/CppGetToday.htm
//2015-Jan-03
std::string GetTodayBoostSimpleString() noexcept
{
  const boost::gregorian::date today
    = boost::gregorian::day_clock::local_day();
  std::stringstream s;
  s << boost::gregorian::to_simple_string(today);
  return s.str();
}

///Get today its date
//From http://www.richelbilderbeek.nl/CppGetToday.htm
//2015-01-03
std::string GetTodayBoostIsoExtendedString() noexcept
{
  const boost::gregorian::date today
    = boost::gregorian::day_clock::local_day();
  std::stringstream s;
  s << boost::gregorian::to_iso_extended_string(today);
  return s.str();
}

///Get today its date
//From http://www.richelbilderbeek.nl/CppGetToday.htm
//20150103
std::string GetTodayBoostIsoString() noexcept
{
  const boost::gregorian::date today
    = boost::gregorian::day_clock::local_day();
  std::stringstream s;
  s << boost::gregorian::to_iso_string(today);
  return s.str();
}

///Get today its date
//From http://www.richelbilderbeek.nl/CppGetToday.htm
//2015-01-03
std::string GetTodayBoostSqlString() noexcept
{
  const boost::gregorian::date today
    = boost::gregorian::day_clock::local_day();
  std::stringstream s;
  s << boost::gregorian::to_sql_string(today);
  return s.str();
}

int main()
{
  std::cout
    << GetTodayStl() << '\n'
    << GetTodayBoost() << '\n'
    << GetTodayBoostIsoExtendedString() << '\n'
    << GetTodayBoostIsoString() << '\n'
    << GetTodayBoostSqlString() << '\n'
  ;
}
/* Screen output:

Sat Jan  3 13:48:43 2015
Sat Jan 3 2015
2015-01-03
20150103
2015-01-03

*/
