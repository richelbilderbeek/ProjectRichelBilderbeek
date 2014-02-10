//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game
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
//From http://www.richelbilderbeek.nl/GameTicTacToe.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "tictactoemenudialog.h"

#include <cassert>
#include <iostream>

#include "textcanvas.h"
#include "tictactoe.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TicTacToeMenuDialog::TicTacToeMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TicTacToeMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  TicTacToe t;
  std::cout << (*t.ToTextCanvas()) << std::endl;
  while (t.GetWinner() == TicTacToe::no_winner)
  {
    const int x = (std::rand() >> 4) % 3;
    const int y = (std::rand() >> 4) % 3;
    if (t.CanDoMove(x,y))
    {
      t.DoMove(x,y);
      std::cout << (*t.ToTextCanvas()) << std::endl;
    }
  }
  return 0;
}

const ribi::About ribi::TicTacToeMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TicTacToe",
    "tic-tac-toe game",
    "the 10th of February 2014",
    "2010-2014",
    "http://www.richelbilderbeek.nl/GameTicTacToe.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("TicTacToe version: " + TicTacToe::GetVersion());
  return a;
}

const ribi::Help ribi::TicTacToeMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::TicTacToeMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramTicTacToe
  };
  assert(p);
  return p;
}

const std::string ribi::TicTacToeMenuDialog::GetVersion() const noexcept
{
  return "1.6";
}

const std::vector<std::string> ribi::TicTacToeMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-09-24: Version 1.0: initial version",
    "2010-11-20: Version 1.1: fixed menu",
    "2011-01-07: version 1.2: merge with Wt TicTacToe game",
    "2011-01-07: version 1.3: seperated wtmain.cpp in multiple units",
    "2011-04-15: version 1.4: major architectural changes",
    "2011-04-16: version 1.5: added use of WtAutoConfig (for web application)"
    "2014-02-10: version 1.6: added retro version"
  };
}


#ifndef NDEBUG
void ribi::TicTacToeMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TicTacToeMenuDialog::Test");
  TRACE("Finished ribi::TicTacToeMenuDialog::Test successfully");
}
#endif
