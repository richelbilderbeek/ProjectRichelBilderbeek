//---------------------------------------------------------------------------
/*
RegexTester, regular expression tester
Copyright (C) 2010-2013 Richel Bilderbeek

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

#include "trace.h"
#pragma GCC diagnostic pop

ribi::RegexTesterBoostXpressiveMainDialog::RegexTesterBoostXpressiveMainDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}


const boost::shared_ptr<ribi::RegexTesterMainDialog>
  ribi::RegexTesterBoostXpressiveMainDialog::Clone() const noexcept
{
  boost::shared_ptr<RegexTesterMainDialog> d(
    new RegexTesterBoostXpressiveMainDialog);
  return d;
}

const std::vector<std::string>
  ribi::RegexTesterBoostXpressiveMainDialog::GetRegexMatches(
  const std::string& s,
  const std::string& r) const
{
  if (!this->GetRegexValid(r)) return std::vector<std::string>();

  return GetRegexMatches(s,boost::xpressive::sregex::compile(r));
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
const std::vector<std::string>
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

bool ribi::RegexTesterBoostXpressiveMainDialog::GetRegexMatchLine(
  const std::string& line, const std::string& regex_str) const noexcept
{
  if (!GetRegexValid(regex_str)) return false;
  const boost::xpressive::sregex r(
    boost::xpressive::sregex::compile(regex_str));
  return boost::xpressive::regex_match(line,r);
}

const std::string ribi::RegexTesterBoostXpressiveMainDialog::GetRegexReplace(
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
  try
  {
    boost::xpressive::sregex::compile(regex_str);
  }
  catch (boost::xpressive::regex_error& e) { return false; }
  return true;
}

#ifndef NDEBUG
void ribi::RegexTesterBoostXpressiveMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::RegexTesterBoostXpressiveMainDialog::Test")
  RegexTesterBoostXpressiveMainDialog d;
  assert(!d.GetExampleRegex().empty());
  for (auto v: d.GetTestRegexes() )
  {
    TRACE(v);
    d.GetRegexValid(v);
    for (auto w: d.GetTestStrings() )
    {
      TRACE(w);
      d.GetRegexMatches(v,w);
      TRACE_FUNC();
      d.GetRegexMatches(w,v);
      TRACE_FUNC();
      d.GetRegexMatchLine(v,w);
      TRACE_FUNC();
      d.GetRegexMatchLine(w,v);
      TRACE_FUNC();
      d.GetRegexReplace(v,w,v);
      TRACE_FUNC();
      d.GetRegexReplace(w,v,v);
      TRACE_FUNC();
      d.GetRegexReplace(v,w,w);
      TRACE_FUNC();
      d.GetRegexReplace(w,v,w);
      TRACE_FUNC();
      d.GetRegexValid(w);
      TRACE_FUNC();
    }
  }
  TRACE("Finished ribi::RegexTesterBoostXpressiveMainDialog::Test successfully")
}
#endif
