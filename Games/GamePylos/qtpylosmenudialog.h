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
#ifndef QTPYLOSMENUDIALOG
#define QTPYLOSMENUDIALOG

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPylosMenuDialog;
}

namespace ribi {
namespace pylos {

class QtPylosMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPylosMenuDialog(QWidget *parent = 0);
  QtPylosMenuDialog(const QtPylosMenuDialog&) = delete;
  QtPylosMenuDialog& operator=(const QtPylosMenuDialog&) = delete;
  ~QtPylosMenuDialog() noexcept;

protected:
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent * e);

private:
  Ui::QtPylosMenuDialog *ui;
  int m_selected;
  bool m_type_basic;
  bool m_theme_bw;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnStart();
  void OnAbout();
  void OnInstructions();
};

} //~namespace pylos
} //~namespace ribi

#endif // QTPYLOSMENUDIALOG
