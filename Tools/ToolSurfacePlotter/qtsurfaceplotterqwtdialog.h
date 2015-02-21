//---------------------------------------------------------------------------
/*
SurfacePlotter, plots a bivariate function
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
//From http://www.richelbilderbeek.nl/ToolSurfacePlotter.htm
//---------------------------------------------------------------------------
#ifndef QTSURFACEPLOTTERQWTDIALOG_H
#define QTSURFACEPLOTTERQWTDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSurfacePlotterQwtDialog;
}

namespace ribi {

struct QwtSurfacePlotterPlot;

class QtSurfacePlotterQwtDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtSurfacePlotterQwtDialog(QWidget *parent = 0);
  QtSurfacePlotterQwtDialog(const QtSurfacePlotterQwtDialog&) = delete;
  QtSurfacePlotterQwtDialog& operator=(const QtSurfacePlotterQwtDialog&) = delete;
  ~QtSurfacePlotterQwtDialog() noexcept;
    
private slots:
  void keyPressEvent(QKeyEvent *event);
  void OnAnyChange();

private:
  Ui::QtSurfacePlotterQwtDialog *ui;
  QwtSurfacePlotterPlot * const m_plot;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSURFACEPLOTTERQWTDIALOG_H
