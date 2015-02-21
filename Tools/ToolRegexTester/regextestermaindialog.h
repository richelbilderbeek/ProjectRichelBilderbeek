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
#ifndef REGEXTESTERMAINDIALOG_H
#define REGEXTESTERMAINDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include <boost/logic/tribool.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///RegexTesterMainDialog is a Strategy Design Pattern
struct RegexTesterMainDialog
{
  RegexTesterMainDialog() noexcept {}
  RegexTesterMainDialog(const RegexTesterMainDialog&) = delete;
  RegexTesterMainDialog& operator=(const RegexTesterMainDialog&) = delete;
  virtual ~RegexTesterMainDialog() noexcept {}

  ///Clone this class
  virtual boost::shared_ptr<RegexTesterMainDialog> Clone() const noexcept = 0;

  ///Get an example format used to replace regex matches
  virtual std::string GetExampleFormat() const noexcept = 0;

  ///Get an example line to apply a regex on
  virtual std::string GetExampleLine() const noexcept
  {
    return "Both '1234 AB' and '9999 ZZ' are valid Dutch zip codes";
  }

  ///Get an example regex
  virtual std::string GetExampleRegex() const noexcept = 0;

  ///Is the regex valid?
  virtual bool GetRegexValid(const std::string& regex_str) const noexcept = 0;

  ///Does the regex match the whole line?
  virtual bool GetRegexMatchLine(const std::string& line, const std::string& regex_str) const noexcept = 0;

  ///Get all regex matches withing a line
  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  virtual std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const std::string& r
  ) const = 0;

  ///Replace all regexes in a std::string following a regex and a format
  virtual std::string GetRegexReplace(
    const std::string& str,
    const std::string& regex_str,
    const std::string& format_str) const = 0;

  ///Obtain a description of the used implementation
  virtual std::string GetUsedImplementation() const noexcept = 0;

  static std::vector<std::string> GetTestRegexes() noexcept;
  static std::vector<std::string> GetTestStrings() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // REGEXTESTERMAINDIALOG_H
