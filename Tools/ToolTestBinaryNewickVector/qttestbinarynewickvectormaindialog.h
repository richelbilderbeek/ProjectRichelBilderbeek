//---------------------------------------------------------------------------
/*
TestBinaryNewickVector, GUI tool to test BinaryNewickVector
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
//From http://www.richelbilderbeek.nl/ToolTestBinaryNewickVector.htm
//---------------------------------------------------------------------------
#ifndef DIALOGTESTBINARYNEWICKVECTOR_H
#define DIALOGTESTBINARYNEWICKVECTOR_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestBinaryNewickVectorMainDialog;
}

namespace ribi {

class QtTestBinaryNewickVectorMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestBinaryNewickVectorMainDialog(QWidget *parent = 0);
  QtTestBinaryNewickVectorMainDialog(const QtTestBinaryNewickVectorMainDialog&) = delete;
  QtTestBinaryNewickVectorMainDialog& operator=(const QtTestBinaryNewickVectorMainDialog&) = delete;
  ~QtTestBinaryNewickVectorMainDialog() noexcept;

private:
  Ui::QtTestBinaryNewickVectorMainDialog *ui;
  QTimer * m_timer;
private slots:
  void on_button_calculate_clicked();
  void on_button_about_clicked();
  void on_button_demo_clicked();
  void OnAnyChange();
  void OnDemoTick();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // DIALOGTESTBINARYNEWICKVECTOR_H
