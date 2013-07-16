//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
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
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtboenkenmaindialog.h"

#include <cassert>
#include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>

#include "boenkengame.h"
#include "ui_qtboenkenmaindialog.h"

///All parameters are fed into the contructor
QtBoenkenMainDialog::QtBoenkenMainDialog(
  QWidget *parent,
  boost::shared_ptr<Boenken::Game> boenken,
  bool is_training)
  : QDialog(parent),
    ui(new Ui::QtBoenkenMainDialog),
    m_background(new QPixmap),
    m_timer(new QTimer),
    m_timer_countdown(new QTimer),
    m_boenken(boenken),
    m_is_training(is_training)
{
  ui->setupUi(this);


  ///Set GUI size to Boenken size
  this->setGeometry(0,0,m_boenken->getWidth(),m_boenken->getHeight());
  ///Size the black background
  m_background.reset(new QPixmap(m_boenken->getWidth(),m_boenken->getHeight()));
  Paint(*m_background,1,1,1); //Black
  ///Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
  ///Disallow resize from now on
  this->setFixedWidth(m_boenken->getWidth());
  this->setFixedHeight(m_boenken->getHeight());

  ///Start the timer
  QObject::connect( m_timer.get(),SIGNAL(timeout()),this,SLOT(onTimer()));
  QObject::connect( m_timer_countdown.get(),SIGNAL(timeout()),this,SLOT(onCountdownTimer()));
  if (!m_is_training)
  {
    m_timer_countdown->start(1000);
  }
}

QtBoenkenMainDialog::~QtBoenkenMainDialog()
{
  m_timer->stop();
  m_timer_countdown->stop();
  delete ui;
}

void QtBoenkenMainDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}


void QtBoenkenMainDialog::paintEvent(QPaintEvent*)
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
  ///Call Boenken to draw the sprites
  m_boenken->drawPlayers(painter);
  ///Draw score on painter
  {
    QFont font = painter.font();
    font.setFamily("Courier");
    painter.setFont(font);
    const std::pair<int,int> scores = m_boenken->GetScore();
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
void QtBoenkenMainDialog::keyPressEvent(QKeyEvent * e)
{
  if (m_is_training) return;
  //Assume that a key is pressed
  //(which according to the Qt doc is always true)
  assert(e->type() == QEvent::KeyPress);
  m_boenken->pressKey(e->key());
}

///This method gives the game 1000 msecs time
///to do those magical start-up things...
void QtBoenkenMainDialog::onCountdownTimer()
{
  assert(!m_is_training);
  m_timer_countdown->stop();
  m_timer->start(20);
}

///The main method when not training:
///every 50msec the Sprites
///move and are drawn to the screen
void QtBoenkenMainDialog::onTimer()
{
  assert(!m_is_training);
  ///Boenken moves all sprites
  m_boenken->tick();
  ///Repaint the screen
  this->repaint();
}

void QtBoenkenMainDialog::Paint(
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

void QtBoenkenMainDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    //boost::shared_ptr<Boenken::Game> p(new Boenken::Game(
  }
}

///Null function
//boost::shared_ptr<Boenken::Game> CreateNoBoenken()
//{
//  boost::shared_ptr<Boenken::Game> p;
//  return p;
//}
