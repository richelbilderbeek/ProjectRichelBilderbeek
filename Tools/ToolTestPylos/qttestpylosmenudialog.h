//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
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
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifndef QTTESTPYLOSMENUDIALOG_H
#define QTTESTPYLOSMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestPylosMenuDialog;
}

namespace ribi {
namespace pylos {

class QtTestPylosMenuDialog : public QtHideAndShowDialog
{
    Q_OBJECT

public:
  explicit QtTestPylosMenuDialog(QWidget *parent = 0);
  QtTestPylosMenuDialog(const QtTestPylosMenuDialog&) = delete;
  QtTestPylosMenuDialog& operator=(const QtTestPylosMenuDialog&) = delete;
  ~QtTestPylosMenuDialog() noexcept;

private slots:
  void on_button_test_board_clicked();
  void on_button_test_game_clicked();
  void on_button_show_game_tests_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_random_play_clicked();

private:
  Ui::QtTestPylosMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace pylos
} //~namespace ribi

#endif // QTTESTPYLOSMENUDIALOG_H
