//---------------------------------------------------------------------------
/*
MenuDialog, menu dialog class
Copyright (C) 2013-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppMenuDialog.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "menudialog.h"
#include <cassert>
#include <iterator>
#include <iostream>

#include "richelbilderbeekprogram.h"
#pragma GCC diagnostic pop

std::vector<std::string> ribi::MenuDialog::ConvertArguments(
  const int argc, const char * const argv[]) noexcept
{
   std::vector<std::string> v;
   v.reserve(argc);
   for (int i=0; i!=argc; ++i)
   {
     v.push_back(std::string(argv[i]));
   }
   assert(argc == static_cast<int>(v.size()));
   return v;
}

int ribi::MenuDialog::Execute(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    return ExecuteSpecific(argv);
  }
  const std::string s = argv[1];
  if (s == "--about" || s == "-a")
  {
    const std::vector<std::string> v { GetAbout().CreateAboutText() };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    std::cout
      << "\n"
      << "Source code built on "
      << __DATE__
      << " "
      << __TIME__
      << " ("
    #ifdef NDEBUG
      << "release"
    #else
      << "debug"
    #endif
      << " version)"
      << std::endl;
    return 0;
  }
  else if (s == "--help" || s == "-h")
  {
    std::cout << GetHelp() << '\n';
    return 0;
  }
  else if (s == "--history" || s == "-i")
  {
    const std::vector<std::string> v { GetVersionHistory() };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  else if (s == "--licence" || s == "-l")
  {
    const std::vector<std::string> v { GetAbout().CreateLicenceText() };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  else if (s == "--version" || s == "-v")
  {
    const std::vector<std::string> v = { GetAbout().CreateLibrariesUsedText() };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  return ExecuteSpecific(argv);
}
