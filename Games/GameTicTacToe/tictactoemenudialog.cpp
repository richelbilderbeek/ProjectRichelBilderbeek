//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game
Copyright (C) 2010-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameTicTacToe.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "tictactoemenudialog.h"


#include "tictactoe.h"

const ribi::About ribi::TicTacToeMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TicTacToe",
    "tic-tac-toe game",
    "the 16th of April 2011",
    "2010-2011",
    "http://www.richelbilderbeek.nl/GameTicTacToe.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("TicTacToe version: " + TicTacToe::GetVersion());
  return a;
}

const std::string ribi::TicTacToeMenuDialog::GetVersion()
{
  return "1.5";
}

const std::vector<std::string> ribi::TicTacToeMenuDialog::GetVersionHistory()
{
  return {
    "2010-09-24: Version 1.0: initial version",
    "2010-11-20: Version 1.1: fixed menu",
    "2011-01-07: version 1.2: merge with Wt TicTacToe game",
    "2011-01-07: version 1.3: seperated wtmain.cpp in multiple units",
    "2011-04-15: version 1.4: major architectural changes",
    "2011-04-16: version 1.5: added use of WtAutoConfig (for web application)"
  };
}

