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
#ifndef REGEXTESTERTR1MAINDIALOG_H
#define REGEXTESTERTR1MAINDIALOG_H

//std::tr1::regex not implemented in GCC
#ifndef __GNUC__

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

  ///Get an example regex
  const std::string GetExampleRegex() const { return ""; }

  ///Get all regex matches withing a line
  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  const std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const std::string& r) const;

  ///Does the regex match the whole line?
  bool GetRegexMatchLine(const std::string& line, const std::string& regex_str) const;

  ///Is the regex valid?
  bool GetRegexValid(const std::string &regex_str) const;

  ///Obtain a description of the used implementation
  const std::string GetUsedImplementation() const { return "TR1"; }

  private:
  ///Get all regex matches withing a line
  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  static const std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const std::tr1::regex& r);
};
#endif // __GNUC__

#endif // REGEXTESTERTR1MAINDIALOG_H
