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
#ifndef QTTESTFUNCTIONPARSERMENUDIALOG_H
#define QTTESTFUNCTIONPARSERMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestFunctionParserMenuDialog;
}

namespace ribi {

class QtTestFunctionParserMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestFunctionParserMenuDialog(QWidget *parent = 0) noexcept;
  QtTestFunctionParserMenuDialog(const QtTestFunctionParserMenuDialog&) = delete;
  QtTestFunctionParserMenuDialog& operator=(const QtTestFunctionParserMenuDialog&) = delete;
  ~QtTestFunctionParserMenuDialog() noexcept;

private slots:
  void on_button_start_clicked() noexcept;
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;

private:
  Ui::QtTestFunctionParserMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTFUNCTIONPARSERMENUDIALOG_H
