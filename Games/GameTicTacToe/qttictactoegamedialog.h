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
#ifndef QTTICTACTOEGAMEDIALOG_H
#define QTTICTACTOEGAMEDIALOG_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtTicTacToeGameDialog;
}

namespace ribi {

struct QtTicTacToeWidget;

class QtTicTacToeGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTicTacToeGameDialog(QWidget *parent = 0);
  QtTicTacToeGameDialog(const QtTicTacToeGameDialog&) = delete;
  QtTicTacToeGameDialog& operator=(const QtTicTacToeGameDialog&) = delete;
  ~QtTicTacToeGameDialog() noexcept;
  static const std::string GetVersion() { return "1.2"; }

private:
  Ui::QtTicTacToeGameDialog *ui;
  boost::shared_ptr<QtTicTacToeWidget> m_tictactoe;

private slots:
  void HasWinner();
};

} //~namespace ribi

#endif // QTTICTACTOEGAMEDIALOG_H
