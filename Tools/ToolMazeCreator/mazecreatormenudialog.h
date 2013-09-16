//---------------------------------------------------------------------------
/*
MazeCreator, creates a maze and displays it on screen.
Copyright (C) 2007-2012 Richel Bilderbeek

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
//From hhtp://www.richelbilderbeek.nl/ToolMazeCreator.htm
//---------------------------------------------------------------------------
#ifndef MAZECREATORMENUDIALOG_H
#define MAZECREATORMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {

///MazeCreatorMenuDialog contains the MazeCreator menu dialog
struct MazeCreatorMenuDialog
{
  static const About GetAbout() noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
};

///From http://www.richelbilderbeek.nl/CppIntToStr.htm
const std::string IntToStr(const int x);

} //~namespace ribi

#endif // MAZECREATORMENUDIALOG_H
