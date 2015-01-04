//---------------------------------------------------------------------------
/*
TestQrcFile, tool to test the QrcFile class
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
//From http://www.richelbilderbeek.nl/ToolTestQrcFile.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQRCFILEMAINDIALOG_H
#define QTTESTQRCFILEMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestQrcFileMainDialog;
}

namespace ribi {

class QtTestQrcFileMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQrcFileMainDialog(QWidget *parent = 0);
  QtTestQrcFileMainDialog(const QtTestQrcFileMainDialog&) = delete;
  QtTestQrcFileMainDialog& operator=(const QtTestQrcFileMainDialog&) = delete;
  ~QtTestQrcFileMainDialog() noexcept;

private slots:
  void on_edit_textChanged(const QString &arg1);

private:
  Ui::QtTestQrcFileMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // QTTESTQRCFILEMAINDIALOG_H
