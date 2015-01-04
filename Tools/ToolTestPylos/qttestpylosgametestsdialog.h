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
#ifndef QTTESTPYLOSGAMETESTSDIALOG_H
#define QTTESTPYLOSGAMETESTSDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestPylosGameTestsDialog;
}

namespace ribi {

///DialogTests shows some of the more elaborate tests that
///are performed on the Pylos class
class QtTestPylosGameTestsDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestPylosGameTestsDialog(QWidget *parent = 0);
  QtTestPylosGameTestsDialog(const QtTestPylosGameTestsDialog&) = delete;
  QtTestPylosGameTestsDialog& operator=(const QtTestPylosGameTestsDialog&) = delete;
  ~QtTestPylosGameTestsDialog() noexcept;

private:
  Ui::QtTestPylosGameTestsDialog *ui;
};

} //~namespace ribi

#endif // QTTESTPYLOSGAMETESTSDIALOG_H
