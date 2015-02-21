//---------------------------------------------------------------------------
/*
RegexTester, regular expression tester
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
//From http://www.richelbilderbeek.nl/ToolRegexTester.htm
//---------------------------------------------------------------------------
#ifndef QTREGEXTESTERMENUDIALOG_H
#define QTREGEXTESTERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtRegexTesterMenuDialog;
}

namespace ribi {

class QtRegexTesterMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtRegexTesterMenuDialog(QWidget *parent = 0);
  QtRegexTesterMenuDialog(const QtRegexTesterMenuDialog&) = delete;
  QtRegexTesterMenuDialog& operator=(const QtRegexTesterMenuDialog&) = delete;
  ~QtRegexTesterMenuDialog() noexcept;

private:
  Ui::QtRegexTesterMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_quit_clicked();
  void on_button_about_clicked();
  void on_button_cpp11_clicked();
  void on_button_qt_clicked();
  void on_button_boost_regex_clicked();
  void on_button_boost_xpressive_clicked();
};

} //~namespace ribi

#endif // QTREGEXTESTERMENUDIALOG_H
