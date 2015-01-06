//---------------------------------------------------------------------------
/*
GameZero, a bare bone game
Copyright (C) 2015-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameZero.htm
//---------------------------------------------------------------------------
#ifndef QTGAMEZEROMAINDIALOG_H
#define QTGAMEZEROMAINDIALOG_H

#include <set>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QPixmap;
struct QTimer;

namespace Ui {
  class QtZeroMainDialog;
}


namespace ribi {

class QtZeroMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:

  explicit QtZeroMainDialog(QWidget *parent = 0);
  QtZeroMainDialog(const QtZeroMainDialog&) = delete;
  QtZeroMainDialog& operator=(const QtZeroMainDialog&) = delete;
  ~QtZeroMainDialog() noexcept;

private:
  Ui::QtZeroMainDialog *ui;

  std::set<int> m_keys_pressed;
  const std::unique_ptr<QPixmap> m_player_sprite;
  int m_player_x;
  int m_player_y;
  const std::unique_ptr<QTimer> m_timer_press_key;
  void keyPressEvent(QKeyEvent * e);
  void keyReleaseEvent(QKeyEvent * e);
  void paintEvent(QPaintEvent * event);
  void resizeEvent(QResizeEvent*);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnTimerPressKey();

};

} //~namespace ribi

#endif // QTGAMEZEROMAINDIALOG_H
