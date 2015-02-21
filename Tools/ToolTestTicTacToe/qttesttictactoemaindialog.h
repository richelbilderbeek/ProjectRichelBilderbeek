//---------------------------------------------------------------------------
/*
TestTicTacToe, tool to test the TicTacToe class
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestTicTacToe.htm
//---------------------------------------------------------------------------
#ifndef QTTESTTICTACTOEMAINDIALOG_H
#define QTTESTTICTACTOEMAINDIALOG_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "tictactoefwd.h"
#pragma GCC diagnostic pop

struct QTableWidget;

namespace Ui {
  class QtTestTicTacToeMainDialog;
}

namespace ribi {
namespace tictactoe {

class QtTestTicTacToeMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestTicTacToeMainDialog(
    const boost::shared_ptr<Ai>& player1,
    const boost::shared_ptr<Ai>& player2,
    QWidget *parent = 0
  );
  QtTestTicTacToeMainDialog(const QtTestTicTacToeMainDialog&) = delete;
  QtTestTicTacToeMainDialog& operator=(const QtTestTicTacToeMainDialog&) = delete;
  ~QtTestTicTacToeMainDialog() noexcept;

private:
  Ui::QtTestTicTacToeMainDialog *ui;
  QtCanvas * m_canvas;
  QtTicTacToeWidget * m_tictactoewidget;
  QTimer * m_timer;

  void OnStateChange(QtTicTacToeWidget* w = nullptr);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnTick();
  void on_button_restart_clicked();
  void on_button_auto_play_clicked();

};


} //~namespace tictactoe
} //~namespace ribi

#endif // QTTESTTICTACTOEMAINDIALOG_H
