//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#ifndef QTBEERWANTERMAINDIALOG_H
#define QTBEERWANTERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtBeerWanterMainDialog;
}

namespace ribi {

struct QtBeerWanterWidget;

class QtBeerWanterMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtBeerWanterMainDialog(QWidget *parent = 0);
  QtBeerWanterMainDialog(const QtBeerWanterMainDialog&) = delete;
  QtBeerWanterMainDialog& operator=(const QtBeerWanterMainDialog&) = delete;
  ~QtBeerWanterMainDialog() noexcept;
private:
  Ui::QtBeerWanterMainDialog *ui;
  boost::shared_ptr<QtBeerWanterWidget> m_widget;

private slots:
  void ChangeTitle(const std::string& title) noexcept;
  void OnShake(const int x, const int y) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTBEERWANTERMAINDIALOG_H

