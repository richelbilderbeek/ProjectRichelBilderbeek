//---------------------------------------------------------------------------
/*
TestPolyFile, tool to test the PolyFile class
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestPolyFile.htm
//---------------------------------------------------------------------------
#ifndef QTTESTPOLYFILEMAINDIALOG_H
#define QTTESTPOLYFILEMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestPolyFileMainDialog;
}

namespace ribi {

class QtTestPolyFileMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestPolyFileMainDialog(QWidget *parent = 0);
  QtTestPolyFileMainDialog(const QtTestPolyFileMainDialog&) = delete;
  QtTestPolyFileMainDialog& operator=(const QtTestPolyFileMainDialog&) = delete;
  ~QtTestPolyFileMainDialog() noexcept;

private slots:
  void on_edit_textChanged(const QString &arg1);

private:
  Ui::QtTestPolyFileMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // QTTESTPOLYFILEMAINDIALOG_H
