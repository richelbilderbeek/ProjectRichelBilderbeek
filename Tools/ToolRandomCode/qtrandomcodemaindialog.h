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
#ifndef QTRANDOMCODEMAINDIALOG_H
#define QTRANDOMCODEMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtRandomCodeMainDialog;
}

namespace ribi {

class QtRandomCodeMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtRandomCodeMainDialog(QWidget *parent = 0);
  QtRandomCodeMainDialog(const QtRandomCodeMainDialog&) = delete;
  QtRandomCodeMainDialog& operator=(const QtRandomCodeMainDialog&) = delete;
  ~QtRandomCodeMainDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtRandomCodeMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_about_clicked();
  void on_button_generate_clicked();
};

} //~namespace ribi

#endif // QTRANDOMCODEMAINDIALOG_H
