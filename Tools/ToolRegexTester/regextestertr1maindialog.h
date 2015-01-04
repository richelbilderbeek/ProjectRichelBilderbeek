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
#ifndef REGEXTESTERTR1MAINDIALOG_H
#define REGEXTESTERTR1MAINDIALOG_H


//std::tr1::regex not implemented in GCC
#ifndef __GNUC__
namespace ribi {

#include <string>
#include <vector>
#include <tr1/regex>

#include <boost/logic/tribool.hpp>
#include "regextestermaindialog.h"

struct RegexTesterTr1MainDialog : public RegexTesterMainDialog
{
  RegexTesterTr1MainDialog() {}

  ///Clone this class
  const boost::shared_ptr<RegexTesterMainDialog> Clone() const;

  ///Get an example format used to replace regex matches
  std::string GetExampleFormat() const { return "$0"; }

  ///Get an example regex
  std::string GetExampleRegex() const { return "(\\d{4} [A-Z]{2})"; }

  ///Get all regex matches withing a line
  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const std::string& r) const;

  ///Does the regex match the whole line?
  bool GetRegexMatchLine(const std::string& line, const std::string& regex_str) const;

  ///Is the regex valid?
  bool GetRegexValid(const std::string &regex_str) const;

  ///Obtain a description of the used implementation
  std::string GetUsedImplementation() const { return "TR1"; }

  private:
  ///Get all regex matches withing a line
  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  static std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const std::tr1::regex& r);
};
} //~namespace ribi

#endif // __GNUC__

#endif // REGEXTESTERTR1MAINDIALOG_H
