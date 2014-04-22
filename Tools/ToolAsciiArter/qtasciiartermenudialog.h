//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------
#ifndef QTASCIIARTERMENUDIALOG_H
#define QTASCIIARTERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtAsciiArterMenuDialog;
}

namespace ribi {

class QtAsciiArterMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtAsciiArterMenuDialog(QWidget *parent = 0);
  QtAsciiArterMenuDialog(const QtAsciiArterMenuDialog&) = delete;
  QtAsciiArterMenuDialog& operator=(const QtAsciiArterMenuDialog&) = delete;
  ~QtAsciiArterMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtAsciiArterMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTASCIIARTERMENUDIALOG_H
