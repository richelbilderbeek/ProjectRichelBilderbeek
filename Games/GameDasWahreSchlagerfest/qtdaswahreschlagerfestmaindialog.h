//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm
//---------------------------------------------------------------------------
#ifndef QTDASWAHRESCHLAGERFESTMAINDIALOG_H
#define QTDASWAHRESCHLAGERFESTMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui { class QtDwsMainDialog; }

namespace ribi {
namespace dws {

class QtMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtMainDialog(QWidget *parent = 0) noexcept;
  QtMainDialog(const QtMainDialog&) = delete;
  QtMainDialog& operator=(const QtMainDialog&) = delete;
  ~QtMainDialog() noexcept;

private:
  Ui::QtDwsMainDialog *ui;
  void closeEvent(QCloseEvent *);
  void keyPressEvent(QKeyEvent *event);
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace dws
} //~namespace ribi

#endif // QTDASWAHRESCHLAGERFESTMAINDIALOG_H
