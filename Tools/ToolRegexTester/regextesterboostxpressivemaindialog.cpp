//---------------------------------------------------------------------------
/*
RegexTester, regular expression tester
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRegexTester.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "regextesterboostxpressivemaindialog.h"

#include <boost/xpressive/xpressive.hpp>

#include <boost/xpressive/detail/dynamic/parse_charset.hpp>

#include "ribi_regex.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::RegexTesterBoostXpressiveMainDialog::RegexTesterBoostXpressiveMainDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}


boost::shared_ptr<ribi::RegexTesterMainDialog>
  ribi::RegexTesterBoostXpressiveMainDialog::Clone() const noexcept
{
  boost::shared_ptr<RegexTesterMainDialog> d(
    new RegexTesterBoostXpressiveMainDialog);
  return d;
}

std::vector<std::string>
  ribi::RegexTesterBoostXpressiveMainDialog::GetRegexMatches(
  const std::string& s,
  const std::string& regex_str
) const noexcept
{
  if (!this->GetRegexValid(regex_str)) return std::vector<std::string>();
  return Regex().GetRegexMatchesXpressive(s,regex_str);
  //return GetRegexMatches(s,boost::xpressive::sregex::compile(r));
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
/*
std::vector<std::string>
  ribi::RegexTesterBoostXpressiveMainDialog::GetRegexMatches(
  const std::string& s,
  const boost::xpressive::sregex& r)
{
  std::vector<std::string> v;

  try
  {
    boost::xpressive::sregex_iterator cur(s.begin(),s.end(),r);
    boost::xpressive::sregex_iterator end;

    for( ; cur != end; ++cur )
    {
      const boost::xpressive::smatch& what = *cur;
      assert(!what.empty());
      v.push_back(what[0]);
    }
  }
  catch (...)
  {
    v.push_back("UNKNOWN exception");
  }
  return v;
}
*/

bool ribi::RegexTesterBoostXpressiveMainDialog::GetRegexMatchLine(
  const std::string& line,
  const std::string& regex_str
) const noexcept
{
  if (!GetRegexValid(regex_str)) return false;
  const boost::xpressive::sregex r(
    boost::xpressive::sregex::compile(regex_str));
  return boost::xpressive::regex_match(line,r);
}

std::string ribi::RegexTesterBoostXpressiveMainDialog::GetRegexReplace(
  const std::string& str,
  const std::string& regex_str,
  const std::string& format_str) const
{
  try
  {
    return boost::xpressive::regex_replace(
      str,
      boost::xpressive::sregex(boost::xpressive::sregex::compile(regex_str)),
      format_str,
      boost::xpressive::regex_constants::match_default
        | boost::xpressive::regex_constants::format_all
        | boost::xpressive::regex_constants::format_no_copy);
  }
  catch (boost::xpressive::regex_error& e)
  {
    const std::string s
      = "boost::xpressive::regex_error: " + std::string(e.what());
    return "";
  }
}

bool ribi::RegexTesterBoostXpressiveMainDialog::GetRegexValid(
  const std::string& regex_str) const noexcept
{
  return Regex().IsValidXpressive(regex_str);
  /*
  try
  {
    boost::xpressive::sregex::compile(regex_str);
  }
  catch (boost::xpressive::regex_error& e) { return false; }
  return true;
  */
}

#ifndef NDEBUG
void ribi::RegexTesterBoostXpressiveMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  RegexTesterBoostXpressiveMainDialog d;
  assert(!d.GetExampleRegex().empty());
  for (const auto& v: d.GetTestRegexes() )
  {
    d.GetRegexValid(v);
    for (const auto& w: d.GetTestStrings() )
    {
      d.GetRegexMatches(v,w);
      d.GetRegexMatches(w,v);
      d.GetRegexMatchLine(v,w);
      d.GetRegexMatchLine(w,v);
      d.GetRegexReplace(v,w,v);
      d.GetRegexReplace(w,v,v);
      d.GetRegexReplace(v,w,w);
      d.GetRegexReplace(w,v,w);
      d.GetRegexValid(w);
    }
  }
}
#endif
