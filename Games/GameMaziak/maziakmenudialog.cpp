//---------------------------------------------------------------------------
/*
Maziak, a simple maze game
Copyright (C) 2007-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameMaziak.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "maziakmenudialog.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>


const ribi::About ribi::MaziakMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "Maziak",
    "a simple maze game",
    "the 6th of March 2012",
    "2007-2012",
    "http://www.richelbilderbeek.nl/GameMaziak.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const std::string ribi::MaziakMenuDialog::GetVersion()
{
  return "2.1";
}

const std::vector<std::string> ribi::MaziakMenuDialog::GetVersionHistory()
{
  return
  {
    "2012-03-06: version 2.1: Conformized architecture and naming for ProjectRichelBilderbeek.",
    "2010-07-31: version 2.0: Reprogrammed in Qt Creator, so Maziak is now cross-platform!",
    "2010-02-25: version 1.4: Improved 'Game Over' screen. Added animation in 'Congratulations' screen. Improved enemies' intelligence. Improved maze creation algorithm. Ensured the player is not placed too close to the exit.",
    "2010-02-18: version 1.3: Animated fights. Prevent overlapping sprites. Add 'Instructions' screen in menu. Improved 'Menu' screen",
    "2010-02-17: version 1.2: Animated prisoners. Animated enemies. Animated player. Improved 'Menu' screen. Improved 'About' screen. Added 'What's New?' screen",
    "2010-02-16: version 1.1: Changed graphics to resemble the original Maziacs more. Changed manu screen. Changed 'Game Over' screen. Changed 'Congratulations' screen.",
    "2007-10-22: version 1.0: Initial version"
  };
}

