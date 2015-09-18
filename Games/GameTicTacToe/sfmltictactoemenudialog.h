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
#ifndef SFMLTICTACTOEMENUDIALOG_H
#define SFMLTICTACTOEMENUDIALOG_H

namespace ribi {
namespace tictactoe {

struct SfmlMenuDialog
{
  explicit SfmlMenuDialog();
  SfmlMenuDialog(const SfmlMenuDialog&) = delete;
  SfmlMenuDialog& operator=(const SfmlMenuDialog&) = delete;

private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  void on_button_quit_clicked();
  void on_button_about_clicked();
  void on_button_start_clicked();
};

} //~namespace tictactoe
} //~namespace ribi

#endif // SFMLTICTACTOEMENUDIALOG_H
