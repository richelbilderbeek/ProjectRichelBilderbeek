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
#ifndef QTTESTCHESSGAMEDIALOG_H
#define QTTESTCHESSGAMEDIALOG_H

#include "qthideandshowdialog.h"

struct QModelIndex;

namespace Ui {
class QtTestChessGameDialog;
}

namespace ribi {

class QtTestChessGameDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestChessGameDialog(QWidget *parent = 0);
  QtTestChessGameDialog(const QtTestChessGameDialog&) = delete;
  QtTestChessGameDialog& operator=(const QtTestChessGameDialog&) = delete;
  ~QtTestChessGameDialog() noexcept;

private slots:
  void on_list_moves_doubleClicked(const QModelIndex &index);

private:
  Ui::QtTestChessGameDialog *ui;

  void OnChessboardChanged();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTCHESSGAMEDIALOG_H
