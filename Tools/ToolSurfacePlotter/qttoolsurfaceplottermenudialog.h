//---------------------------------------------------------------------------
/*
SurfacePlotter, plots a bivariate function
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolSurfacePlotter.htm
//---------------------------------------------------------------------------
#ifndef QTTOOLSURFACEPLOTTERMENUDIALOG_H
#define QTTOOLSURFACEPLOTTERMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtToolSurfacePlotterMenuDialog;
}

namespace ribi {

class QtToolSurfacePlotterMenuDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit QtToolSurfacePlotterMenuDialog(QWidget *parent = 0);
  QtToolSurfacePlotterMenuDialog(const QtToolSurfacePlotterMenuDialog&) = delete;
  QtToolSurfacePlotterMenuDialog& operator=(const QtToolSurfacePlotterMenuDialog&) = delete;
  ~QtToolSurfacePlotterMenuDialog() noexcept;
    
private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtToolSurfacePlotterMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLSURFACEPLOTTERMENUDIALOG_H
