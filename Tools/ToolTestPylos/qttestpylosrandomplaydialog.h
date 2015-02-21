//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
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
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifndef QTTESTPYLOSRANDOMPLAYDIALOG_H
#define QTTESTPYLOSRANDOMPLAYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestPylosRandomPlayDialog;
}


namespace ribi {
namespace pylos {

class QtTestPylosRandomPlayDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtTestPylosRandomPlayDialog(QWidget *parent = 0);
  QtTestPylosRandomPlayDialog(const QtTestPylosRandomPlayDialog&) = delete;
  QtTestPylosRandomPlayDialog& operator=(const QtTestPylosRandomPlayDialog&) = delete;
  ~QtTestPylosRandomPlayDialog() noexcept;
    
private slots:
    void on_button_start_clicked();
    void on_edit_n_games_textChanged(const QString &arg1);

private:
  Ui::QtTestPylosRandomPlayDialog *ui;
};

} //~namespace pylos
} //~namespace ribi

#endif // QTTESTPYLOSRANDOMPLAYDIALOG_H
