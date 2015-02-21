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


#include "regextesterboostregexmaindialog.h"

#ifdef TOOLREGEXTESTER_ADD_BOOST_REGEX


#include <boost/regex.hpp>

const boost::shared_ptr<RegexTesterMainDialog> RegexTesterBoostRegexMainDialog::Clone() const
{
  boost::shared_ptr<RegexTesterMainDialog> d(
    new RegexTesterBoostRegexMainDialog);
  return d;
}

const std::vector<std::string> RegexTesterBoostRegexMainDialog::GetRegexMatches(
  const std::string& s,
  const std::string& r) const
{
  if (!this->GetRegexValid(r)) return std::vector<std::string>();

  return GetRegexMatches(s,boost::regex(r));
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
const std::vector<std::string> RegexTesterBoostRegexMainDialog::GetRegexMatches(
  const std::string& s,
  const boost::regex& r)
{
  std::vector<std::string> v;
  std::string::const_iterator start = s.begin();
  const std::string::const_iterator end = s.end();
  boost::match_results<std::string::const_iterator> what;
  boost::match_flag_type flags = boost::match_default;
  while(boost::regex_search(start, end, what, r, flags))
  {
    const std::string x = what.str();
    v.push_back(x);
    if (v.size() == 10) return v;
    start = what[0].second;
    flags |= boost::match_prev_avail;
    flags |= boost::match_not_bob;
  }
  return v;
}

bool RegexTesterBoostRegexMainDialog::GetRegexMatchLine(
  const std::string& line, const std::string& regex_str) const
{
  if (!GetRegexValid(regex_str)) return false;
  const boost::regex r(regex_str);
  return boost::regex_match(line,r);
}

const std::string RegexTesterBoostRegexMainDialog::GetRegexReplace(
  const std::string& str,
  const std::string& regex_str,
  const std::string& format_str) const
{
  try
  {
    return boost::regex_replace(
      str, boost::regex(regex_str), format_str,
      boost::match_default | boost::format_all);
  }
  catch (boost::regex_error& )
  {
    return "";
  }
}

bool RegexTesterBoostRegexMainDialog::GetRegexValid(
  const std::string& regex_str) const
{
  try { const boost::regex regex_temp(regex_str); }
  catch (boost::regex_error& e) { return false; }
  return true;
}
#endif
