//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#include "beerwantermenudialog.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

const ribi::About ribi::BeerWanterMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "BeerWanter",
    "a simple game",
    "the 13th of July 2013",
    "2005-2013",
    "http://www.richelbilderbeek.nl/GameBeerWanter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const std::string ribi::BeerWanterMenuDialog::GetVersion()
{
  return "7.1";
}

const std::vector<std::string> ribi::BeerWanterMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2005-11-16: version 1.0: (at that time called) 'Beerwanter 1' was programmed in C++ using the C++ Builder IDE during a 'Spass programmieren' session, which made BeerWanter a game for Windows users only.");
  v.push_back("2005-11-18: version 2.0: (at that time called) 'Beerwanter 2' was programmed after the success of BeerWanter 1.0. The game was made tougher.");
  v.push_back("2005-11-22: version 3.0: (at that time called) 'Beerwanter 3' was programmed after the success of BeerWanter 2.0. The game was made even tougher.");
  v.push_back("2010-06-23: version 4.0: port code to Qt Creator, BeerWanter is now cross-platform. The game its name is changed back to 'BeerWanter'.");
  v.push_back("2010-06-24: version 5.0: improved the GUI, changed the beer sprite to an adaptation of my favorite beer.");
  v.push_back("2010-10-10: version 5.1: (temporary NDS-only fork) start of port to NDS.");
  v.push_back("2010-10-11: version 5.2: BeerWanter is one project again and build for NDS, Ubuntu and Windows.");
  v.push_back("2010-12-19: version 6.0: seperated project files for NDS, Ubuntu and Windows development. Preparation for seperating game logic from GUI.");
  v.push_back("2010-12-23: version 6.1: added ClickWilBeSuccess method, fixed bug in BeerWanterMainDialog::ShakeWindow");
  v.push_back("2012-03-06: version 7.0: added menu, conformized project architecture for ProjectRichelBilderbeek");
  v.push_back("2013-07-13: version 7.1: added libcvautomation script to beat the game, improved desktop menu and about screen");
  return v;
}
