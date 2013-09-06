//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
Copyright (C) 2011 Richel Bilderbeek

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

#include <QDialog>

namespace Ui {
  class QtTestDialMainDialog;
}

namespace ribi {

class QtTestDialMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestDialMainDialog(QWidget *parent = 0);
  ~QtTestDialMainDialog();

protected:
  

private slots:
  void on_dial_color_valueChanged(int value);

private:
  Ui::QtTestDialMainDialog *ui;

  void DisplayDialColor();
  void DisplayDialValue();
};

} //~namespace ribi

#endif // QTTESTDIALMAINDIALOG_H
