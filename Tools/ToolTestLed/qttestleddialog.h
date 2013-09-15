//---------------------------------------------------------------------------
/*
TestLed, tool to test the Led class
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
//From http://www.richelbilderbeek.nl/ToolTestLed.htm
//---------------------------------------------------------------------------
#ifndef QTTESTLEDDIALOG_H
#define QTTESTLEDDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestLedDialog;
}


namespace ribi {

class QtTestLedDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestLedDialog(QWidget *parent = 0);
  QtTestLedDialog(const QtTestLedDialog&) = delete;
  QtTestLedDialog& operator=(const QtTestLedDialog&) = delete;
  ~QtTestLedDialog();

protected:
  

private:
  Ui::QtTestLedDialog *ui;

private slots:
    void on_button_about_clicked();
    void on_slider_valueChanged(int value);
};

} //~namespace ribi

#endif // QTTESTLEDDIALOG_H
