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
#ifndef WTTICTACTOEGAMEDIALOG_H
#define WTTICTACTOEGAMEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct WtTicTacToeWidget;

struct WtTicTacToeGameDialog : public Wt::WContainerWidget
{
  WtTicTacToeGameDialog(const bool display_close_button = true);
  WtTicTacToeGameDialog(const WtTicTacToeGameDialog&) = delete;
  WtTicTacToeGameDialog& operator=(const WtTicTacToeGameDialog&) = delete;

  boost::signals2::signal<void ()> m_signal_close;
  private:
  Wt::WPushButton * m_button_restart;
  WtTicTacToeWidget * const m_tictactoe;
  void OnClose();
  void OnRestart();
  void OnStateChanged();
};

} //~namespace ribi

#endif // WTTICTACTOEGAMEDIALOG_H
