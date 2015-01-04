//---------------------------------------------------------------------------
/*
TestFunctionParser, tool to demonstrate Warp's FunctionParser class
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestFunctionParser.htm
//---------------------------------------------------------------------------
#ifndef QTTESTFUNCTIONPARSERMAINDIALOG_H
#define QTTESTFUNCTIONPARSERMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestFunctionParserMainDialog;
}

namespace ribi {

class QtTestFunctionParserMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestFunctionParserMainDialog(QWidget *parent = 0) noexcept;
  QtTestFunctionParserMainDialog(const QtTestFunctionParserMainDialog&) = delete;
  QtTestFunctionParserMainDialog& operator=(const QtTestFunctionParserMainDialog&) = delete;
  ~QtTestFunctionParserMainDialog() noexcept;

private slots:
  void on_edit_value_textChanged(QString ) noexcept;
  void on_edit_function_textChanged(QString ) noexcept;

private:
  Ui::QtTestFunctionParserMainDialog *ui;
  void Parse() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTFUNCTIONPARSERMAINDIALOG_H
