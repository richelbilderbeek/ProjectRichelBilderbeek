//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
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
//From http://www.richelbilderbeek.nl/GamePylos.htm
//---------------------------------------------------------------------------
#ifndef QTPYLOSWONDIALOG
#define QTPYLOSWONDIALOG

#include <QDialog>

#include "pyloswinner.h"

namespace Ui {
  class QtPylosWonDialog;
}

namespace ribi {

class QtPylosWonDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtPylosWonDialog(QWidget *parent = 0);
  ~QtPylosWonDialog();
  void SetWinner(const Pylos::Winner winner);

private:
  Ui::QtPylosWonDialog *ui;
};

} //~namespace ribi

#endif // QTPYLOSWONDIALOG
