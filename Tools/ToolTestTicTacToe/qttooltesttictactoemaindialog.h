//---------------------------------------------------------------------------
/*
TestTicTacToe, tool to test the TicTacToe class
Copyright (C) 2011-2013 Richel Bilderbeek

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

#include "qthideandshowdialog.h"


struct QTableWidget;

namespace Ui {
  class QtTestTicTacToeMainDialog;
}

namespace ribi {

struct QtTicTacToeWidget;

class QtTestTicTacToeMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestTicTacToeMainDialog(QWidget *parent = 0);
  QtTestTicTacToeMainDialog(const QtTestTicTacToeMainDialog&) = delete;
  QtTestTicTacToeMainDialog& operator=(const QtTestTicTacToeMainDialog&) = delete;
  ~QtTestTicTacToeMainDialog() noexcept;

private:
  Ui::QtTestTicTacToeMainDialog *ui;
  QtTicTacToeWidget * m_tictactoewidget;
  QTimer * m_timer;

private slots:
  void OnPlay();
  void OnRestart();
  void OnStateChange();
  void OnTick();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

///SetReadOnlyTableWidget makes the QTableWidget read-only.
///From http://www.richelbilderbeek.nl/CppSetReadOnlyTableWidget.htm
void SetReadOnlyTableWidget(QTableWidget * const t);

} //~namespace ribi

#endif // QTTESTTICTACTOEMAINDIALOG_H
