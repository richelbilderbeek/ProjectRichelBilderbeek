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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmaziakmaindialog.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <iostream>
#include <stdexcept>
#include <vector>

#include <boost/scoped_ptr.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include "maziakhelper.h"
#include "maziakintmaze.h"
#include "qtmaziakgameoverdialog.h"
#include "qtmaziakgamewondialog.h"
#include "ui_qtmaziakmaindialog.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::maziak::QtMaziakMainDialog::QtMaziakMainDialog(QWidget *parent, const int maze_size)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtMaziakMainDialog),
    //Floor
    m_pixmap_empty(new QPixmap(":/images/Empty.png")),
    m_pixmap_wall(new QPixmap(":/images/Wall.png")),
    m_pixmap_path(new QPixmap(":/images/Path.png")),
    m_pixmap_transparent(new QPixmap(":/images/Transparent.png")),
    //Player sprites
    m_pixmap_player_look_down(new QPixmap(":/images/PlayerLookDown.png")),
    m_pixmap_player_look_down_sword(new QPixmap(":/images/PlayerLookDownSword.png")),
    m_pixmap_player_look_left(new QPixmap(":/images/PlayerLookLeft.png")),
    m_pixmap_player_look_left_sword(new QPixmap(":/images/PlayerLookLeftSword.png")),
    m_pixmap_player_look_right(new QPixmap(":/images/PlayerLookRight.png")),
    m_pixmap_player_look_right_sword(new QPixmap(":/images/PlayerLookRightSword.png")),
    m_pixmap_player_look_up(new QPixmap(":/images/PlayerLookUp.png")),
    m_pixmap_player_look_up_sword(new QPixmap(":/images/PlayerLookUpSword.png")),
    m_pixmap_player_walk_left1(new QPixmap(":/images/PlayerWalkLeft1.png")),
    m_pixmap_player_walk_left2(new QPixmap(":/images/PlayerWalkLeft2.png")),
    m_pixmap_player_walk_left_sword1(new QPixmap(":/images/PlayerWalkLeftSword1.png")),
    m_pixmap_player_walk_left_sword2(new QPixmap(":/images/PlayerWalkLeftSword2.png")),
    m_pixmap_player_walk_right1(new QPixmap(":/images/PlayerWalkRight1.png")),
    m_pixmap_player_walk_right2(new QPixmap(":/images/PlayerWalkRight2.png")),
    m_pixmap_player_walk_right_sword1(new QPixmap(":/images/PlayerWalkRightSword1.png")),
    m_pixmap_player_walk_right_sword2(new QPixmap(":/images/PlayerWalkRightSword2.png")),
    m_pixmap_player_walk_down1(new QPixmap(":/images/PlayerWalkDown1.png")),
    m_pixmap_player_walk_down2(new QPixmap(":/images/PlayerWalkDown2.png")),
    m_pixmap_player_walk_down_sword1(new QPixmap(":/images/PlayerWalkDownSword1.png")),
    m_pixmap_player_walk_down_sword2(new QPixmap(":/images/PlayerWalkDownSword2.png")),
    m_pixmap_player_walk_up1(new QPixmap(":/images/PlayerWalkUp1.png")),
    m_pixmap_player_walk_up2(new QPixmap(":/images/PlayerWalkUp2.png")),
    m_pixmap_player_walk_up_sword1(new QPixmap(":/images/PlayerWalkUpSword1.png")),
    m_pixmap_player_walk_up_sword2(new QPixmap(":/images/PlayerWalkUpSword2.png")),
    m_pixmap_player_won1(new QPixmap(":/images/PlayerWon1.png")),
    m_pixmap_player_won2(new QPixmap(":/images/PlayerWon2.png")),
    //Fighting sprites
    m_pixmap_fight_sword1(new QPixmap(":/images/FightSword1.png")),
    m_pixmap_fight_no_sword1(new QPixmap(":/images/FightNoSword1.png")),
    m_pixmap_fight2(new QPixmap(":/images/Fight2.png")),
    m_pixmap_fight3(new QPixmap(":/images/Fight3.png")),
    m_pixmap_fight4(new QPixmap(":/images/Fight4.png")),
    m_pixmap_fight_won1(new QPixmap(":/images/FightWon1.png")),
    m_pixmap_fight_won2(new QPixmap(":/images/FightWon2.png")),
    m_pixmap_fight_lost1(new QPixmap(":/images/FightLost1.png")),
    m_pixmap_fight_lost2(new QPixmap(":/images/FightLost2.png")),
    //Others
    m_pixmap_enemy1(new QPixmap(":/images/Enemy1.png")),
    m_pixmap_enemy2(new QPixmap(":/images/Enemy2.png")),
    m_pixmap_prisoner1(new QPixmap(":/images/Prisoner1.png")),
    m_pixmap_prisoner2(new QPixmap(":/images/Prisoner2.png")),
    m_pixmap_sword(new QPixmap(":/images/Sword.png")),
    m_pixmap_exit(new QPixmap(":/images/Exit.png")),
    m_timer_press_key(new QTimer),
    m_timer_enemy(new QTimer),
    m_timer_show_solution(new QTimer),
    mX(-1),
    mY(-1),
    mViewWidth(9),
    mViewHeight(9),
    mHasSword(true),
    mFighting(0),
    mCheat(false),
    mShowSolution(false),
    mDirection(PlayerDirection::pdDown),
    mMoveNow(PlayerMove::none),
    mKeys{},
    mSolution{},
    mIntMaze{new IntMaze(maze_size)},
    mMaze{},
    mDistances{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  assert(m_pixmap_empty);
  assert(!m_pixmap_empty->isNull());
  assert(m_pixmap_wall);
  assert(!m_pixmap_wall->isNull());
  assert(m_pixmap_path);
  assert(!m_pixmap_path->isNull());
  assert(!m_pixmap_player_look_down->isNull());
  assert(!m_pixmap_player_look_down_sword->isNull());
  assert(!m_pixmap_player_look_left->isNull());
  assert(!m_pixmap_player_look_left_sword->isNull());
  assert(!m_pixmap_player_look_right->isNull());
  assert(!m_pixmap_player_look_right_sword->isNull());
  assert(!m_pixmap_player_look_up->isNull());
  assert(!m_pixmap_player_look_up_sword->isNull());
  assert(!m_pixmap_player_walk_left1->isNull());
  assert(!m_pixmap_player_walk_left2->isNull());
  assert(!m_pixmap_player_walk_left_sword1->isNull());
  assert(!m_pixmap_player_walk_left_sword2->isNull());
  assert(!m_pixmap_player_walk_right1->isNull());
  assert(!m_pixmap_player_walk_right2->isNull());
  assert(!m_pixmap_player_walk_right_sword1->isNull());
  assert(!m_pixmap_player_walk_right_sword2->isNull());
  assert(!m_pixmap_player_walk_down1->isNull());
  assert(!m_pixmap_player_walk_down2->isNull());
  assert(!m_pixmap_player_walk_down_sword1->isNull());
  assert(!m_pixmap_player_walk_down_sword2->isNull());
  assert(!m_pixmap_player_walk_up1->isNull());
  assert(!m_pixmap_player_walk_up2->isNull());
  assert(!m_pixmap_player_walk_up_sword1->isNull());
  assert(!m_pixmap_player_walk_up_sword2->isNull());
  assert(!m_pixmap_player_won1->isNull());
  assert(!m_pixmap_player_won2->isNull());

  assert(maze_size && "Maze size must be 7 + (4 * n) for n e [0,->>");

  m_timer_press_key->setInterval(100);
  m_timer_enemy->setInterval(1000);
  m_timer_show_solution->setInterval(5000);

  QObject::connect(m_timer_press_key.get(),SIGNAL(timeout()),
    this,SLOT(onTimerPressKey()));
  QObject::connect(m_timer_enemy.get(),SIGNAL(timeout()),
    this,SLOT(onTimerEnemy()));
  QObject::connect(m_timer_show_solution.get(),SIGNAL(timeout()),
    this,SLOT(onTimerShowSolution()));

  CreateMaze(maze_size);
  assert(IsSquare(mMaze));
  assert(IsSquare(mIntMaze));
  assert(mSolution.empty() || IsSquare(mSolution));
  assert(IsSquare(mDistances));

  m_timer_press_key->start();
  m_timer_enemy->start();

  //Put the dialog in the screen center at 75% of fullscreen size
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 75 / 100,screen.height() * 75 / 100);
  this->move( screen.center() - this->rect().center() );
}

ribi::maziak::QtMaziakMainDialog::~QtMaziakMainDialog() noexcept
{
  delete ui;
}

void ribi::maziak::QtMaziakMainDialog::resizeEvent(QResizeEvent*)
{
  this->repaint();
}

void ribi::maziak::QtMaziakMainDialog::keyPressEvent(QKeyEvent* e)
{
  if (mFighting > 0) repaint();

  mKeys.insert(e->key());

  switch (e->key())
  {
    case Qt::Key_Left : mKeys.erase(Qt::Key_Right); break;
    case Qt::Key_Right: mKeys.erase(Qt::Key_Left); break;
    case Qt::Key_Up   : mKeys.erase(Qt::Key_Down); break;
    case Qt::Key_Down : mKeys.erase(Qt::Key_Up); break;
    case Qt::Key_F1   : gameOver(); close(); break;
    case Qt::Key_F2   : gameWon(); close(); break;
    case Qt::Key_Escape: close(); break;
  }
}

void ribi::maziak::QtMaziakMainDialog::keyReleaseEvent(QKeyEvent * e)
{
  mKeys.erase(e->key());
}

void ribi::maziak::QtMaziakMainDialog::onTimerPressKey()
{
  if (mFighting > 0) return;
  if (mKeys.empty()) { mMoveNow = PlayerMove::none; }

  for(WORD key: mKeys)
  {
    //Check the keys pressed
    switch (key)
    {
      case Qt::Key_Left:
        mDirection = PlayerDirection::pdLeft;
        if (!CanMoveTo(mMaze,mX-1,mY,mHasSword,mShowSolution))
        {
          mMoveNow = PlayerMove::none;
          continue;
        }
        mMoveNow = (mMoveNow == PlayerMove::left1 ? PlayerMove::left2 : PlayerMove::left1);
        --mX;
        break;
      case Qt::Key_Right:
        mDirection = PlayerDirection::pdRight;
        if (!CanMoveTo(mMaze,mX+1,mY,mHasSword,mShowSolution))
        {
          mMoveNow = PlayerMove::none;
          continue;
        }
        mMoveNow = (mMoveNow == PlayerMove::right1 ? PlayerMove::right2 : PlayerMove::right1);
        ++mX;
        break;
      case Qt::Key_Up:
        mDirection = PlayerDirection::pdUp;
        if (!CanMoveTo(mMaze,mX,mY-1,mHasSword,mShowSolution))
        {
          mMoveNow = PlayerMove::none;
          continue;
        }
        mMoveNow = (mMoveNow == PlayerMove::up1 ? PlayerMove::up2 : PlayerMove::up1);
        --mY;
        break;
      case Qt::Key_Down:
        mDirection = PlayerDirection::pdDown;
        if (!CanMoveTo(mMaze,mX,mY+1,mHasSword,mShowSolution))
        {
          mMoveNow = PlayerMove::none;
          continue;
        }
        mMoveNow = (mMoveNow == PlayerMove::down1 ? PlayerMove::down2 : PlayerMove::down1);
        ++mY;
        break;
      default:
        mMoveNow = PlayerMove::none;
        continue;
    }
    //Draw the screen
    repaint();
  }
}

void ribi::maziak::QtMaziakMainDialog::onTimerEnemy()
{
  //Move them
  const int minx = std::max(0,mX - mViewWidth );
  const int miny = std::max(0,mY - mViewHeight);
  const int maxy = std::min(static_cast<int>(mMaze.size()),mY + mViewHeight);
  const int maxx = std::min(static_cast<int>(mMaze[mY].size()),mX + mViewWidth);
  assert(miny >= 0);
  assert(miny <= static_cast<int>(mMaze.size()));
  assert(maxy >= 0);
  assert(maxy <= static_cast<int>(mMaze.size()));
  assert(minx >= 0);
  assert(minx <= static_cast<int>(mMaze[mY].size()));
  assert(maxx >= 0);
  assert(maxx <= static_cast<int>(mMaze[mY].size()));
  assert(miny <= maxy);
  assert(minx <= maxx);
  for (int y=miny; y!=maxy; ++y)
  {
    assert( y >= 0);
    assert( y < static_cast<int>(mMaze.size()));
    for (int x=minx; x!=maxx; ++x)
    {
      //msEnemy1 changes to msEnemy2
      //Only msEnemy2 moves, after moving turning to msEnemy1
      assert( x >= 0);
      assert( x < static_cast<int>(mMaze[y].size()));
      const MazeSquare s = mMaze[y][x];

      if (s == MazeSquare::msEnemy1)
      {
        //msEnemy1 changes to msEnemy2
        mMaze[y][x] = MazeSquare::msEnemy2;
        continue;
      }
      else if (s == MazeSquare::msEnemy2)
      {
        //msEnemy 2 tries to walk
        std::vector<std::pair<int,int> > moves;
        if (y > mY && y >        1 && mMaze[y-1][x  ] == MazeSquare::msEmpty) moves.push_back(std::make_pair(x,y-1));
        if (x < mX && x < maxx - 1 && mMaze[y  ][x+1] == MazeSquare::msEmpty) moves.push_back(std::make_pair(x+1,y));
        if (y < mY && y < maxy - 1 && mMaze[y+1][x  ] == MazeSquare::msEmpty) moves.push_back(std::make_pair(x,y+1));
        if (x > mX && x >        1 && mMaze[y  ][x-1] == MazeSquare::msEmpty) moves.push_back(std::make_pair(x-1,y));
        const int nMoves = static_cast<int>(moves.size());
        if (nMoves == 1)
        {
          mMaze[y][x] = MazeSquare::msEnemy1;
          std::swap(mMaze[y][x],mMaze[moves[0].second][moves[0].first]);
        }
        else if (nMoves > 1)
        {
          assert(nMoves == 2);
          mMaze[y][x] = MazeSquare::msEnemy1;
          const int moveIndex = (std::rand() >> 4) % nMoves;
          std::swap(mMaze[y][x],mMaze[moves[moveIndex].second][moves[moveIndex].first]);
        }
      }
      else if (s==MazeSquare::msPrisoner1)
      {
        //Animate prisoners
        mMaze[y][x] = MazeSquare::msPrisoner2;
      }
      else if (s==MazeSquare::msPrisoner2)
      {
        //Animate prisoners
        mMaze[y][x] = MazeSquare::msPrisoner1;
      }
    }
  }
  repaint();
}

void ribi::maziak::QtMaziakMainDialog::onTimerShowSolution()
{
  mShowSolution = false;
  m_timer_show_solution->stop();
}

void ribi::maziak::QtMaziakMainDialog::paintEvent(QPaintEvent *)
{
  const int block_width  = 1 + ((ui->widget->width()  - 4) / mViewWidth);
  const int block_height = 1 + ((ui->widget->height() - 4) / mViewHeight);

  if (mFighting > 0)
  {
    ++mFighting;
    if (mFighting == 13)
    {
      if (!mHasSword)
      {
        gameOver();
        this->close();
      }
      mFighting = 0;
      mHasSword = false;
    }
  }

  //Player-environment interactions
  QPainter painter(this);
  assert(painter.isActive());

  //Clean painter
  {
    const QPixmap temp(":/images/Empty.png");
    assert(!temp.isNull());
    painter.drawPixmap(ui->widget->rect(),temp);
  }


  assert(mY >= 0);
  assert(mY < static_cast<int>(mMaze.size()));
  assert(mX >= 0);
  assert(mX < static_cast<int>(mMaze[mY].size()));
  switch (mMaze[mY][mX])
  {

    case MazeSquare::msEmpty:
      break;
    case MazeSquare::msWall:
      assert(!"Should not get here");
      throw std::logic_error("Player cannot be in wall");
    case MazeSquare::msEnemy1: case MazeSquare::msEnemy2:
      mFighting = 1;
      mMaze[mY][mX] = MazeSquare::msEmpty;
      break;
    case MazeSquare::msPrisoner1: case MazeSquare::msPrisoner2:
      mMaze[mY][mX] = MazeSquare::msEmpty;
      mSolution = GetDistancesPath(mDistances,mX,mY);
      assert(IsSquare(mSolution));
      mShowSolution = true;
      m_timer_show_solution->start();
      break;
    case MazeSquare::msSword:
      mMaze[mY][mX] = MazeSquare::msEmpty;
      mHasSword = true;
      break;
    case MazeSquare::msExit:
    {
      gameWon();
      this->close();
      break;
    }
    default:
      assert(!"Should not get here");
      break;
  }

  //Draw maze
  {
    for (int y=0; y!=mViewHeight; ++y)
    {
      for (int x=0; x!=mViewWidth; ++x)
      {
        //xVector and yVector are the indices in the non-visual maze 2D std::vector
        const int xVector = mX - (mViewWidth  / 2) + x;
        const int yVector = mY - (mViewHeight / 2) + y;
        //Draw the floor tile
        const QPixmap& pixmap_floor = GetPixmapFloor(xVector,yVector);
        assert(!pixmap_floor.isNull());
        painter.drawPixmap(
          (x * block_width )+0,
          (y * block_height)+0,
          block_width,
          block_height,
          pixmap_floor);
        //Draw what's moving or standing on the floor
        const QPixmap& pixmap_above_floor = GetPixmapAboveFloor(xVector,yVector);
        assert(!pixmap_above_floor.isNull());
        painter.drawPixmap(
          (x * block_width )+0,
          (y * block_height)+0,
          block_width,
          block_height,
          pixmap_above_floor);
      }
    }
  }

  //Draw player
  {
    const QPixmap& player = GetPixmapPlayer(mDirection,mMoveNow);
    assert(!player.isNull());
    painter.drawPixmap(
      ((mViewWidth  / 2) * block_width )+0,
      ((mViewHeight / 2) * block_height)+0,
       block_width,
       block_height,
       player);
  }
}

void ribi::maziak::QtMaziakMainDialog::gameOver()
{
  m_timer_press_key->stop();
  m_timer_enemy->stop();
  m_timer_show_solution->stop();
  this->hide();
  boost::scoped_ptr<QtMaziakGameOverDialog> f(new QtMaziakGameOverDialog(0));
  f->exec();
}

void ribi::maziak::QtMaziakMainDialog::gameWon()
{
  m_timer_press_key->stop();
  m_timer_enemy->stop();
  m_timer_show_solution->stop();
  this->hide();
  boost::scoped_ptr<QtMaziakGameWonDialog> f(new QtMaziakGameWonDialog);
  this->hide();
  f->exec();
}


const QPixmap& ribi::maziak::QtMaziakMainDialog::GetPixmapFloor(const int x, const int y) const
{
  const int sz = static_cast<int>(mMaze.size());
  assert(sz > 0);
  assert(sz == static_cast<int>(mMaze[0].size()));
  assert(mShowSolution == false ||  mSolution.size() == mMaze.size());

  //QPixmap pixmap;
  if ( x < 0
    || y < 0
    || x >= sz
    || y >= sz)
  {
    return *(m_pixmap_wall.get());
  }
  else if (mShowSolution
    && mSolution[y][x] == 1
    && ( mMaze[y][x] == MazeSquare::msEmpty
      || mMaze[y][x] == MazeSquare::msEnemy1
      || mMaze[y][x] == MazeSquare::msEnemy2)
    )
  {
    return *(m_pixmap_path.get());
  }
  return *(m_pixmap_empty.get());
}

const QPixmap& ribi::maziak::QtMaziakMainDialog::GetPixmapAboveFloor(const int x, const int y) const
{
  const int sz = static_cast<int>(mMaze.size());
  if ( x < 0
    || y < 0
    || x >= sz
    || y >= sz)
  {
    return *m_pixmap_wall.get();
  }
  //What else here?
  switch(mMaze[y][x])
  {
    case MazeSquare::msEmpty     : return *m_pixmap_transparent.get();
    case MazeSquare::msWall      : return *m_pixmap_wall.get();
    case MazeSquare::msEnemy1    : return *m_pixmap_enemy1.get();
    case MazeSquare::msEnemy2    : return *m_pixmap_enemy2.get();
    case MazeSquare::msPrisoner1 : return *m_pixmap_prisoner1.get();
    case MazeSquare::msPrisoner2 : return *m_pixmap_prisoner2.get();
    case MazeSquare::msSword     : return *m_pixmap_sword.get();
    case MazeSquare::msExit      : return *m_pixmap_exit.get();
    default:
      assert(!"Should not get here");
      throw std::logic_error("Unexpected MazeSquare at mMaze");
  }
}

const QPixmap& ribi::maziak::QtMaziakMainDialog::GetPixmapPlayer(
  const PlayerDirection direction,
  const PlayerMove moveNow) const
{
  switch (mFighting)
  {
    case  0: break;
    case  1: return (mHasSword ? *m_pixmap_fight_sword1.get() : *m_pixmap_fight_no_sword1.get());
    case  2: return *m_pixmap_fight2.get();
    case  3: return *m_pixmap_fight3.get();
    case  4: return *m_pixmap_fight4.get();
    case  5: return (mHasSword ? *m_pixmap_fight_sword1.get() : *m_pixmap_fight_no_sword1.get());
    case  6: return *m_pixmap_fight2.get();
    case  7: return *m_pixmap_fight3.get();
    case  8: return *m_pixmap_fight4.get();
    case  9: return (mHasSword ? *m_pixmap_fight_won1.get() : *m_pixmap_fight_lost1.get());
    case 10: return (mHasSword ? *m_pixmap_fight_won2.get() : *m_pixmap_fight_lost2.get());
    case 11: return (mHasSword ? *m_pixmap_fight_won1.get() : *m_pixmap_fight_lost1.get());
    case 12: return (mHasSword ? *m_pixmap_fight_won2.get() : *m_pixmap_fight_lost2.get());
  }

  switch (direction)
  {
  case PlayerDirection::pdUp:
    {
      switch (moveNow)
      {
      case PlayerMove::none: return (mHasSword ? *m_pixmap_player_look_up_sword.get() : *m_pixmap_player_look_up.get());
      case PlayerMove::up1:  return (mHasSword ? *m_pixmap_player_walk_up_sword1.get() : *m_pixmap_player_walk_up1.get());
      case PlayerMove::up2:  return (mHasSword ? *m_pixmap_player_walk_up_sword2.get() : *m_pixmap_player_walk_up2.get());
      default:
        assert("!Should not get here");
        throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == up");
      }
    }
    //break; Unreachable
  case PlayerDirection::pdRight:
    {
      switch (moveNow)
      {
      case PlayerMove::none:   return (mHasSword ? *m_pixmap_player_look_right_sword.get() : *m_pixmap_player_look_right.get());
      case PlayerMove::right1: return (mHasSword ? *m_pixmap_player_walk_right_sword1.get() : *m_pixmap_player_walk_right1.get());
      case PlayerMove::right2: return (mHasSword ? *m_pixmap_player_walk_right_sword2.get() : *m_pixmap_player_walk_right2.get());
      default:
        assert("!Should not get here");
        throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == right");
      }
    }
    //break; Unreachable
  case PlayerDirection::pdDown:
    {
      switch (moveNow)
      {
      case PlayerMove::none:  return (mHasSword ? *m_pixmap_player_look_down_sword.get() : *m_pixmap_player_look_down.get());
      case PlayerMove::down1: return (mHasSword ? *m_pixmap_player_walk_down_sword1.get() : *m_pixmap_player_walk_down1.get());
      case PlayerMove::down2: return (mHasSword ? *m_pixmap_player_walk_down_sword2.get() : *m_pixmap_player_walk_down2.get());
      default:
        assert("!Should not get here");
        throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == down");
      }
    }
    //break; Unreachable
  case PlayerDirection::pdLeft:
    {
      switch (moveNow)
      {
      case PlayerMove::none:  return (mHasSword ? *m_pixmap_player_look_left_sword.get() : *m_pixmap_player_look_left.get());
      case PlayerMove::left1: return (mHasSword ? *m_pixmap_player_walk_left_sword1.get() : *m_pixmap_player_walk_left1.get());
      case PlayerMove::left2: return (mHasSword ? *m_pixmap_player_walk_left_sword2.get() : *m_pixmap_player_walk_left2.get());
      default:
        assert("!Should not get here");
        throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == left");
      }
    }
    //break; Unreachable
  default:
    assert("!Should not get here");
    throw std::logic_error("Unsupported PlayerDirection");
  }
  //Unreachable
}

void ribi::maziak::QtMaziakMainDialog::CreateMaze(const int sz)
{
  //mIntMaze = ribi::maziak::CreatIntMaze(sz);
  mMaze = ConvertMatrix<int,MazeSquare>(mIntMaze->Get());

  {
    std::vector<std::pair<int,int> > deadEnds = GetShuffledDeadEnds(mIntMaze);
    const int nDeadEnds = deadEnds.size();
    assert(nDeadEnds >= 2);
    const int nSwords    = (nDeadEnds - 2) / 3;
    const int nPrisoners = (nDeadEnds - 2) / 10;
    const int nEnemies   = (nDeadEnds - 2) / 4;

    //Set a minimum distance for the player to travel
    while (1)
    {
      const double x1 = static_cast<double>(deadEnds[0].first );
      const double y1 = static_cast<double>(deadEnds[0].second);
      const double x2 = static_cast<double>(deadEnds[1].first );
      const double y2 = static_cast<double>(deadEnds[1].second);
      const double a = x1 - x2;
      const double b = y1 - y2;
      const double minDist = 0.75 * static_cast<double>(sz);
      if (std::sqrt( (a * a) + (b * b) ) > minDist)
      {
        break;
      }
      else
      {
        std::swap(deadEnds[0],deadEnds[std::rand() % nDeadEnds]);
        std::swap(deadEnds[1],deadEnds[std::rand() % nDeadEnds]);
      }
    }

    mX = deadEnds[0].first;
    mY = deadEnds[0].second;
    assert(mMaze[deadEnds[0].second][deadEnds[0].first] == msEmpty);
    const int exitX = deadEnds[1].first;
    const int exitY = deadEnds[1].second;
    assert(mMaze[exitY][exitX] == msEmpty);
    mDistances = GetMazeDistances(mIntMaze,exitX,exitY);
    mMaze[deadEnds[1].second][deadEnds[1].first] = MazeSquare::msExit;

    std::vector<std::pair<int,int> >::const_iterator deadEndIterator = deadEnds.begin() + 2;

    {
      //Place swords in maze, only in dead ends
      for (int i=0; i!=nSwords; ++i)
      {
        assert(deadEndIterator != deadEnds.end());
        const int x = (*deadEndIterator).first;
        const int y = (*deadEndIterator).second;
        assert(x!=mX || y!=mY);
        assert(mMaze[y][x] == msEmpty);
        mMaze[y][x] = MazeSquare::msSword;
        ++deadEndIterator;
      }
      //Place prisoners in maze, only in dead ends
      for (int i=0; i!=nPrisoners; ++i)
      {
        assert(deadEndIterator != deadEnds.end());
        const int x = (*deadEndIterator).first;
        const int y = (*deadEndIterator).second;
        assert(x!=mX || y!=mY);
        assert(mMaze[y][x] == msEmpty);
        mMaze[y][x] = MazeSquare::msPrisoner1;
        ++deadEndIterator;
      }

      for (int i=0; i!=nEnemies; ++i)
      {
        assert(deadEndIterator != deadEnds.end());
        const int x = (*deadEndIterator).first;
        const int y = (*deadEndIterator).second;
        assert(mMaze[y][x] == msEmpty);
        mMaze[y][x] = MazeSquare::msEnemy1;
        ++deadEndIterator;
      }
    }
  }
}



#ifndef NDEBUG
void ribi::maziak::QtMaziakMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::maziak::QtMaziakMainDialog::Test");
  QtMaziakMainDialog(0,99);
  TRACE("Finished ribi::maziak::QtMaziakMainDialog::Test successfully");
}
#endif
