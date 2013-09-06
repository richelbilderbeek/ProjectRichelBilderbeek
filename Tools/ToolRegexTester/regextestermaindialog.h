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
#ifndef REGEXTESTERMAINDIALOG_H
#define REGEXTESTERMAINDIALOG_H

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/logic/tribool.hpp>

namespace ribi {

///RegexTesterMainDialog is a Strategy Design Pattern
struct RegexTesterMainDialog
{
  RegexTesterMainDialog() {}

  virtual ~RegexTesterMainDialog() {}

  ///Clone this class
  virtual const boost::shared_ptr<RegexTesterMainDialog> Clone() const = 0;

  ///Get an example format used to replace regex matches
  virtual const std::string GetExampleFormat() const = 0;

  ///Get an example line to apply a regex on
  virtual const std::string GetExampleLine() const
  {
    return "Both '1234 AB' and '9999 ZZ' are valid Dutch zip codes";
  }

  ///Get an example regex
  virtual const std::string GetExampleRegex() const = 0;

  ///Is the regex valid?
  virtual bool GetRegexValid(const std::string& regex_str) const = 0;

  ///Does the regex match the whole line?
  virtual bool GetRegexMatchLine(const std::string& line, const std::string& regex_str) const = 0;

  ///Get all regex matches withing a line
  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  virtual const std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const std::string& r) const = 0;

  ///Replace all regexes in a std::string following a regex and a format
  virtual const std::string GetRegexReplace(
    const std::string& str,
    const std::string& regex_str,
    const std::string& format_str) const = 0;

  ///Obtain a description of the used implementation
  virtual const std::string GetUsedImplementation() const = 0;

  static const std::vector<std::string> GetTestRegexes();
  static const std::vector<std::string> GetTestStrings();

};

} //~namespace ribi

#endif // REGEXTESTERMAINDIALOG_H
