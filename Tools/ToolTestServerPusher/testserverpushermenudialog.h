//---------------------------------------------------------------------------
/*
TestServerPusher, tool to test WtServerPusher
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestServerPusher.htm
//---------------------------------------------------------------------------
#ifndef TESTSERVERPUSHERMENUDIALOG_H
#define TESTSERVERPUSHERMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {
namespace ToolTestServerPusher {

///The GUI independent part of the menu
struct MenuDialog
{
  ///Get this class its version
  static std::string GetVersion();

  ///Get this class its version history
  static TODOnHistory();

  ///Get this class its About
  static const About GetAbout();
};

} //~namespace ToolTestServerPusher
} //~namespace ribi

#endif // TESTSERVERPUSHERMENUDIALOG_H
