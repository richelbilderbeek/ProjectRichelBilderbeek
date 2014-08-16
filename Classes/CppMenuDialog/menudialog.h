//---------------------------------------------------------------------------
/*
MenuDialog, menu dialog class
Copyright (C) 2013-2014 Richel Bilderbeek

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
#ifndef RIBI_MENUDIALOG_H
#define RIBI_MENUDIALOG_H

#include <vector>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "about.h"
#include "help.h"
#pragma GCC diagnostic pop

namespace ribi {

struct Program;

///Class for all ProjectRichelBilderbeek menu dialogs
struct MenuDialog
{
  MenuDialog() noexcept {}

  virtual ~MenuDialog() noexcept {}

  ///Convert the C style array and string to C++ equivalents
  ///This is used when menu
  static std::vector<std::string> ConvertArguments(const int argc, const char * const argv[]) noexcept;

  ///Start the command line version
  ///First performs a default parse, then passed arguments on to ExecuteSpecific
  ///Returns the error code to give back to the operatings system
  ///Make it a non-const member function: a menu is allowed to have state
  int Execute(const std::vector<std::string>& argv) noexcept;

  ///Obtain the About information of this class
  virtual About GetAbout() const noexcept = 0;

  ///Obtain the help information of this class
  virtual Help GetHelp() const noexcept = 0;

  ///Obtain information about the program
  virtual boost::shared_ptr<const Program> GetProgram() const noexcept = 0;

  ///Obtain the version of this class
  virtual std::string GetVersion() const noexcept = 0;

  ///Obtain the version history of this class
  virtual std::vector<std::string> GetVersionHistory() const noexcept = 0;

  protected:
  ///When Execute has done the default parse, the arguments are passed to ExecuteSpecific.
  ///Here the program itself is called.
  ///Returns the error code to give back to the operatings system
  ///Make it a non-const member function: a menu is allowed to have state
  virtual int ExecuteSpecific(const std::vector<std::string>& argv) noexcept = 0;

};

} //namespace ribi

#endif // RIBI_MENUDIALOG_H
