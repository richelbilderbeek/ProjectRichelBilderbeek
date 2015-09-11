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
#ifndef QTMAZIAKDISPLAY_H
#define QTMAZIAKDISPLAY_H

#include <cassert>
#include <map>
#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "maziakmazesquare.h"
#include "maziaksprite.h"
#include "maziakdisplay.h"
#include "maziakfwd.h"
#include "maziakkey.h"
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"
#include "stopwatch.h"
#pragma GCC diagnostic pop

struct QPixmap;
struct QTimer;

namespace ribi {
namespace maziak {


class QtDisplay : public QWidget, public Display
{
  Q_OBJECT

public:

  explicit QtDisplay(QWidget *parent = 0);
  QtDisplay(const QtDisplay&) = delete;
  QtDisplay& operator=(const QtDisplay&) = delete;
  ~QtDisplay() {}

  void DoDisplay(const MainDialog& main_dialog) override;

  int GetViewHeight() const noexcept override { return 9; }
  int GetViewWidth() const noexcept override { return 9; }

  bool MustAnimateEnemiesAndPrisoners() noexcept override;

  std::set<Key> RequestKeys() override;

private:
  typedef unsigned int WORD;

  //Will be painted
  QImage m_image;

  std::set<Key> m_keys;

  const boost::shared_ptr<const Sprites> m_sprites;
  Stopwatch m_timer_animate_enemies_and_prisoners;
  Stopwatch m_timer_show_solution;

  static std::map<WORD,Key> CreateDefaultKeys() noexcept;
  bool GetDoShowSolution() override;

  void OnGameOver();
  void OnGameWon();
  void OnTimerStartShowingSolution();
  void StartShowSolution();

  void resizeEvent(QResizeEvent*);
  void keyPressEvent(QKeyEvent * e);
  void keyReleaseEvent(QKeyEvent * e);
  void paintEvent(QPaintEvent * event);


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKDISPLAY_H
