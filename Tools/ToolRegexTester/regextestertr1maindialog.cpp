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



//std::tr1::regex not implemented in GCC
#ifndef __GNUC__
#include "regextestertr1maindialog.h"

#include <tr1/regex>
#include "trace.h"

const boost::shared_ptr<ribi::RegexTesterMainDialog> ribi::RegexTesterTr1MainDialog::Clone() const
{
  boost::shared_ptr<RegexTesterMainDialog> d(
    new RegexTesterTr1MainDialog);
  return d;
}

std::vector<std::string> ribi::RegexTesterTr1MainDialog::GetRegexMatches(
  const std::string& s,
  const std::string& r) const
{
  if (!this->GetRegexValid(r)) return std::vector<std::string>();
  return GetRegexMatches(s,std::tr1::regex(r, std::tr1::regex_constants::basic));
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
std::vector<std::string> ribi::RegexTesterTr1MainDialog::GetRegexMatches(
  const std::string&,
  const std::tr1::regex&)
{
  std::vector<std::string> v;
  v.push_back("GCC does not support regex yet");
  return v;
}


bool ribi::RegexTesterTr1MainDialog::GetRegexMatchLine(const std::string &line, const std::string &regex_str) const
{
  if (!GetRegexValid(regex_str)) return false;
  const std::tr1::regex r(regex_str, std::tr1::regex_constants::basic);
  return std::tr1::regex_match(line,r);
}

bool ribi::RegexTesterTr1MainDialog::GetRegexValid(const std::string &regex_str) const
{
  try { const std::tr1::regex regex_temp( regex_str, std::tr1::regex_constants::basic ); }
  catch (std::tr1::regex_error& e) { return false; }
  return true;
}

#endif // __GNUC__

