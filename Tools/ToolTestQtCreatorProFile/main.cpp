//---------------------------------------------------------------------------
/*
TestQtCreatorProFile, tool to test the QtCreatorProFile class
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
//From http://www.richelbilderbeek.nl/ToolTestQtCreatorProFile.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "qtcreatorprofile.h"
#include "testqtcreatorprofilemenudialog.h"
#include "trace.h"

int main(int argc, char* argv[])
{
  START_TRACE();

  boost::program_options::options_description d("Allowed options for ToolTestQtCreatorProFileConsole");
  std::string filename;

  d.add_options()
      ("about","displays the 'About' information")
      ("filename",
         boost::program_options::value<std::string>(&filename),
         "filename of Qt Creator project (.pro) file")
      ("help","produce this help message")
      ("version","displays the version")
       ;

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

  if (m.count("about"))
  {
    std::cout << TestQtCreatorProFileMenuDialog::GetAbout() << "\n";
    return 0;
  }

  if (m.count("version"))
  {
    std::cout << TestQtCreatorProFileMenuDialog::GetVersion() << "\n";
    return 0;
  }

  if (m.count("filename"))
  {
    if (filename.empty())
    {
      std::cout << "Please specify a filename.\n";
      return 1;
    }
    if (filename.size() < 5)
    {
      std::cout << "Please specify a full Qt Creator (.pro) project filename.\n";
      return 1;
    }
    if (filename.substr(filename.size() - 4,4) != ".pro")
    {
      std::cout << "Please specify a filename ending on .pro.\n";
      return 1;
    }
    if (!boost::filesystem::exists(filename))
    {
      std::cout << "Please specify a Qt Creator (.pro) project filename that exists.\n";
      return 1;
    }
    const boost::shared_ptr<const QtCreatorProFile> p(
      new QtCreatorProFile(filename));
    std::cout << p << '\n';
    return 0;
  }

  //Display the help
  std::cout << d << "\n";
}

