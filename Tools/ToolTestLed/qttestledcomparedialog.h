//---------------------------------------------------------------------------
/*
TestLed, tool to test the Led class
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestLed.htm
//---------------------------------------------------------------------------
#ifndef QTTESTLEDCOMPAREDIALOG_H
#define QTTESTLEDCOMPAREDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestLedCompareDialog;
}


namespace ribi {

class QtTestLedCompareDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestLedCompareDialog(QWidget *parent = 0) noexcept;
  QtTestLedCompareDialog(const QtTestLedCompareDialog&) = delete;
  QtTestLedCompareDialog& operator=(const QtTestLedCompareDialog&) = delete;
  ~QtTestLedCompareDialog() noexcept;

protected:
  

private:
  Ui::QtTestLedCompareDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_slider_valueChanged(int value) noexcept;
};

} //~namespace ribi

#endif // QTTESTLEDCOMPAREDIALOG_H
