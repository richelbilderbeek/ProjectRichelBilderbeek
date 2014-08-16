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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
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
#include "testtimer.h"
#include "qtmaziakgamewondialog.h"
#include "maziaksolutionmaze.h"
#include "maziakmaindialog.h"
#include "ui_qtmaziakmaindialog.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::maziak::QtMaziakMainDialog::QtMaziakMainDialog(
  const int maze_size,
  QWidget *parent
)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtMaziakMainDialog),
    m_dialog{new MainDialog(maze_size)},
    m_keys{},
    m_sprites(new Sprites),
    m_timer_enemy(new QTimer),
    m_timer_press_key(new QTimer),
    m_timer_show_solution(new QTimer),
    m_view_height(9),
    m_view_width(9)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  m_dialog->m_signal_game_over.connect(
    boost::bind(&ribi::maziak::QtMaziakMainDialog::OnGameOver,this)
  );
  m_dialog->m_signal_game_won.connect(
    boost::bind(&ribi::maziak::QtMaziakMainDialog::OnGameWon,this)
  );
  m_dialog->m_signal_start_showing_solution.connect(
    boost::bind(&ribi::maziak::QtMaziakMainDialog::OnTimerStartShowingSolution,this)
  );

  assert(maze_size && "Maze size must be 7 + (4 * n) for n e [0,->>");
  assert(m_dialog->GetMaze()->IsSquare());

  m_timer_press_key->setInterval(100);
  m_timer_enemy->setInterval(1000);
  m_timer_show_solution->setInterval(5000);

  QObject::connect(m_timer_press_key.get(),&QTimer::timeout,
    this,&ribi::maziak::QtMaziakMainDialog::OnTimerPressKey);
  QObject::connect(m_timer_enemy.get(),&QTimer::timeout,
    this,&ribi::maziak::QtMaziakMainDialog::OnTimerEnemy);
  QObject::connect(m_timer_show_solution.get(),&QTimer::timeout,
    this,&ribi::maziak::QtMaziakMainDialog::OnTimerStopShowingSolution);

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

const std::map<ribi::maziak::QtMaziakMainDialog::WORD,ribi::maziak::Key> ribi::maziak::QtMaziakMainDialog::CreateDefaultKeys() noexcept
{
  std::map<WORD,Key> m;
  m.insert(std::make_pair(Qt::Key_Up   ,Key::up   ));
  m.insert(std::make_pair(Qt::Key_Right,Key::right));
  m.insert(std::make_pair(Qt::Key_Down ,Key::down ));
  m.insert(std::make_pair(Qt::Key_Left ,Key::left ));
  return m;
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
    case Qt::Key_F1   : OnGameOver(); close(); break;
    case Qt::Key_F2   : OnGameWon(); close(); break;
    case Qt::Key_Escape: close(); break;
  }
}

void ribi::maziak::QtMaziakMainDialog::keyReleaseEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Left : m_dialog->OnKeyRelease(Key::left); break;
    case Qt::Key_Right: m_dialog->OnKeyRelease(Key::right); break;
    case Qt::Key_Up   : m_dialog->OnKeyRelease(Key::up); break;
    case Qt::Key_Down : m_dialog->OnKeyRelease(Key::down); break;
  }
}

void ribi::maziak::QtMaziakMainDialog::OnTimerPressKey()
{
  m_dialog->OnTimerPressKeys();
  repaint();
}

void ribi::maziak::QtMaziakMainDialog::OnTimerEnemy()
{
  m_dialog->AnimateEnemiesAndPrisoners(m_view_width,m_view_height);
  repaint();
}

void ribi::maziak::QtMaziakMainDialog::OnTimerStopShowingSolution()
{
  m_dialog->SetShowSolution(false);
  m_timer_show_solution->stop();
}

void ribi::maziak::QtMaziakMainDialog::OnTimerStartShowingSolution()
{
  m_timer_show_solution->start();
}

void ribi::maziak::QtMaziakMainDialog::paintEvent(QPaintEvent *)
{
  //const int block_width  = 1 + ((ui->widget->width()  - 4) / m_view_width);
  //const int block_height = 1 + ((ui->widget->height() - 4) / m_view_height);
  const int block_width  = width()  / m_view_width;
  const int block_height = height() / m_view_height;

  m_dialog->AnimateFighting();

  //Player-environment interactions
  QPainter painter(this);
  assert(painter.isActive());

  //Clean painter
  //?Really needed?
  /*
  {
    const boost::shared_ptr<const QPixmap> temp { m_sprites->Get(Sprite::empty) };

    assert(temp);
    painter.drawPixmap(ui->widget->rect(),*temp);
  }
  */

  m_dialog->RespondToCurrentSquare();

  //Draw maze
  {
    for (int y=0; y!=m_view_height; ++y)
    {
      for (int x=0; x!=m_view_width; ++x)
      {
        //xVector and yVector are the indices in the non-visual maze 2D std::vector
        const int xVector = m_dialog->GetX() - (m_view_width  / 2) + x;
        const int yVector = m_dialog->GetY() - (m_view_height / 2) + y;
        //Draw the floor tile
        const boost::shared_ptr<const QPixmap> pixmap_floor {
          m_sprites->Get(
            m_dialog->GetSpriteFloor(
              xVector,
              yVector
            )
          )
        };
        assert(pixmap_floor);
        painter.drawPixmap(
          (x * block_width )+0,
          (y * block_height)+0,
          block_width,
          block_height,
          *pixmap_floor);
        //Draw what's moving or standing on the floor
        const auto pixmap_above_floor(
          m_sprites->Get(
            m_dialog->GetSpriteAboveFloor(
              xVector,
              yVector
            )
          )
        );
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
      m_sprites->Get(
        m_dialog->GetSpritePlayer()
      )
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

void ribi::maziak::QtMaziakMainDialog::OnGameOver()
{
  m_timer_press_key->stop();
  m_timer_enemy->stop();
  m_timer_show_solution->stop();
  this->hide();
  boost::scoped_ptr<QtMaziakGameOverDialog> f(new QtMaziakGameOverDialog(0));
  f->exec();
  close();
}

void ribi::maziak::QtMaziakMainDialog::OnGameWon()
{
  m_timer_press_key->stop();
  m_timer_enemy->stop();
  m_timer_show_solution->stop();
  this->hide();
  boost::scoped_ptr<QtMaziakGameWonDialog> f(new QtMaziakGameWonDialog);
  this->hide();
  f->exec();
  close();
}




#ifndef NDEBUG
void ribi::maziak::QtMaziakMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtMaziakMainDialog(99);
  maziak::MainDialog(7);
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
