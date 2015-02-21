//---------------------------------------------------------------------------
/*
RibiRegex, class for working with regular expressions
Copyright (C) 2014-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRibiRegex.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "ribi_regex.h"

#include <cassert>

#include <boost/xpressive/xpressive.hpp>

#include <QRegExp>

#include "testtimer.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::Regex::Regex()
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<std::string>
  ribi::Regex::GetRegexMatchesQRegExp(
  const std::string& s,
  const std::string& regex_str
) const noexcept
{
  QRegExp r(regex_str.c_str());
  r.setMinimal(true); //QRegExp must be non-greedy
  std::vector<std::string> v;
  int pos = 0;
  while ((pos = r.indexIn(s.c_str(), pos)) != -1)
  {
    const QString q = r.cap(1);
    if (q.isEmpty()) break;
    v.push_back(q.toStdString());
    pos += r.matchedLength();
  }
  return v;
}

std::vector<std::string>
  ribi::Regex::GetRegexMatchesXpressive(
  const std::string& s,
  const std::string& regex_str
) const noexcept
{
  assert(IsValidXpressive(regex_str));

  const boost::xpressive::sregex r
    = boost::xpressive::sregex::compile(regex_str)
  ;

  std::vector<std::string> v;
  boost::xpressive::sregex_iterator cur(s.begin(),s.end(),r);
  boost::xpressive::sregex_iterator end;
  for( ; cur != end; ++cur )
  {
    const boost::xpressive::smatch& what = *cur;
    v.push_back(what[0]);
  }
  return v;
}

std::string ribi::Regex::GetRegexDutchFloat() const noexcept
{
  return R"((\d*,\d*))";
}

std::string ribi::Regex::GetRegexDutchPostalCode() const noexcept
{
  return R"((\d{4})( )([A-Z]{2}))";
}

std::string ribi::Regex::GetRegexPolygon() const noexcept
{
  return
    "(POLYGON\\(\\(.*?\\)\\))"
  ;
}

std::string ribi::Regex::GetRegexShapes() const noexcept
{
  return R"((POLYGON\(\(.*?\)\))|(LINESTRING\(.*?\)))";
}

std::string ribi::Regex::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Regex::GetVersionHistory() noexcept
{
  return {
    "2014-06-19: Version 1.0: initial version",
    "2014-01-02: Version 1.1: added GetRegexDutchFloat"
  };
}

bool ribi::Regex::IsValidXpressive(const std::string& regex_str) const noexcept
{
  try
  {
    boost::xpressive::sregex::compile(regex_str);
  }
  catch (boost::xpressive::regex_error&)
  {
    return false;
  }
  return true;
}

#ifndef NDEBUG
void ribi::Regex::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  Regex r;
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};

  if (verbose) { TRACE("GetRegexMatches, plain, on Dutch postal codes"); }
  {
    const std::string s = "In the Netherlands, 1234 AB and 2345 BC are valid zip codes";
    std::vector<std::string> expected;
    expected.push_back("1234 AB");
    expected.push_back("2345 BC");
    {
      const std::string r = "(\\d{4} [A-Z]{2})";
      assert(Regex().GetRegexMatches(s,(r.c_str())) == expected);
    }
  }
  if (verbose) { TRACE("GetRegexMatches, plain, XML"); }
  {
    const std::string s = "<concept><name>Concept with examples</name><example>Example 1</example><example>Example 2</example><example>Example 3</example></concept>";
    const std::vector<std::string> expected {
      "<example>Example 1</example>",
      "<example>Example 2</example>",
      "<example>Example 3</example>"
    };
    const std::string regex_str = "(<example>.*?</example>)";
    assert(r.GetRegexMatches(s,regex_str) == expected);
  }
  if (verbose) { TRACE("GetRegexMatches on GetRegexDutchPostalCode"); }
  {
    const std::string s = "Both '1234 AB' and '9999 ZZ' are valid Dutch zip codes";
    const std::string t = r.GetRegexDutchPostalCode();
    const auto v = r.GetRegexMatches(s,t);
    //const auto w = r.GetRegexMatchesQRegExp(s,t);
    const auto x = r.GetRegexMatchesXpressive(s,t);
    assert(v.size() == 2);
    //assert(v == w);
    assert(v == x);
  }
  if (verbose) { TRACE("GetRegexMatches on GetRegexShapes"); }
  {
    const std::string s = "POLYGON((0 0,0 1,1 0)),LINESTRING(0 0,0 1,1 0)";
    const std::string t = r.GetRegexShapes();
    const auto v = r.GetRegexMatches(s,t);
    assert(v.size() == 2);
    assert(v[0] == "POLYGON((0 0,0 1,1 0))");
    assert(v[1] == "LINESTRING(0 0,0 1,1 0)");
    //const auto w = r.GetRegexMatchesQRegExp(s,t);
    const auto x = r.GetRegexMatchesXpressive(s,t);
    //assert(v == w);
    assert(v == x);
  }
  if (verbose) { TRACE("GetRegexDutchFloat"); }
  {
    assert( r.GetRegexMatches("1.23",r.GetRegexDutchFloat()).empty());
    assert(!r.GetRegexMatches("1,23",r.GetRegexDutchFloat()).empty());
  }
}
#endif
