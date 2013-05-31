//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
Copyright (C) 2012-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/program_options.hpp>

#include "createqtprojectzipfilemenudialog.h"
#include "qtcreatorprofilezipscript.h"
#include "qtcreatorprofile.h"
#include "trace.h"

int main(int argc, char* argv[])
{
  START_TRACE();

  // Declare the supported options.
  boost::program_options::options_description d("Allowed options for CreateQtProjectZipFile");

  std::string source_folder;
  std::string target_filename;

  d.add_options()
      ("about","displays the 'About' information")
      ("help","produce this help message")
      ("source_folder",
         boost::program_options::value<std::string>(&source_folder),
         "Source folder containing one or more .pro files, must start with '../../'")
      ("target_filename",
         boost::program_options::value<std::string>(&target_filename)->default_value("zip.sh"),
         "the generated script's designed filename")
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
    std::cout
      << "\n"
      << "Example use: \n"
      << "./ToolCreateQtProjectZipFileConsole --source_folder ../../Projects/ProjectRichelBilderbeek\n";
    return 0;
  }

  if (m.count("about"))
  {
    std::cout << CreateQtProjectZipFile::MenuDialog::GetAbout() << "\n";
    return 0;
  }

  if (m.count("version"))
  {
    std::cout << CreateQtProjectZipFile::MenuDialog::GetVersion() << "\n";
    return 0;
  }

  if (source_folder.empty())
  {
    std::cout << "Please submit a source folder or use '--help'.\n";
    std::cout
      << "\n"
      << "Example use: \n"
      << "./ToolCreateQtProjectZipFileConsole --source_folder ../../Projects/ProjectRichelBilderbeek\n";
    return 0;
  }

  if (source_folder.size() < 6 || source_folder.substr(0,6) != std::string("../../"))
  {
    std::cout << "Please submit a source folder that starts with '../../'.\n";
    std::cout
      << "\n"
      << "Example use: \n"
      << "./ToolCreateQtProjectZipFileConsole --source_folder ../../Projects/ProjectRichelBilderbeek\n";
    return 0;
  }

  const std::string script = QtCreatorProFileZipScript::CreateScript(source_folder);

  std::ofstream f(target_filename.c_str());
  f << script;

  #ifndef NDEBUG
  std::cout << f;
  #endif
}

