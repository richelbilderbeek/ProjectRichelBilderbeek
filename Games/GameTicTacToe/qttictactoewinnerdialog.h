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
#ifndef QTTICTACTOEWINNERDIALOG_H
#define QTTICTACTOEWINNERDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTicTacToeWinnerDialog;
}

namespace ribi {
namespace tictactoe {

class QtTicTacToeWinnerDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTicTacToeWinnerDialog(QWidget *parent = 0);
  QtTicTacToeWinnerDialog(const QtTicTacToeWinnerDialog&) = delete;
  QtTicTacToeWinnerDialog& operator=(const QtTicTacToeWinnerDialog&) = delete;
  ~QtTicTacToeWinnerDialog() noexcept;
  void SetDraw();
  void SetWinnerCross();
  void SetWinnerCircle();

private:
  Ui::QtTicTacToeWinnerDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace tictactoe
} //~namespace ribi

#endif // QTTICTACTOEWINNERDIALOG_H
