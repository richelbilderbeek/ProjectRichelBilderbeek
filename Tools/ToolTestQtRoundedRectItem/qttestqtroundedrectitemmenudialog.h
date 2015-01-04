//---------------------------------------------------------------------------
/*
TestQtRoundedRectItem, tool to test QtRoundedRectItem
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQTROUNDEDRECTITEMMENUDIALOG_H
#define QTTESTQTROUNDEDRECTITEMMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestQtRoundedRectItemMenuDialog;
}

namespace ribi {

class QtTestQtRoundedRectItemMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQtRoundedRectItemMenuDialog(QWidget *parent = 0);
  QtTestQtRoundedRectItemMenuDialog(const QtTestQtRoundedRectItemMenuDialog&) = delete;
  QtTestQtRoundedRectItemMenuDialog& operator=(const QtTestQtRoundedRectItemMenuDialog&) = delete;
  ~QtTestQtRoundedRectItemMenuDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtTestQtRoundedRectItemMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_modify_clicked();
  void on_button_quit_clicked();
  void on_button_compare_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDRECTITEMMENUDIALOG_H
