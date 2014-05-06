//---------------------------------------------------------------------------
/*
StaircaseCardCreator, tool to generate staircase cards
Copyright (C) 2014-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolStaircaseCardCreator.htm
//---------------------------------------------------------------------------
#ifndef STAIRCASECARDCREATORMENUDIALOG_H
#define STAIRCASECARDCREATORMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"
//#include "staircasecardcreatorfwd.h"

namespace ribi {
namespace scc {

///GUI independent staircasecardcreator menu dialog
struct MenuDialog : public ::ribi::MenuDialog
{
  MenuDialog();
  ~MenuDialog() noexcept {}
  About GetAbout() const noexcept;
  Help GetHelp() const noexcept;
  boost::shared_ptr<const Program> GetProgram() const noexcept;
  std::string GetVersion() const noexcept;

  std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARDCREATORMENUDIALOG_H
