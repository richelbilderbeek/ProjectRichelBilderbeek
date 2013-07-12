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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "regextestercpp11maindialog.h"

#include <regex>
#include "trace.h"

const boost::shared_ptr<RegexTesterMainDialog> RegexTesterCpp11MainDialog::Clone() const
{
  boost::shared_ptr<RegexTesterMainDialog> d(
    new RegexTesterCpp11MainDialog);
  return d;
}

const std::vector<std::string> RegexTesterCpp11MainDialog::GetRegexMatches(
  const std::string& s,
  const std::string& r) const
{
  if (!this->GetRegexValid(r)) return std::vector<std::string>();
  return GetRegexMatches(s,std::regex(r, std::regex_constants::basic));
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
const std::vector<std::string> RegexTesterCpp11MainDialog::GetRegexMatches(
  const std::string&,
  const std::regex&)
{
  std::vector<std::string> v;
  v.push_back("GCC does not support regex yet");
  return v;
}


bool RegexTesterCpp11MainDialog::GetRegexMatchLine(const std::string &line, const std::string &regex_str) const
{
  if (!GetRegexValid(regex_str)) return false;
  const std::regex r(regex_str, std::regex_constants::basic);
  return std::regex_match(line,r);
}

const std::string RegexTesterCpp11MainDialog::GetRegexReplace(
  const std::string& str,
  const std::string& regex_str,
  const std::string& format_str) const
{
  return std::regex_replace(
    str, std::regex(regex_str), format_str,
    std::regex_constants::match_default | std::regex_constants::format_default);
}

bool RegexTesterCpp11MainDialog::GetRegexValid(const std::string &regex_str) const
{
  try { const std::regex regex_temp( regex_str, std::regex_constants::basic ); }
  catch (std::regex_error& e) { return false; }
  return true;
}
