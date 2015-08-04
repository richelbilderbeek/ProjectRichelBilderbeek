#include <cassert>
#include <iostream>
#include <chrono>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
//#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop


#ifndef _WIN32

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
#endif

//Returns date in YYYY-MM-DD format
//From http://www.richelbilderbeek.nl/CppGetDateIso8601.htm
const std::string GetDateIso8601Stl()
{
  const std::time_t t = std::time(0);
  const std::tm * const now = std::localtime( &t );
  std::string year;
  {
    std::stringstream s;
    s << (now->tm_year + 1900);
    year = s.str();
  }
  assert(year.size() == 4);
  std::string month;
  {
    std::stringstream s;
    s << (now->tm_mon + 1);
    month = s.str();
    if (month.size() == 1) month = std::string("0") + month;
  }
  assert(month.size() == 2);
  std::string day;
  {
    std::stringstream s;
    s << (now->tm_mday);
    day = s.str();
    if (day.size() == 1) day = std::string("0") + day;
  }
  assert(day.size() == 2);
  const std::string date{
    year + "-" + month + "-" + day
  };
  assert(date.size()==10);
  assert(date[4]=='-');
  assert(date[7]=='-');
  return date;
}

int main()
{
  #ifndef _WIN32
  assert(GetDateIso8601Boost() == GetDateIso8601Stl());
  #endif
  std::cout << GetDateIso8601Stl() << '\n';
}
