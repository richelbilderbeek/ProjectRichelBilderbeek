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
#include "maziakmaze.h"
#include "maziaksprites.h"
#include "qtmaziakgameoverdialog.h"
#include "qtmaziakgamewondialog.h"
#include "maziaksolutionmaze.h"
#include "maziakmaindialog.h"
#include "ui_qtmaziakmaindialog.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::maziak::QtMaziakMainDialog::QtMaziakMainDialog(
  QWidget *parent,
  const int maze_size)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtMaziakMainDialog),
    m_direction(PlayerDirection::pdDown),
    m_distances{},
    m_do_show_solution(false),
    m_fighting_frame(0),
    m_has_sword(true),
    m_keys{},
    m_maze{new Maze(maze_size)},
    m_move_now(PlayerMove::none),
    m_solution{},
    m_sprites(new Sprites),
    m_timer_enemy(new QTimer),
    m_timer_press_key(new QTimer),
    m_timer_show_solution(new QTimer),
    m_view_height(9),
    m_view_width(9),
    m_x(-1),
    m_y(-1)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {
    const std::pair<int,int> exit = m_maze->FindExit();
    m_distances = m_maze->GetIntMaze()->GetDistancesMaze(exit.first,exit.second);
  }
  {
    const std::pair<int,int> start = m_maze->FindStart();
    m_x = start.first;
    m_y = start.second;
  }

  assert(maze_size && "Maze size must be 7 + (4 * n) for n e [0,->>");
  assert(m_maze->IsSquare());
  m_solution = CreateNewSolution();

  m_timer_press_key->setInterval(100);
  m_timer_enemy->setInterval(1000);
  m_timer_show_solution->setInterval(5000);

  QObject::connect(m_timer_press_key.get(),SIGNAL(timeout()),
    this,SLOT(onTimerPressKey()));
  QObject::connect(m_timer_enemy.get(),SIGNAL(timeout()),
    this,SLOT(onTimerEnemy()));
  QObject::connect(m_timer_show_solution.get(),SIGNAL(timeout()),
    this,SLOT(onTimerShowSolution()));

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

const boost::shared_ptr<const ribi::maziak::SolutionMaze> ribi::maziak::QtMaziakMainDialog::CreateNewSolution() noexcept
{
  const boost::shared_ptr<const SolutionMaze> solution {
    new SolutionMaze(m_distances,m_x,m_y)
  };
  assert(solution);
  return solution;
}

void ribi::maziak::QtMaziakMainDialog::resizeEvent(QResizeEvent*)
{
  this->repaint();
}

void ribi::maziak::QtMaziakMainDialog::keyPressEvent(QKeyEvent* e)
{
  switch (e->key())
  {
    case Qt::Key_Left : m_dialog->OnKeyPress(Key::left); break;
    case Qt::Key_Right: m_dialog->OnKeyPress(Key::right); break;
    case Qt::Key_Up   : m_dialog->OnKeyPress(Key::up); break;
    case Qt::Key_Down : m_dialog->OnKeyPress(Key::down); break;
    case Qt::Key_F1   : GameOver(); close(); break;
    case Qt::Key_F2   : GameWon(); close(); break;
    case Qt::Key_Escape: close(); break;
  }
}

void ribi::maziak::QtMaziakMainDialog::keyReleaseEvent(QKeyEvent * e)
{
  m_keys.erase(e->key());
}

void ribi::maziak::QtMaziakMainDialog::onTimerPressKey()
{
  if (m_fighting_frame > 0) return;
  if (m_keys.empty()) { m_move_now = PlayerMove::none; }

  for(WORD key: m_keys)
  {
    //Check the keys pressed
    switch (key)
    {
      case Qt::Key_Left:
        m_direction = PlayerDirection::pdLeft;
        if (!m_maze->CanMoveTo(m_x-1,m_y,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::left1 ? PlayerMove::left2 : PlayerMove::left1);
        --m_x;
        break;
      case Qt::Key_Right:
        m_direction = PlayerDirection::pdRight;
        if (!m_maze->CanMoveTo(m_x+1,m_y,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::right1 ? PlayerMove::right2 : PlayerMove::right1);
        ++m_x;
        break;
      case Qt::Key_Up:
        m_direction = PlayerDirection::pdUp;
        if (!m_maze->CanMoveTo(m_x,m_y-1,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::up1 ? PlayerMove::up2 : PlayerMove::up1);
        --m_y;
        break;
      case Qt::Key_Down:
        m_direction = PlayerDirection::pdDown;
        if (!m_maze->CanMoveTo(m_x,m_y+1,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::down1 ? PlayerMove::down2 : PlayerMove::down1);
        ++m_y;
        break;
      default:
        m_move_now = PlayerMove::none;
        continue;
    }
    //Draw the screen
    repaint();
  }
}

void ribi::maziak::QtMaziakMainDialog::onTimerEnemy()
{
  m_maze->AnimateEnemiesAndPrisoners(
    m_x,
    m_y,
    m_view_width,
    m_view_height
  );

  repaint();
}

void ribi::maziak::QtMaziakMainDialog::onTimerShowSolution()
{
  m_do_show_solution = false;
  m_timer_show_solution->stop();
}

void ribi::maziak::QtMaziakMainDialog::paintEvent(QPaintEvent *)
{
  const int block_width  = 1 + ((ui->widget->width()  - 4) / m_view_width);
  const int block_height = 1 + ((ui->widget->height() - 4) / m_view_height);

  if (m_fighting_frame > 0)
  {
    ++m_fighting_frame;
    if (m_fighting_frame == 13)
    {
      if (!m_has_sword)
      {
        GameOver();
        this->close();
      }
      m_fighting_frame = 0;
      m_has_sword = false;
    }
  }

  //Player-environment interactions
  QPainter painter(this);
  assert(painter.isActive());

  //Clean painter
  {
    const boost::shared_ptr<const QPixmap> temp { m_sprites->Get(Sprite::empty) };

    assert(temp);
    painter.drawPixmap(ui->widget->rect(),*temp);
  }

  assert(m_maze->CanGet(m_x,m_y));
  switch (m_maze->Get(m_x,m_y))
  {
    case MazeSquare::msStart:
    case MazeSquare::msEmpty:
      break;
    case MazeSquare::msWall:
      assert(!"Should not get here");
      throw std::logic_error("Player cannot be in wall");
    case MazeSquare::msEnemy1: case MazeSquare::msEnemy2:
      m_fighting_frame = 1;
      m_maze->Set(m_x,m_y,MazeSquare::msEmpty);
      break;
    case MazeSquare::msPrisoner1: case MazeSquare::msPrisoner2:
      m_maze->Set(m_x,m_y,MazeSquare::msEmpty);
      m_solution = CreateNewSolution();
      //GetDistancesPath(m_distances,m_x,m_y);
      assert(m_solution->IsSquare());
      m_do_show_solution = true;
      m_timer_show_solution->start();
      break;
    case MazeSquare::msSword:
      m_maze->Set(m_x,m_y,MazeSquare::msEmpty);
      m_has_sword = true;
      break;
    case MazeSquare::msExit:
    {
      GameWon();
      this->close();
      break;
    }
    default:
      assert(!"Should not get here");
      break;
  }

  //Draw maze
  {
    for (int y=0; y!=m_view_height; ++y)
    {
      for (int x=0; x!=m_view_width; ++x)
      {
        //xVector and yVector are the indices in the non-visual maze 2D std::vector
        const int xVector = m_x - (m_view_width  / 2) + x;
        const int yVector = m_y - (m_view_height / 2) + y;
        //Draw the floor tile
        const auto pixmap_floor = m_sprites->Get(GetSpriteFloor(m_maze,xVector,yVector,m_do_show_solution,m_solution));
        assert(pixmap_floor);
        painter.drawPixmap(
          (x * block_width )+0,
          (y * block_height)+0,
          block_width,
          block_height,
          *pixmap_floor);
        //Draw what's moving or standing on the floor
        const auto pixmap_above_floor = m_sprites->Get(GetSpriteAboveFloor(xVector,yVector,m_maze));
        assert(pixmap_above_floor);
        painter.drawPixmap(
          (x * block_width )+0,
          (y * block_height)+0,
          block_width,
          block_height,
          *pixmap_above_floor
        );
      }
    }
  }

  //Draw player
  {
    const boost::shared_ptr<const QPixmap> player {
      m_sprites->Get(GetSpritePlayer(m_direction,m_move_now,m_has_sword,m_fighting_frame))
    };
    assert(player);
    painter.drawPixmap(
      ((m_view_width  / 2) * block_width )+0,
      ((m_view_height / 2) * block_height)+0,
       block_width,
       block_height,
       *player
     );
  }
}

void ribi::maziak::QtMaziakMainDialog::GameOver()
{
  m_timer_press_key->stop();
  m_timer_enemy->stop();
  m_timer_show_solution->stop();
  this->hide();
  boost::scoped_ptr<QtMaziakGameOverDialog> f(new QtMaziakGameOverDialog(0));
  f->exec();
}

void ribi::maziak::QtMaziakMainDialog::GameWon()
{
  m_timer_press_key->stop();
  m_timer_enemy->stop();
  m_timer_show_solution->stop();
  this->hide();
  boost::scoped_ptr<QtMaziakGameWonDialog> f(new QtMaziakGameWonDialog);
  this->hide();
  f->exec();
}


ribi::maziak::Sprite ribi::maziak::QtMaziakMainDialog::GetSpriteFloor(
  const boost::shared_ptr<const Maze> maze,
  const int x,
  const int y,
  const bool do_show_solution,
  const boost::shared_ptr<const SolutionMaze> solution
) noexcept
{
  assert(do_show_solution == false || solution->GetSize() == maze->GetSize());
  if (!maze->CanGet(x,y)) { return Sprite::wall; }
  else if (do_show_solution
    && solution->Get(x,y) == 1
    && ( maze->Get(x,y) == MazeSquare::msEmpty
      || maze->Get(x,y) == MazeSquare::msEnemy1
      || maze->Get(x,y) == MazeSquare::msEnemy2)
    )
  {
    return Sprite::path;
  }
  return Sprite::empty;
}

ribi::maziak::Sprite ribi::maziak::QtMaziakMainDialog::GetSpriteAboveFloor(
  const int x,
  const int y,
  const boost::shared_ptr<const Maze> maze
) noexcept
{
  if (!maze->CanGet(x,y)) { return Sprite::wall; }
  //What else here?
  switch(maze->Get(x,y))
  {
    case MazeSquare::msStart     :
    case MazeSquare::msEmpty     : return Sprite::transparent;
    case MazeSquare::msWall      : return Sprite::wall;
    case MazeSquare::msEnemy1    : return Sprite::enemy1;
    case MazeSquare::msEnemy2    : return Sprite::enemy2;
    case MazeSquare::msPrisoner1 : return Sprite::prisoner1;
    case MazeSquare::msPrisoner2 : return Sprite::prisoner2;
    case MazeSquare::msSword     : return Sprite::sword;
    case MazeSquare::msExit      : return Sprite::exit;
    default:
      assert(!"Should not get here");
      throw std::logic_error("Unexpected MazeSquare at mMaze");
  }
}

ribi::maziak::Sprite ribi::maziak::QtMaziakMainDialog::GetSpritePlayer(
  const PlayerDirection direction,
  const PlayerMove move,
  const bool has_sword,
  const int fighting_frame
) noexcept
{
  switch (fighting_frame)
  {
    case  0: break;
    case  1: return has_sword ? Sprite::fight_sword1 : Sprite::fight_no_sword1;
    case  2: return Sprite::fight2;
    case  3: return Sprite::fight3;
    case  4: return Sprite::fight4;
    case  5: return has_sword ? Sprite::fight_sword1 : Sprite::fight_no_sword1;
    case  6: return Sprite::fight2;
    case  7: return Sprite::fight3;
    case  8: return Sprite::fight4;
    case  9: return has_sword ? Sprite::fight_won1 : Sprite::fight_lost1;
    case 10: return has_sword ? Sprite::fight_won2 : Sprite::fight_lost2;
    case 11: return has_sword ? Sprite::fight_won1 : Sprite::fight_lost1;
    case 12: return has_sword ? Sprite::fight_won2 : Sprite::fight_lost2;
  }

  switch (direction)
  {
    case PlayerDirection::pdUp:
    {
      switch (move)
      {
      case PlayerMove::none: return has_sword ? Sprite::player_look_up_sword : Sprite::player_look_up;
      case PlayerMove::up1:  return has_sword ? Sprite::player_walk_up_sword1 : Sprite::player_walk_up1;
      case PlayerMove::up2:  return has_sword ? Sprite::player_walk_up_sword2 : Sprite::player_walk_up2;
      default:
        assert("!Should not get here");
        throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == up");
      }
    }
    //break; Unreachable
    case PlayerDirection::pdRight:
    {
      switch (move)
      {
        case PlayerMove::none:   return has_sword ? Sprite::player_look_right_sword : Sprite::player_look_right;
        case PlayerMove::right1: return has_sword ? Sprite::player_walk_right_sword1 : Sprite::player_walk_right1;
        case PlayerMove::right2: return has_sword ? Sprite::player_walk_right_sword2 : Sprite::player_walk_right2;
        default:
          assert("!Should not get here");
          throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == right");
      }
    }
    //break; Unreachable
    case PlayerDirection::pdDown:
    {
      switch (move)
      {
      case PlayerMove::none:  return has_sword ? Sprite::player_look_down_sword : Sprite::player_look_down;
      case PlayerMove::down1: return has_sword ? Sprite::player_walk_down_sword1 : Sprite::player_walk_down1;
      case PlayerMove::down2: return has_sword ? Sprite::player_walk_down_sword2 : Sprite::player_walk_down2;
      default:
        assert("!Should not get here");
        throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == down");
      }
    }
    //break; Unreachable
    case PlayerDirection::pdLeft:
    {
      switch (move)
      {
        case PlayerMove::none:  return (has_sword ? Sprite::player_look_left_sword : Sprite::player_look_left);
        case PlayerMove::left1: return (has_sword ? Sprite::player_walk_left_sword1 : Sprite::player_walk_left1);
        case PlayerMove::left2: return (has_sword ? Sprite::player_walk_left_sword2 : Sprite::player_walk_left2);
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
