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
#ifndef QTPYLOSMAINDIALOG_H
#define QTPYLOSMAINDIALOG_H

#include <memory>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"

//#include <boost/shared_ptr.hpp>
#include "qtpylosgamewidget.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPylosMainDialog;
}

namespace ribi {
namespace pylos {

class QtPylosMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  using QtGameWidget = std::shared_ptr<ribi::pylos::QtPylosGameWidget>;

  explicit QtPylosMainDialog(
    const QtGameWidget pylos_widget,
    QWidget *parent = 0);
  QtPylosMainDialog(const QtPylosMainDialog&) = delete;
  QtPylosMainDialog& operator=(const QtPylosMainDialog&) = delete;
  ~QtPylosMainDialog() noexcept;

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private:
  Ui::QtPylosMainDialog *ui;
  const QtGameWidget m_pylos_widget;


private slots:
  void OnWinner();
};

} //~namespace pylos
} //~namespace ribi

#endif // QTPYLOSMAINDIALOG_H
