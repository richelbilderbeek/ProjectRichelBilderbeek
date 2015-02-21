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
#include "regextestercpp11maindialog.h"
#include <regex>
#include "trace.h"
#pragma GCC diagnostic pop

boost::shared_ptr<ribi::RegexTesterMainDialog>
  ribi::RegexTesterCpp11MainDialog::Clone() const noexcept
{
  boost::shared_ptr<RegexTesterMainDialog> d(
    new RegexTesterCpp11MainDialog);
  return d;
}

std::vector<std::string> ribi::RegexTesterCpp11MainDialog::GetRegexMatches(
  const std::string& s,
  const std::string& r) const
{
  if (!this->GetRegexValid(r)) return std::vector<std::string>();
  return GetRegexMatches(s,std::regex(r, std::regex_constants::basic));
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
std::vector<std::string> ribi::RegexTesterCpp11MainDialog::GetRegexMatches(
  const std::string& /* s */,
  const std::regex& /* r */) const
{
  std::vector<std::string> v;

  /* COMPILES, BUT NOT SUPPORTED
  std::string::const_iterator start = s.begin();
  const std::string::const_iterator end = s.end();
  std::match_results<std::string::const_iterator> what;
  std::regex_constants::match_flag_type flags = std::regex_constants::match_default;
  while(std::regex_search(start, end, what, r, flags))
  {
    const std::string x = what.str();
    v.push_back(x);
    if (v.size() == 10) return v;
    start = what[0].second;
    flags |= std::regex_constants::match_prev_avail;
    flags |= std::regex_constants::match_not_bow; //was: boost::match_not_bob
  }
  */
  v.push_back("GCC does not support std::regex yet");
  return v;
}


bool ribi::RegexTesterCpp11MainDialog::GetRegexMatchLine(
  const std::string &line, const std::string &regex_str) const noexcept
{
  if (!GetRegexValid(regex_str)) return false;
  const std::regex r(regex_str, std::regex_constants::basic);
  return std::regex_match(line,r);
}

std::string ribi::RegexTesterCpp11MainDialog::GetRegexReplace(
  const std::string& str,
  const std::string& regex_str,
  const std::string& format_str) const
{
  try
  {
    return std::regex_replace(
      str, std::regex(regex_str), format_str,
      std::regex_constants::match_default | std::regex_constants::format_default);
  }
  catch (std::regex_error& e)
  {
    const std::string s = "std::regex_error: " + std::string(e.what());
    return s;
  }
}

bool ribi::RegexTesterCpp11MainDialog::GetRegexValid(
  const std::string &regex_str) const noexcept
{
  try { const std::regex regex_temp( regex_str, std::regex_constants::basic ); }
  catch (std::regex_error& e) { return false; }
  return true;
}
