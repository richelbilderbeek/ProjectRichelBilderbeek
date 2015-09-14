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
#include <QApplication>
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
#include "qtgraphics.h"
#include "maziaksolutionmaze.h"
#include "maziakmaindialog.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::maziak::QtDisplay::QtDisplay(QWidget *parent)
  : QWidget(parent),
    m_image{QtGraphics().CreateImage(22 * ((9 * 2) + 1), 22 * ((9 * 2) + 1))},
    m_keys{},
    m_sprites(new Sprites),
    m_timer_animate_enemies_and_prisoners{},
    m_timer_show_solution{}
{
  #ifndef NDEBUG
  Test();
  #endif

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

void ribi::maziak::QtDisplay::DoDisplay(const MainDialog& main_dialog)
{
  const int block_width  = 22;
  const int block_height = 22;
  const int view_height{GetViewHeight()};
  const int view_width{GetViewWidth()};
  //Draw maze
  {
    for (int y=0; y!=view_height; ++y)
    {
      for (int x=0; x!=view_width; ++x)
      {
        //xVector and yVector are the indices in the non-visual maze 2D std::vector
        const int xVector = main_dialog.GetX() - (view_width  / 2) + x;
        const int yVector = main_dialog.GetY() - (view_height / 2) + y;
        //Draw the floor tile
        const boost::shared_ptr<const QPixmap> pixmap_floor {
          m_sprites->Get(
            main_dialog.GetSpriteFloor(
              xVector,
              yVector
            )
          )
        };

        assert(pixmap_floor);
        QtGraphics().DrawImage(
          m_image,
          pixmap_floor->toImage(),
          (x * block_width )+0,
          (y * block_height)+0
        );
        //Draw what's moving or standing on the floor
        const auto pixmap_above_floor(
          m_sprites->Get(
            main_dialog.GetSpriteAboveFloor(
              xVector,
              yVector
            )
          )
        );
        assert(pixmap_above_floor);
        QtGraphics().DrawImage(
          m_image,
          pixmap_above_floor->toImage(),
          (x * block_width )+0,
          (y * block_height)+0
        );
      }
    }
  }

  //Draw player
  {
    const boost::shared_ptr<const QPixmap> player {
      m_sprites->Get(
        main_dialog.GetSpritePlayer()
      )
    };
    assert(player);
    QtGraphics().DrawImage(
      m_image,
      player->toImage(),
      ((view_width  / 2) * block_width ) + 0,
      ((view_height / 2) * block_height) + 0
     );
  }
  this->repaint();
}

bool ribi::maziak::QtDisplay::GetDoShowSolution()
{
  return m_timer_show_solution.GetElapsedSecs() < 5.0;
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

bool ribi::maziak::QtDisplay::MustAnimateEnemiesAndPrisoners() noexcept
{
  if (m_timer_animate_enemies_and_prisoners.GetElapsedSecs() > 0.9)
  {
    m_timer_animate_enemies_and_prisoners = Stopwatch();
    return true;
  }
  return false;
}

void ribi::maziak::QtDisplay::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(0,0,m_image);
}

void ribi::maziak::QtDisplay::OnGameOver()
{
  this->hide();
  boost::scoped_ptr<QtMaziakGameOverDialog> f(new QtMaziakGameOverDialog(0));
  f->exec();
  close();
}

void ribi::maziak::QtDisplay::OnGameWon()
{
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

void ribi::maziak::QtDisplay::StartShowSolution()
{
  m_timer_show_solution = Stopwatch();
}

#ifndef NDEBUG
void ribi::maziak::QtDisplay::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    maziak::MainDialog d(7);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    QtDisplay q;
    //Cannot test this in constructor: never call virtual functions in a class constructor
    assert(q.GetViewHeight() == 9);
    assert(q.GetViewWidth() == 9);
  }
  {
    QtDisplay q;
    maziak::MainDialog d(7);
    d.SetDisplay(&q);
    q.show();
  }
}
#endif
