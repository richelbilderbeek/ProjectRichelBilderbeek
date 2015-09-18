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
#ifndef SFMLTICTACTOEWINNERDIALOG_H
#define SFMLTICTACTOEWINNERDIALOG_H

namespace ribi {
namespace tictactoe {

class SfmlWinnerDialog
{

public:
  explicit SfmlWinnerDialog();
  void SetDraw();
  void SetWinnerCross();
  void SetWinnerCircle();

private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace tictactoe
} //~namespace ribi

#endif // SFMLTICTACTOEWINNERDIALOG_H
