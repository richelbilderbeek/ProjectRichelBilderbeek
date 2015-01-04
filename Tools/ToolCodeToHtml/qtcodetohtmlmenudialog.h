//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#ifndef QTCODETOHTMLMENUDIALOG_H
#define QTCODETOHTMLMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtCodeToHtmlMenuDialog;
}

namespace ribi {
namespace c2h {

class QtCodeToHtmlMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtCodeToHtmlMenuDialog(QWidget *parent = 0) noexcept;
  QtCodeToHtmlMenuDialog(const QtCodeToHtmlMenuDialog&) = delete;
  QtCodeToHtmlMenuDialog& operator=(const QtCodeToHtmlMenuDialog&) = delete;
  ~QtCodeToHtmlMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtCodeToHtmlMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
  void on_button_test_1_clicked();
  void on_button_test_2_clicked();
  void on_button_test_3_clicked();
};

} //~namespace c2h
} //~namespace ribi

#endif // QTCODETOHTMLMENUDIALOG_H
