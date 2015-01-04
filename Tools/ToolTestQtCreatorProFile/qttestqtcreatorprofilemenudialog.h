//---------------------------------------------------------------------------
/*
TestQtCreatorProFile, tool to test the QtCreatorProFile class
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
//From http://www.richelbilderbeek.nl/ToolTestQtCreatorProFile.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQTCREATORPROFILEMENUDIALOG_H
#define QTTESTQTCREATORPROFILEMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtTestQtCreatorProFileMenuDialog;
}

namespace ribi {

class QtTestQtCreatorProFileMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQtCreatorProFileMenuDialog(QWidget *parent = 0);
  QtTestQtCreatorProFileMenuDialog(const QtTestQtCreatorProFileMenuDialog&) = delete;
  QtTestQtCreatorProFileMenuDialog& operator=(const QtTestQtCreatorProFileMenuDialog&) = delete;
  ~QtTestQtCreatorProFileMenuDialog() noexcept;

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestQtCreatorProFileMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTQTCREATORPROFILEMENUDIALOG_H
