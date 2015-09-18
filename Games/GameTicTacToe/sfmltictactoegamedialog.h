//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game
Copyright (C) 2010-2015 Richel Bilderbeek

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
#ifndef SFMLTICTACTOEGAMEDIALOG_H
#define SFMLTICTACTOEGAMEDIALOG_H
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"


#include <string>

#include <boost/shared_ptr.hpp>

#include "tictactoefwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tictactoe {

struct Widget;

struct SfmlGameDialog
{
  explicit SfmlGameDialog(
    const boost::shared_ptr<Ai>& player1,
    const boost::shared_ptr<Ai>& player2
  );
  SfmlGameDialog(const SfmlGameDialog&) = delete;
  SfmlGameDialog& operator=(const SfmlGameDialog&) = delete;
  static std::string GetVersion() noexcept;

private:
  boost::shared_ptr<Widget> m_tictactoe;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  void HasWinner(const Widget* const);
};

} //~namespace tictactoe
} //~namespace ribi

#endif // SFMLTICTACTOEGAMEDIALOG_H
