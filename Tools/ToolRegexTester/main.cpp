//---------------------------------------------------------------------------
/*
RegexTester, regular expression tester
Copyright (C) 2010 Richel Bilderbeek

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
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/program_options.hpp>

#include "regextestermaindialog.h"
#include "regextesterboostregexmaindialog.h"
#include "regextesterboostxpressivemaindialog.h"
#include "regextestercpp11maindialog.h"
#include "regextestertr1maindialog.h"
#include "regextesterqtmaindialog.h"
#include "regextestermenudialog.h"

#pragma GCC diagnostic pop


int main(int argc, char* argv[])
{
  std::string s;
  std::string r;

  boost::program_options::options_description d("Allowed options for RegexTester");
  d.add_options()
      ("help",
        "produce this help message")
      ("a",
        "show the information about the program")
      ("v",
        "show the version of this program")
      ("r",
         boost::program_options::value<std::string>(&r)->default_value("(\\d{4}\\s[A-Z]{2})"),
         "the regular expression")
      ("s",
         boost::program_options::value<std::string>(&s)->default_value("Both '1234 AB' and '9999 ZZ' are valid Dutch zip codes"),
         "the string to be searched");

  boost::program_options::variables_map m;
  boost::program_options::store(
    boost::program_options::parse_command_line(
      argc, argv, d), m);
  boost::program_options::notify(m);

  if (m.count("help"))
  {
    std::cout << d << "\n";
    return 0;
  }

  if (m.count("a"))
  {
    std::cout << ribi::RegexTesterMenuDialog::GetAbout() << '\n';
    return 0;
  }

  if (m.count("v"))
  {
    std::cout << ribi::RegexTesterMenuDialog::GetVersion() << '\n';
    return 0;
  }

  std::cout << "Line: " << s << '\n'
    << "Regex: " << r << '\n'
    << '\n';

  std::vector<boost::shared_ptr<ribi::RegexTesterMainDialog> > dialogs;
  //Cannot get my crosscompiler to support -lboost_regex
  {
    boost::shared_ptr<ribi::RegexTesterMainDialog> p(new ribi::RegexTesterBoostXpressiveMainDialog);
    assert(p);
    dialogs.push_back(p);
  }
  #ifndef _WIN32
  {
    boost::shared_ptr<RegexTesterMainDialog> p(new RegexTesterBoostRegexMainDialog);
    assert(p);
    dialogs.push_back(p);
  }
  #endif
  {
    boost::shared_ptr<ribi::RegexTesterMainDialog> p(new ribi::RegexTesterQtMainDialog);
    assert(p);
    dialogs.push_back(p);
  }
  //std::regex not implemented in GCC
  #ifndef __GNUC__
  {
    boost::shared_ptr<ribi::RegexTesterMainDialog> p(new ribi::RegexTesterCpp11MainDialog);
    assert(p);
    dialogs.push_back(p);
  }
  #endif
  //std::tr1::regex not implemented in GCC
  #ifndef __GNUC__
  {
    boost::shared_ptr<ribi::RegexTesterMainDialog> p(new ribi::RegexTesterTr1MainDialog);
    assert(p);
    dialogs.push_back(p);
  }
  #endif

  std::for_each(dialogs.begin(),dialogs.end(),
    [&r, &s](const boost::shared_ptr<ribi::RegexTesterMainDialog> dialog)
    {
      std::cout << "Using: " << dialog->GetUsedImplementation() << '\n';
      std::cout << std::boolalpha
        << "* Regex valid: " << dialog->GetRegexValid(r) << '\n'
        << "* Regex matches line: " << dialog->GetRegexMatchLine(s,r) << '\n'
        << "* Regexes found in line: { ";
      const std::vector<std::string> v = dialog->GetRegexMatches(s,r);
      std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,","));
      std::cout
        << " }\n";
    }
  );
}
