//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
Copyright (C) 2010-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GamePylos.htm
//---------------------------------------------------------------------------
#include "pylosmenudialog.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "pylosboard.h"
#include "pyloscoordinat.h"
#include "pyloscurrentmovestate.h"
#include "pylosgame.h"
#include "pylosmove.h"
#include "pylosplayer.h"

const ribi::About ribi::PylosMenuDialog::GetAbout() noexcept
{
  About a(
    "Richel Bilderbeek",
    "Pylos",
    "Pylos/Pyraos game",
    "the 28th of May 2012",
    "2010-2012",
    "http://www.richelbilderbeek.nl/GamePylos.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Pylos::Board version: " + Pylos::Board::GetVersion());
  a.AddLibrary("Pylos::Coordinat version: " + Pylos::Coordinat::GetVersion());
  a.AddLibrary("Pylos::CurrentMoveState version: " + Pylos::CurrentMoveState::GetVersion());
  a.AddLibrary("Pylos::Game version: " + Pylos::Game::GetVersion());
  a.AddLibrary("Pylos::Move version: " + Pylos::Move::GetVersion());
  return a;
}

const std::string ribi::PylosMenuDialog::GetVersion() noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::PylosMenuDialog::GetVersionHistory() noexcept
{
  return {
    "2010-09-22: version 1.0: initial release version",
    "2012-05-28: version 2.0: improved version to work with ProjectRichelBilderbeek"
  };
}

