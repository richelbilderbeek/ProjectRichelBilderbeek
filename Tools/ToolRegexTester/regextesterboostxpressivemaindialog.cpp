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
#include "regextesterboostxpressivemaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

const boost::shared_ptr<RegexTesterMainDialog>
  RegexTesterBoostXpressiveMainDialog::Clone() const
{
  boost::shared_ptr<RegexTesterMainDialog> d(
    new RegexTesterBoostXpressiveMainDialog);
  return d;
}

const std::vector<std::string>
  RegexTesterBoostXpressiveMainDialog::GetRegexMatches(
  const std::string& s,
  const std::string& r) const
{
  if (!this->GetRegexValid(r)) return std::vector<std::string>();

  return GetRegexMatches(s,boost::xpressive::sregex::compile(r));
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
const std::vector<std::string>
  RegexTesterBoostXpressiveMainDialog::GetRegexMatches(
  const std::string& s,
  const boost::xpressive::sregex& r)
{
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

bool RegexTesterBoostXpressiveMainDialog::GetRegexMatchLine(
  const std::string& line, const std::string& regex_str) const
{
  if (!GetRegexValid(regex_str)) return false;
  const boost::xpressive::sregex r(
    boost::xpressive::sregex::compile(regex_str));
  return boost::xpressive::regex_match(line,r);
}

const std::string RegexTesterBoostXpressiveMainDialog::GetRegexReplace(
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
        | boost::xpressive::regex_constants::format_all);
  }
  catch (boost::xpressive::regex_error& )
  {
    return "";
  }
}

bool RegexTesterBoostXpressiveMainDialog::GetRegexValid(
  const std::string& regex_str) const
{
  try
  {
    const boost::xpressive::sregex regex_temp(
      boost::xpressive::sregex::compile(regex_str));
  }
  catch (boost::xpressive::regex_error& e) { return false; }
  return true;
}
