//---------------------------------------------------------------------------
/*
EverythingToPiecesShooter. A multiplayer soccer/billiards game.
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
//From http://www.richelbilderbeek.nl/GameEverythingToPiecesShooter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
/*
#include "qteverythingtopiecesshootermaindialog.h"

#include <cassert>
#include <cstdlib>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>

#include "ui_qteverythingtopiecesshootermaindialog.h"
#include "trace.h"

#pragma GCC diagnostic pop

///All parameters are fed into the contructor
ribi::QtEverythingToPiecesShooterMainDialog::QtEverythingToPiecesShooterMainDialog(
  QWidget *parent,
) : QtHideAndShowDialog(parent),
    ui(new Ui::QtEverythingToPiecesShooterMainDialog),
    m_timer(new QTimer)
{
  ui->setupUi(this);

  ///Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
  if (!m_is_training)
  {
    m_timer_countdown->start(1000);
  }
}

ribi::QtEverythingToPiecesShooterMainDialog::~QtEverythingToPiecesShooterMainDialog() noexcept
{
  m_timer->stop();
  m_timer_countdown->stop();
  delete ui;
}

void ribi::QtEverythingToPiecesShooterMainDialog::paintEvent(QPaintEvent*)
{
  QPainter painter(this);

  ///Draw background on painter
  painter.drawPixmap(rect(),*m_background);

  ///Draw all sprites on painter
  {
    //Set the pen to white and 3 pixels wide
    QPen pen = painter.pen();
    pen.setWidth(3);
    pen.setColor(QColor(255,255,255));
    painter.setPen(pen);
  }
  ///Call EverythingToPiecesShooter to draw the sprites
  m_everythingtopiecesshooter->drawPlayers(painter);
  ///Draw score on painter
  {
    QFont font = painter.font();
    font.setFamily("Courier");
    painter.setFont(font);
    const std::pair<int,int> scores = m_everythingtopiecesshooter->GetScore();
    const QString score_left
      = QString(boost::lexical_cast<std::string>(scores.first).c_str());
    const QString score_right
      = boost::lexical_cast<std::string>(scores.second).c_str();
    painter.drawText(120,0,80,20,0,score_left);
    painter.drawText(440,0,80,20,0,score_right);
  }
}

///Handles key presses.
///These are ignored when the computer is training
void ribi::QtEverythingToPiecesShooterMainDialog::keyPressEvent(QKeyEvent * e)
{
  if (m_is_training) return;
  //Assume that a key is pressed
  //(which according to the Qt doc is always true)
  assert(e->type() == QEvent::KeyPress);
  m_everythingtopiecesshooter->pressKey(e->key());
}

///This method gives the game 1000 msecs time
///to do those magical start-up things...
void ribi::QtEverythingToPiecesShooterMainDialog::onCountdownTimer()
{
  assert(!m_is_training);
  m_timer_countdown->stop();
  m_timer->start(20);
}

///The main method when not training:
///every 50msec the Sprites
///move and are drawn to the screen
void ribi::QtEverythingToPiecesShooterMainDialog::onTimer()
{
  assert(!m_is_training);
  ///EverythingToPiecesShooter moves all sprites
  m_everythingtopiecesshooter->tick();
  ///Repaint the screen
  this->repaint();
}

void ribi::QtEverythingToPiecesShooterMainDialog::Paint(
  QPixmap& pixmap,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b,
  const unsigned char a)
{
  const int width = pixmap.width();
  const int height = pixmap.height();

  QImage image = pixmap.toImage();

  assert(image.bytesPerLine() / width == 4
    && "Assume there are 4 bytes per pixel");

  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image.scanLine(y));
    for (int x=0; x!=width; ++x)
    {
      line[x*4+3] = a; //Alpha value
      line[x*4+2] = r; //Red
      line[x*4+1] = g; //Green
      line[x*4+0] = b; //Blue
    }
  }
  pixmap = pixmap.fromImage(image);
}

#ifndef NDEBUG
void ribi::QtEverythingToPiecesShooterMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtEverythingToPiecesShooterMainDialog::Test");
  TRACE("Finished ribi::QtEverythingToPiecesShooterMainDialog::Test successfully");
}
#endif
*/
