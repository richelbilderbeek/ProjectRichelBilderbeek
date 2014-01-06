//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
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
//From http://www.richelbilderbeek.nl/GamePylos.htm
//---------------------------------------------------------------------------
#ifndef QTPYLOSMAINDIALOG
#define QTPYLOSMAINDIALOG

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"

#include "qtpylosgamewidget.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPylosMainDialog;
}

namespace ribi {

class QtPylosMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPylosMainDialog(
  QtPylosGameWidget * const pylos_widget = 0,
    QWidget *parent = 0);
  QtPylosMainDialog(const QtPylosMainDialog&) = delete;
  QtPylosMainDialog& operator=(const QtPylosMainDialog&) = delete;
  ~QtPylosMainDialog() noexcept;

  ///Obtain this class its version
  static const std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

private:
  Ui::QtPylosMainDialog *ui;
  QtPylosGameWidget * const m_pylos_widget;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnWinner();
};

} //~namespace ribi

#endif // QTPYLOSMAINDIALOG
