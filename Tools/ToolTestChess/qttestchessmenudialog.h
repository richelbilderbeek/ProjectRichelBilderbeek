//---------------------------------------------------------------------------
/*
TestChess, program to test my chess classes
Copyright (C) 2012-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestChess.htm
//---------------------------------------------------------------------------
#ifndef QTTESTCHESSMENUDIALOG_H
#define QTTESTCHESSMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestChessMenuDialog;
}

namespace ribi {

class QtTestChessMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestChessMenuDialog(QWidget *parent = 0);
  QtTestChessMenuDialog(const QtTestChessMenuDialog&) = delete;
  QtTestChessMenuDialog& operator=(const QtTestChessMenuDialog&) = delete;
  ~QtTestChessMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_view_resources_clicked();
  void on_button_test_board_clicked();
  void on_button_test_game_clicked();

private:
  Ui::QtTestChessMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTCHESSMENUDIALOG_H
