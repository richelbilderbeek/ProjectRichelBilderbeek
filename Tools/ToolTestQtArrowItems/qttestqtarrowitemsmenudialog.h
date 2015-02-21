// ---------------------------------------------------------------------------
/*
TestQtArrowItems, tool to test Qt arrow QGraphicsItems
Copyright (C) 2012-2015 Richel Bilderbeek

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
// ---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestQtArrowItems.htm
// ---------------------------------------------------------------------------
#ifndef QTTESTQTARROWITEMSMENUDIALOG_H
#define QTTESTQTARROWITEMSMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestQtArrowItemsMenuDialog;
}

namespace ribi {

class QtTestQtArrowItemsMenuDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQtArrowItemsMenuDialog(QWidget *parent = 0);
  QtTestQtArrowItemsMenuDialog(const QtTestQtArrowItemsMenuDialog&) = delete;
  QtTestQtArrowItemsMenuDialog& operator=(const QtTestQtArrowItemsMenuDialog&) = delete;
  ~QtTestQtArrowItemsMenuDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent * event) noexcept override final;

private:
  Ui::QtTestQtArrowItemsMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_compare_clicked();
  void on_button_quit_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
  void on_button_modify_clicked();
};

} //~namespace ribi

#endif // QTTESTQTARROWITEMSMENUDIALOG_H
