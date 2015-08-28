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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtmaziakdisplay.h"

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

ribi::maziak::QtDisplay::QtDisplay(QWidget *parent)
  : QWidget(parent),
    m_image{},
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

  m_timer_press_key->setInterval(100);
  m_timer_enemy->setInterval(1000);
  m_timer_show_solution->setInterval(5000);

  QObject::connect(m_timer_press_key.get(),&QTimer::timeout,
    this,&ribi::maziak::QtDisplay::OnTimerPressKey);
  QObject::connect(m_timer_enemy.get(),&QTimer::timeout,
    this,&ribi::maziak::QtDisplay::OnTimerEnemy);
  QObject::connect(m_timer_show_solution.get(),&QTimer::timeout,
    this,&ribi::maziak::QtDisplay::OnTimerStopShowingSolution);

  m_timer_press_key->start();
  m_timer_enemy->start();

  //Put the dialog in the screen center at 75% of fullscreen size
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 75 / 100,screen.height() * 75 / 100);
  this->move( screen.center() - this->rect().center() );
}

std::map<ribi::maziak::QtDisplay::WORD,ribi::maziak::Key> ribi::maziak::QtDisplay::CreateDefaultKeys() noexcept
{
  std::map<WORD,Key> m;
  m.insert(std::make_pair(Qt::Key_Up   ,Key::up   ));
  m.insert(std::make_pair(Qt::Key_Right,Key::right));
  m.insert(std::make_pair(Qt::Key_Down ,Key::down ));
  m.insert(std::make_pair(Qt::Key_Left ,Key::left ));
  return m;
}

void ribi::maziak::QtDisplay::DoDisplay(const MainDialog& /* main_dialog */)
{
  qApp->processEvents();
  this->repaint();
  this->show();
}

void ribi::maziak::QtDisplay::resizeEvent(QResizeEvent*)
{
  this->repaint();
}

void ribi::maziak::QtDisplay::keyPressEvent(QKeyEvent* e)
{
  switch (e->key())
  {
    case Qt::Key_Up   : m_keys.insert(Key::up   ); break;
    case Qt::Key_Right: m_keys.insert(Key::right); break;
    case Qt::Key_Down : m_keys.insert(Key::down ); break;
    case Qt::Key_Left : m_keys.insert(Key::left ); break;
  }
}

void ribi::maziak::QtDisplay::keyReleaseEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up   : m_keys.erase(Key::up   ); break;
    case Qt::Key_Right: m_keys.erase(Key::right); break;
    case Qt::Key_Down : m_keys.erase(Key::down ); break;
    case Qt::Key_Left : m_keys.erase(Key::left ); break;
  }
}

void ribi::maziak::QtDisplay::OnTimerPressKey()
{
  m_dialog->OnTimerPressKeys();
  repaint();
}

void ribi::maziak::QtDisplay::OnTimerEnemy()
{
  m_dialog->AnimateEnemiesAndPrisoners(m_view_width,m_view_height);
  repaint();
}

void ribi::maziak::QtDisplay::OnTimerStopShowingSolution()
{
  m_dialog->SetShowSolution(false);
  m_timer_show_solution->stop();
}

void ribi::maziak::QtDisplay::OnTimerStartShowingSolution()
{
  m_timer_show_solution->start();
}

void ribi::maziak::QtDisplay::paintEvent(QPaintEvent *)
{
  const int block_width  = width()  / m_view_width;
  const int block_height = height() / m_view_height;

  m_dialog->AnimateFighting();

  //Player-environment interactions
  QPainter painter(this);
  assert(painter.isActive());

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
      ((m_view_width  / 2) * block_width ) + 0,
      ((m_view_height / 2) * block_height) + 0,
       block_width,
       block_height,
       *player
     );
  }
}

void ribi::maziak::QtDisplay::OnGameOver()
{
  m_timer_press_key->stop();
  m_timer_enemy->stop();
  m_timer_show_solution->stop();
  this->hide();
  boost::scoped_ptr<QtMaziakGameOverDialog> f(new QtMaziakGameOverDialog(0));
  f->exec();
  close();
}

void ribi::maziak::QtDisplay::OnGameWon()
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

std::set<ribi::maziak::Key> ribi::maziak::QtDisplay::RequestKeys()
{
  return m_keys;
}

#ifndef NDEBUG
void ribi::maziak::QtDisplay::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtDisplay(19);
  maziak::MainDialog(7);
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
