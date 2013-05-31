//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
Copyright (C) 2010-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifndef QTTESTPYLOSRANDOMPLAYDIALOG_H
#define QTTESTPYLOSRANDOMPLAYDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
class QtTestPylosRandomPlayDialog;
}
//---------------------------------------------------------------------------
class QtTestPylosRandomPlayDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit QtTestPylosRandomPlayDialog(QWidget *parent = 0);
  ~QtTestPylosRandomPlayDialog();
    
private slots:

    void on_button_start_clicked();


    void on_edit_n_games_textChanged(const QString &arg1);

private:
  Ui::QtTestPylosRandomPlayDialog *ui;
};
//---------------------------------------------------------------------------
#endif // QTTESTPYLOSRANDOMPLAYDIALOG_H
