//---------------------------------------------------------------------------
/*
RandomCode, tool to generate random C++ code
Copyright (C) 2007-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------
#ifndef QTRANDOMCODEMENUDIALOG_H
#define QTRANDOMCODEMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtRandomCodeMenuDialog;
}

namespace ribi {

class QtRandomCodeMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtRandomCodeMenuDialog(QWidget *parent = 0);
  QtRandomCodeMenuDialog(const QtRandomCodeMenuDialog&) = delete;
  QtRandomCodeMenuDialog& operator=(const QtRandomCodeMenuDialog&) = delete;
  ~QtRandomCodeMenuDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtRandomCodeMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();
};

} //~namespace ribi

#endif // QTRANDOMCODEMENUDIALOG_H
