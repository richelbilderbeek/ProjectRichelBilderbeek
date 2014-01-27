//---------------------------------------------------------------------------
/*
Maziak, a simple maze game
Copyright (C) 2007-2014 Richel Bilderbeek

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
#include <set>
#include <list>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"
#include "maziakmazesquare.h"
#include "maziaksprite.h"
#include "maziakfwd.h"
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

  explicit QtMaziakMainDialog(QWidget *parent = 0, const int maze_size = 0);
  QtMaziakMainDialog(const QtMaziakMainDialog&) = delete;
  QtMaziakMainDialog& operator=(const QtMaziakMainDialog&) = delete;
  ~QtMaziakMainDialog() noexcept;

private:
  Ui::QtMaziakMainDialog *ui;

  typedef unsigned int WORD;

  PlayerDirection m_direction;
  boost::shared_ptr<const DistancesMaze> m_distances;
  bool m_do_show_solution;
  int m_fighting_frame;
  bool m_has_sword;
  std::set<WORD> m_keys;
  const boost::shared_ptr<Maze> m_maze;
  PlayerMove m_move_now;
  boost::shared_ptr<const SolutionMaze> m_solution;
  const boost::shared_ptr<const Sprites> m_sprites;
  const boost::shared_ptr<QTimer> m_timer_enemy;
  const boost::shared_ptr<QTimer> m_timer_press_key;
  const boost::shared_ptr<QTimer> m_timer_show_solution;
  const int m_view_height;
  const int m_view_width;
  int m_x;
  int m_y;
  boost::shared_ptr<MainDialog> m_dialog;

  const boost::shared_ptr<const SolutionMaze> CreateNewSolution() noexcept;
  void GameOver();
  void GameWon();
  static Sprite GetSpriteFloor(
    const boost::shared_ptr<const Maze> maze,
    const int x,
    const int y,
    const bool show_solution,
    const boost::shared_ptr<const SolutionMaze> solution
  ) noexcept;
  static Sprite GetSpriteAboveFloor(
    const int x,
    const int y,
    const boost::shared_ptr<const Maze> m_maze
  ) noexcept;
  static Sprite GetSpritePlayer(
    const PlayerDirection direction,
    const PlayerMove moveNow,
    const bool m_has_sword,
    const int m_fighting_frame
  ) noexcept;

  //Events
  void resizeEvent(QResizeEvent*);
  void keyPressEvent(QKeyEvent * e);
  void keyReleaseEvent(QKeyEvent * e);
  void paintEvent(QPaintEvent * event);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void onTimerPressKey();
  void onTimerEnemy();
  void onTimerShowSolution();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKMAINDIALOG_H
