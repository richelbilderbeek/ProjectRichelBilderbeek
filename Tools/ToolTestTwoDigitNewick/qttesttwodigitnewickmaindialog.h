//---------------------------------------------------------------------------
/*
TestTwoDigitNewick, tool to test the two-digit-Newick architecture
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick.htm
//---------------------------------------------------------------------------
#ifndef QTTESTTWODIGITNEWICKDIALOG_H
#define QTTESTTWODIGITNEWICKDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestTwoDigitNewickMainDialog;
}

namespace ribi {

class QtTestTwoDigitNewickMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestTwoDigitNewickMainDialog(QWidget *parent = 0);
  QtTestTwoDigitNewickMainDialog(const QtTestTwoDigitNewickMainDialog&) = delete;
  QtTestTwoDigitNewickMainDialog& operator=(const QtTestTwoDigitNewickMainDialog&) = delete;
  ~QtTestTwoDigitNewickMainDialog() noexcept;

protected:


private:
  Ui::QtTestTwoDigitNewickMainDialog *ui;

private slots:
  void OnAnyChange();
  void OnAboutClick();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTTWODIGITNEWICKDIALOG_H
