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
#ifndef QTTESTCHESSBOARDDIALOG_H
#define QTTESTCHESSBOARDDIALOG_H

#include "qthideandshowdialog.h"
#include "chessfwd.h"

struct QModelIndex;

namespace Ui {
  class QtTestChessBoardDialog;
}

namespace ribi {
class QtTestChessBoardDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestChessBoardDialog(QWidget *parent = 0);
  QtTestChessBoardDialog(const QtTestChessBoardDialog&) = delete;
  QtTestChessBoardDialog& operator=(const QtTestChessBoardDialog&) = delete;
  ~QtTestChessBoardDialog() noexcept;

private slots:
  void on_list_moves_doubleClicked(const QModelIndex &index);

  void on_radio_white_clicked();

  void on_radio_black_clicked();

private:
  Ui::QtTestChessBoardDialog *ui;

  void OnChessboardChanged();
};

} //~namespace ribi

#endif // QTTESTCHESSBOARDDIALOG_H
