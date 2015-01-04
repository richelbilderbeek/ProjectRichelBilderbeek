//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
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
//From http://www.richelbilderbeek.nl/GamePylos.htm
//---------------------------------------------------------------------------
#ifndef QTPYLOSWONDIALOG
#define QTPYLOSWONDIALOG

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"

#include "pyloswinner.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPylosWonDialog;
}

namespace ribi {

class QtPylosWonDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPylosWonDialog(QWidget *parent = 0);
  QtPylosWonDialog(const QtPylosWonDialog&) = delete;
  QtPylosWonDialog& operator=(const QtPylosWonDialog&) = delete;
  ~QtPylosWonDialog() noexcept;
  void SetWinner(const pylos::Winner winner);

private:
  Ui::QtPylosWonDialog *ui;
};

} //~namespace ribi

#endif // QTPYLOSWONDIALOG
