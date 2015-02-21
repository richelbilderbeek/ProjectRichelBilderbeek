//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestDial.htm
//---------------------------------------------------------------------------
#ifndef QTTESTDIALMAINDIALOG_H
#define QTTESTDIALMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestDialMainDialog;
}

namespace ribi {

class QtTestDialMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestDialMainDialog(QWidget *parent = 0) noexcept;
  QtTestDialMainDialog(const QtTestDialMainDialog&) = delete;
  QtTestDialMainDialog& operator=(const QtTestDialMainDialog&) = delete;
  ~QtTestDialMainDialog() noexcept;

protected:
  

private slots:
  void on_box_radius_valueChanged(int arg1);
  void on_dial_color_valueChanged(int value) noexcept;

private:
  Ui::QtTestDialMainDialog *ui;

  void DisplayDialAsText() noexcept;
  void DisplayDialColor() noexcept;
  void DisplayDialValue() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTDIALMAINDIALOG_H
