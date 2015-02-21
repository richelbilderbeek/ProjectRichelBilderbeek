//---------------------------------------------------------------------------
/*
Maziak, a simple maze game
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameMaziak.htm
//---------------------------------------------------------------------------
#ifndef QTMAZIAKMAINDIALOG_H
#define QTMAZIAKMAINDIALOG_H

#include <cassert>
#include <map>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "maziakmazesquare.h"
#include "maziaksprite.h"
#include "maziakfwd.h"
#include "maziakkey.h"
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"
#pragma GCC diagnostic pop

struct QPixmap;
struct QTimer;

namespace Ui {
  class QtMaziakMainDialog;
}


namespace ribi {
namespace maziak {


class QtMaziakMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:

  explicit QtMaziakMainDialog(const int maze_size, QWidget *parent = 0);
  QtMaziakMainDialog(const QtMaziakMainDialog&) = delete;
  QtMaziakMainDialog& operator=(const QtMaziakMainDialog&) = delete;
  ~QtMaziakMainDialog() noexcept;

private:
  Ui::QtMaziakMainDialog *ui;

  typedef unsigned int WORD;

  boost::shared_ptr<MainDialog> m_dialog;
  std::map<WORD,Key> m_keys;

  const boost::shared_ptr<const Sprites> m_sprites;
  const boost::shared_ptr<QTimer> m_timer_enemy;
  const boost::shared_ptr<QTimer> m_timer_press_key;
  const boost::shared_ptr<QTimer> m_timer_show_solution;
  const int m_view_height;
  const int m_view_width;

  static const std::map<WORD,Key> CreateDefaultKeys() noexcept;
  void OnGameOver();
  void OnGameWon();
  void OnTimerStartShowingSolution();

  void resizeEvent(QResizeEvent*);
  void keyPressEvent(QKeyEvent * e);
  void keyReleaseEvent(QKeyEvent * e);
  void paintEvent(QPaintEvent * event);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnTimerPressKey();
  void OnTimerEnemy();
  void OnTimerStopShowingSolution();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKMAINDIALOG_H
