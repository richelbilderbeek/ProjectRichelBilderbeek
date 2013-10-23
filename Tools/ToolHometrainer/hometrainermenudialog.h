//---------------------------------------------------------------------------
/*
Hometrainer, exercise and survey suite
Copyright (C) 2009-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolHometrainer.htm
//---------------------------------------------------------------------------
#ifndef HOMETRAINERMENUDIALOG_H
#define HOMETRAINERMENUDIALOG_H

#include "about.h"

namespace ribi {

///The logic behind the menu dialog
struct HometrainerMenuDialog
{
  ///Create the example exercises
  static void CreateExamples() noexcept;

  ///Execute Hometrainer from the command line
  ///The return code is the error code given back to main
  static int Execute(const int argc, const char* const argv[]) noexcept;

  ///Obtain the about information
  static const About GetAbout() noexcept;

  ///Obtain the version
  static const std::string GetVersion() noexcept;

  ///Obtain the version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Show the command-line options
  static void ShowHelp() noexcept;
};

} //~namespace ribi

#endif // HOMETRAINERMENUDIALOG_H
