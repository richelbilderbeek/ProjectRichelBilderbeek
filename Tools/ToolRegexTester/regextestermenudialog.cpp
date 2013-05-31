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
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "regextestermenudialog.h"

const About RegexTesterMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "RegexTester",
    "regular expression tester",
    "the 20th of March 2013",
    "2010-2013",
    "http://www.richelbilderbeek.nl/ToolRegexTester.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}

const std::string RegexTesterMenuDialog::GetVersion()
{
  return "1.6";
}

const std::vector<std::string> RegexTesterMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-08-19: Version 1.3: Qt GUI application");
  v.push_back("2012-01-07: Version 1.4: port to Wt and console application");
  v.push_back("2012-09-24: Version 1.5: added Qt and C++11 versions");
  v.push_back("2013-03-20: Version 1.6: added TR1 version, added replace");
  return v;
}
