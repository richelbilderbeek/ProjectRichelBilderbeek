//---------------------------------------------------------------------------
/*
WtTicTacToeWidget, Wt widget to display the TicTacToe class
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtTicTacToeWidget.htm
//---------------------------------------------------------------------------
#ifndef WTTICTACTOEWIDGET_H
#define WTTICTACTOEWIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/signals2.hpp>

#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>

#include "tictactoewidget.h"
#pragma GCC diagnostic pop

namespace ribi {


struct WtTicTacToeWidget : public Wt::WPaintedWidget
{
  WtTicTacToeWidget();
  boost::signals2::signal<void ()> m_signal_has_winner;
  boost::signals2::signal<void ()> m_signal_state_changed;
  tictactoe::Winner GetWinner() const noexcept;
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
  void Restart();
  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice);
  private:
  boost::shared_ptr<tictactoe::Widget> m_tictactoe;
  int GetWidth() const;
  int GetHeight() const;
  void OnClicked(const Wt::WMouseEvent& e);
};

} //~namespace ribi

#endif // WTTICTACTOEWIDGET_H
