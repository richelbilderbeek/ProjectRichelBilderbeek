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
#ifndef REGEXTESTERQTMAINDIALOG_H
#define REGEXTESTERQTMAINDIALOG_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "regextestermaindialog.h"

struct QRegExp;

namespace ribi {

struct RegexTesterQtMainDialog : public RegexTesterMainDialog
{
  RegexTesterQtMainDialog() {}

  ///Clone this class
  boost::shared_ptr<RegexTesterMainDialog> Clone() const noexcept;

  ///Get an example format used to replace regex matches
  std::string GetExampleFormat() const noexcept { return "$0"; }

  ///Get an example regex
  std::string GetExampleRegex() const noexcept { return "(\\d{4} [A-Z]{2})"; }

  ///Get all regex matches withing a line
  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const std::string& r) const;

  ///Does the regex match the whole line?
  bool GetRegexMatchLine(const std::string &line, const std::string &regex_str) const noexcept;

  ///Is the regex valid?
  bool GetRegexValid(const std::string &regex_str) const noexcept;

  ///Replace all regexes in a std::string following a regex and a format
  std::string GetRegexReplace(
    const std::string& str,
    const std::string& regex_str,
    const std::string& format_str) const;

  ///Obtain a description of the used implementation
  std::string GetUsedImplementation() const noexcept { return "QRegex"; }

  private:
  ///Get all regex matches withing a line
  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  static std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const QRegExp& r);

};

} //~namespace ribi

#endif // REGEXTESTERQTMAINDIALOG_H
