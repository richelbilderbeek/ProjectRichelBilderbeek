//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
Copyright (C) 2010-2014 Richel Bilderbeek

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

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "pylosboard.h"
#include "pyloscoordinat.h"
#include "pyloscurrentmovestate.h"
#include "pylosgame.h"
#include "pylosmove.h"
#include "pylosplayer.h"
#include "trace.h"

int ribi::PylosMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  std::cout
    << this->GetAbout().GetFileTitle() << " cannot be run in console mode\n"
    << std::endl;
  return 0;
}

const ribi::About ribi::PylosMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Pylos",
    "Pylos/Pyraos game",
    "the 28th of May 2012",
    "2010-2014",
    "http://www.richelbilderbeek.nl/GamePylos.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Pylos::Board version: " + Pylos::Board::GetVersion());
  a.AddLibrary("Pylos::Coordinat version: " + Pylos::Coordinat::GetVersion());
  a.AddLibrary("Pylos::CurrentMoveState version: " + Pylos::CurrentMoveState::GetVersion());
  a.AddLibrary("Pylos::Game version: " + Pylos::Game::GetVersion());
  a.AddLibrary("Pylos::Move version: " + Pylos::Move::GetVersion());
  //a.AddLibrary("Pylos::MustRemoveState version: " + Pylos::MustRemoveState:: enum
  //a.AddLibrary("Pylos::Player version: " + Pylos::Player:: enum
  //a.AddLibrary("Pylos::PositionState version: " + Pylos::PositionState:: enum
  //a.AddLibrary("Pylos::Winner version: " + Pylos::Winner:: enum
  return a;
}

const ribi::Help ribi::PylosMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

const boost::shared_ptr<const ribi::Program> ribi::PylosMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramPylos
  };
  assert(p);
  return p;
}

const std::string ribi::PylosMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::PylosMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-09-22: version 1.0: initial release version",
    "2012-05-28: version 2.0: improved version to work with ProjectRichelBilderbeek"
  };
}

#ifndef NDEBUG
void ribi::PylosMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PylosMenuDialog::Test");
  const boost::shared_ptr<ribi::Pylos::Board> a(
    new ribi::Pylos::BoardAdvanced
  );
  assert(a);
  const boost::shared_ptr<ribi::Pylos::Board> b(
    new ribi::Pylos::BoardBasic
  );
  assert(b);
  Pylos::Coordinat(0,0,0);
  Pylos::CurrentMoveState();
  const boost::shared_ptr<Pylos::Game> g_a(
    new Pylos::Game(a)
  );
  assert(g_a);
  const boost::shared_ptr<Pylos::Game> g_b(
    new Pylos::Game(b)
  );
  assert(g_b);
  Pylos::Move();
  TRACE("Finished ribi::PylosMenuDialog::Test successfully");
}
#endif
