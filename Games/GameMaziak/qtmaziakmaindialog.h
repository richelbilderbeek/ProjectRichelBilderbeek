//---------------------------------------------------------------------------
/*
Maziak, a simple maze game
Copyright (C) 2007-2012 Richel Bilderbeek

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
#include <QDialog>
#pragma GCC diagnostic pop

struct QPixmap;
struct QTimer;

namespace Ui {
  class QtMaziakMainDialog;
}

namespace ribi {

class QtMaziakMainDialog : public QDialog
{
  Q_OBJECT


public:
  enum PlayerDirection { pdLeft, pdRight, pdUp, pdDown };
  enum PlayerMove { none, left1, left2, right1, right2, up1, up2, down1, down2 };
  enum MazeSquare { msEmpty, msWall, msEnemy1, msEnemy2, msPrisoner1, msPrisoner2, msSword, msExit };

  explicit QtMaziakMainDialog(QWidget *parent = 0, const int maze_size = 0);
  QtMaziakMainDialog(const QtMaziakMainDialog&) = delete;
  QtMaziakMainDialog& operator=(const QtMaziakMainDialog&) = delete;
  ~QtMaziakMainDialog() noexcept;

private:
  Ui::QtMaziakMainDialog *ui;
  //Floor sprites
  const boost::shared_ptr<const QPixmap> m_pixmap_empty;
  const boost::shared_ptr<const QPixmap> m_pixmap_wall;
  const boost::shared_ptr<const QPixmap> m_pixmap_path;
  const boost::shared_ptr<const QPixmap> m_pixmap_transparent;
  //Player sprites
  const boost::shared_ptr<const QPixmap> m_pixmap_player_look_down;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_look_down_sword;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_look_left;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_look_left_sword;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_look_right;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_look_right_sword;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_look_up;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_look_up_sword;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_left1;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_left2;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_left_sword1;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_left_sword2;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_right1;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_right2;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_right_sword1;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_right_sword2;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_down1;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_down2;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_down_sword1;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_down_sword2;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_up1;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_up2;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_up_sword1;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_walk_up_sword2;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_won1;
  const boost::shared_ptr<const QPixmap> m_pixmap_player_won2;
  //Fighting sprites
  const boost::shared_ptr<const QPixmap> m_pixmap_fight_sword1;
  const boost::shared_ptr<const QPixmap> m_pixmap_fight_no_sword1;
  const boost::shared_ptr<const QPixmap> m_pixmap_fight2;
  const boost::shared_ptr<const QPixmap> m_pixmap_fight3;
  const boost::shared_ptr<const QPixmap> m_pixmap_fight4;
  const boost::shared_ptr<const QPixmap> m_pixmap_fight_won1;
  const boost::shared_ptr<const QPixmap> m_pixmap_fight_won2;
  const boost::shared_ptr<const QPixmap> m_pixmap_fight_lost1;
  const boost::shared_ptr<const QPixmap> m_pixmap_fight_lost2;
  //Non-player sprites
  const boost::shared_ptr<const QPixmap> m_pixmap_enemy1;
  const boost::shared_ptr<const QPixmap> m_pixmap_enemy2;
  const boost::shared_ptr<const QPixmap> m_pixmap_prisoner1;
  const boost::shared_ptr<const QPixmap> m_pixmap_prisoner2;
  const boost::shared_ptr<const QPixmap> m_pixmap_sword;
  const boost::shared_ptr<const QPixmap> m_pixmap_exit;
  //Timers
  const boost::shared_ptr<QTimer> m_timer_press_key;
  const boost::shared_ptr<QTimer> m_timer_enemy;
  const boost::shared_ptr<QTimer> m_timer_show_solution;

  int mX;
  int mY;
  const int mViewWidth;
  const int mViewHeight;
  bool mHasSword;
  int mFighting;
  bool mCheat;
  bool mShowSolution;
  PlayerDirection mDirection;
  PlayerMove mMoveNow;
  typedef unsigned int WORD;
  std::set<WORD> mKeys;
  std::vector<std::vector<int> > mSolution;
  std::vector<std::vector<int> > mIntMaze;
  std::vector<std::vector<MazeSquare> > mMaze;
  std::vector<std::vector<int> > mDistances;

  void createMaze(const int sz);
  void gameOver();
  void gameWon();
  const QPixmap& GetPixmapFloor(const int x, const int) const;
  const QPixmap& GetPixmapAboveFloor(const int x, const int) const;
  const QPixmap& GetPixmapPlayer(
      const PlayerDirection direction,
      const PlayerMove moveNow) const;

  //Events
  void resizeEvent(QResizeEvent*);
  void keyPressEvent(QKeyEvent * e);
  void keyReleaseEvent(QKeyEvent * e);
  void paintEvent(QPaintEvent * event);

private slots:
  void onTimerPressKey();
  void onTimerEnemy();
  void onTimerShowSolution();

};

template <class Source, class Target>
    const std::vector<std::vector<Target> > ConvertMatrix(
        const std::vector<std::vector<Source> >& v)
{
  const int maxy = static_cast<int>(v.size());
  assert(maxy>0);
  const int maxx = static_cast<int>(v[0].size());
  std::vector<std::vector<Target> > t(maxy,std::vector<Target>(maxx));
  for (int y=0; y!=maxy; ++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      t[y][x] = static_cast<Target>(v[y][x]);
    }
  }
  return t;
}

const std::vector<std::pair<int,int> > GetShuffledDeadEnds(
    const std::vector<std::vector<int> >& intMaze);

const std::vector<std::pair<int,int> > GetShuffledNonDeadEnds(
    const std::vector<std::vector<int> >& intMaze);

bool CanMoveTo(
    const std::vector<std::vector<QtMaziakMainDialog::MazeSquare> >& maze,
    const int x, const int y,
    const bool hasSword,
    const bool showSolution);


//Creates a maze
// 0 : path
// 1 : wall
//From http://www.richelbilderbeek.nl/CppCreateMaze.htm
std::vector<std::vector<int> > CreateMaze(const int sz);

//From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
std::vector<std::pair<int,int> > GetDeadEnds(const std::vector<std::vector<int> >& maze);

//From http://www.richelbilderbeek.nl/GetDistancesPath.htm
std::vector<std::vector<int> > GetDistancesPath(
  const std::vector<std::vector<int> >& distances,
  const int playerX,
  const int playerY);

//From http://www.richelbilderbeek.nl/CppGetMazeDistances.htm
std::vector<std::vector<int> > GetMazeDistances(
    const std::vector<std::vector<int> >& maze,
    const int x,
    const int y);

const std::vector<std::pair<int,int> > GetShuffledDeadEnds(
    const std::vector<std::vector<int> >& intMaze);


bool IsSquare(const std::vector<std::vector<QtMaziakMainDialog::MazeSquare> >& v);
bool IsSquare(const std::vector<std::vector<int> >& v);

} //~namespace ribi

#endif // QTMAZIAKMAINDIALOG_H
