
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

//From hhtp://www.richelbilderbeek.nl/ToolMazeCreator.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "mazecreatormenudialog.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>


const About MazeCreatorMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "MazeCreator",
    "creates a maze and displays it on screen",
    "the 6th of March 2012",
    "2007-2012",
    "http://www.richelbilderbeek.nl/ToolMazeCreator.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const std::string MazeCreatorMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> MazeCreatorMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2007-xx-xx: version 1.0: initial version.");
  v.push_back("2012-03-06: version 1.1: added versioning. Added menu screen.");
  return v;
}

