//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#include <iostream>
#include <iterator>

#include <boost/filesystem.hpp>

#ifndef _WIN32
//Do not use Boost.Program_options and Boost.Filesystem together when crosscompiling,
//see .pro file for more detail
#include <boost/program_options.hpp>
#endif

#include "richelbilderbeekprogram.h"
#include "richelbilderbeekmenudialog.h"
#include "trace.h"

void DisplayHelp()
{
  std::cout
    << "Allowed options for ProjectRichelBilderbeekConsole:" << '\n'
    << "--about               display about message" << '\n'
    << "--help                produce this help message" << '\n'
    << "--history             display version history" << '\n'
    << "--licence             display licence" << '\n'
    << "--status              display class statuses" << '\n'
    << "--version             display class versions" << '\n'
    ;

}

int main(int argc, char **argv)
{
  START_TRACE();

  #ifdef _WIN32
  //Do not use Boost.Program_options and Boost.Filesystem together when crosscompiling,
  //see .pro file for more detail
  if (argc == 1)
  {
    DisplayHelp();
    return 0;
  }
  const std::string s = argv[1];
  if (s == "about")
  {
    const std::vector<std::string> v = ribi::RichelBilderbeek::MenuDialog::GetAbout().CreateAboutText();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  }
  else if (s == "help")
  {
    DisplayHelp();
  }
  else if (s == "history")
  {
    const std::vector<std::string> v = ribi::RichelBilderbeek::MenuDialog::GetVersionHistory();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  }
  else if (s == "licence")
  {
    const std::vector<std::string> v = ribi::RichelBilderbeek::MenuDialog::GetAbout().CreateLicenceText();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  }
  else if (s == "status")
  {
    ribi::RichelBilderbeek::MenuDialog d;
    const std::vector<boost::shared_ptr<ribi::RichelBilderbeek::Program> >& v = d.GetPrograms();
    std::for_each(
      v.begin(),v.end(),
      [](const boost::shared_ptr<ribi::RichelBilderbeek::Program>& p)
      {
        std::cout << p.get() << '\n';
      }
    );
  }
  else if (s == "version")
  {
    const std::vector<std::string> v = ribi::RichelBilderbeek::MenuDialog::GetAbout().CreateLibrariesUsedText();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  }
  else
  {
    DisplayHelp();
  }
  #else
  // Declare the supported options.
  boost::program_options::options_description d("Allowed options for ProjectRichelBilderbeekConsole");
  d.add_options()
      ("about",
        "display about message")
      ("help",
        "produce this help message")
      ("history",
         "display version history")
      ("licence",
        "display licence")
      ("status",
        "display class statuses")
      ("version",
        "display class versions");

  boost::program_options::variables_map m;
  boost::program_options::store(
    boost::program_options::parse_command_line(
      argc, argv, d), m);
  boost::program_options::notify(m);

  if (m.count("about"))
  {
    const std::vector<std::string> v = RichelBilderbeek::MenuDialog::GetAbout().CreateAboutText();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  }
  else if (m.count("help"))
  {
    std::cout << d << "\n";
  }
  else if (m.count("history"))
  {
    const std::vector<std::string> v = RichelBilderbeek::MenuDialog::GetVersionHistory();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  }
  else if (m.count("licence"))
  {
    const std::vector<std::string> v = RichelBilderbeek::MenuDialog::GetAbout().CreateLicenceText();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  }
  else if (m.count("status"))
  {
    RichelBilderbeek::MenuDialog d;
    const std::vector<boost::shared_ptr<RichelBilderbeek::Program> >& v = d.GetPrograms();
    std::for_each(
      v.begin(),v.end(),
      [](const boost::shared_ptr<RichelBilderbeek::Program>& p)
      {
        std::cout << p.get() << '\n';
      }
    );
  }
  else if (m.count("version"))
  {
    const std::vector<std::string> v = RichelBilderbeek::MenuDialog::GetAbout().CreateLibrariesUsedText();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  }
  else
  {
    //Invalid use: display the help
    std::cout << d << "\n";
  }
  #endif
}

