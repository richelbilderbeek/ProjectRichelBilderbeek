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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtzeromaindialog.h"

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
#include <QPixmap>
#include <QTimer>

#include "testtimer.h"

#include "ui_qtzeromaindialog.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::QtZeroMainDialog::QtZeroMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtZeroMainDialog),
    m_keys_pressed{},
    m_player_sprite{std::make_unique<QPixmap>()},
    m_player_x{0},
    m_player_y{0},
    m_timer_press_key{std::make_unique<QTimer>()}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  ///Keys are virtually pressed every 10 milliseconds
  m_timer_press_key->setInterval(10);

  ///Connect the key-press-timer to the OnTimerPressKey event
  QObject::connect(m_timer_press_key.get(),&QTimer::timeout,
    this,&ribi::QtZeroMainDialog::OnTimerPressKey);
  ///Start the key-press-timer
  m_timer_press_key->start();

  //Put the dialog in the screen center at 75% of fullscreen size
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 75 / 100,screen.height() * 75 / 100);
  this->move( screen.center() - this->rect().center() );

  //Set the player in the middle
  m_player_x = ((screen.center().x() * 75) / 100) - (m_player_sprite->width() / 2);
  m_player_y = ((screen.center().y() * 75) / 100) - (m_player_sprite->height() / 2);
}

ribi::QtZeroMainDialog::~QtZeroMainDialog() noexcept
{
  delete ui;
}

void ribi::QtZeroMainDialog::resizeEvent(QResizeEvent*)
{
  this->repaint();
}

void ribi::QtZeroMainDialog::keyPressEvent(QKeyEvent* e)
{
  ///Store the key pressed down
  m_keys_pressed.insert(e->key());
}

void ribi::QtZeroMainDialog::keyReleaseEvent(QKeyEvent * e)
{
  ///Remove the key released
  m_keys_pressed.erase(e->key());
}

void ribi::QtZeroMainDialog::OnTimerPressKey()
{
  ///Respond to the keys that are pressed
  if(m_keys_pressed.count(Qt::Key_Up   )) { --m_player_y; }
  if(m_keys_pressed.count(Qt::Key_Right)) { ++m_player_x; }
  if(m_keys_pressed.count(Qt::Key_Down )) { ++m_player_y; }
  if(m_keys_pressed.count(Qt::Key_Left )) { --m_player_x; }

  ///Start the paintEvent
  repaint();
}

void ribi::QtZeroMainDialog::paintEvent(QPaintEvent *)
{
  //Obtain the painter (do not touch)
  QPainter painter(this);

  //Paint the background
  painter.drawPixmap(this->rect(),QPixmap(":/GameZero/images/GameZeroBackground.png"));

  //Paint the player
  painter.drawPixmap(m_player_x,m_player_y,QPixmap(":/GameZero/images/GameZeroBeer.png"));
}

#ifndef NDEBUG
void ribi::QtZeroMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtZeroMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
