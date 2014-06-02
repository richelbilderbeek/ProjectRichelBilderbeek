//---------------------------------------------------------------------------
/*
TestPolyFileFromPolygons, tests the PolyFileFromPolygons class
Copyright (C) 2014-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestPolyFileFromPolygons.htm
//---------------------------------------------------------------------------
#ifndef QTTESTTRIANGLEMENUDIALOG_H
#define QTTESTTRIANGLEMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestPolyFileFromPolygonsMenuDialog;
}

namespace ribi {

class QtTestPolyFileFromPolygonsMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestPolyFileFromPolygonsMenuDialog(QWidget *parent = 0) noexcept;
  QtTestPolyFileFromPolygonsMenuDialog(const QtTestPolyFileFromPolygonsMenuDialog&) = delete;
  QtTestPolyFileFromPolygonsMenuDialog& operator=(const QtTestPolyFileFromPolygonsMenuDialog&) = delete;
  ~QtTestPolyFileFromPolygonsMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtTestPolyFileFromPolygonsMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTTRIANGLEMENUDIALOG_H
