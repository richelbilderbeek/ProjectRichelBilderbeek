//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2012 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From hhtp://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtbeerwanterwidget.h"

#include <iostream>
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QMouseEvent>
#include <QTimer>
#include <QVBoxLayout>
//---------------------------------------------------------------------------
#include "beerwantermaindialog.h"
//---------------------------------------------------------------------------
QtBeerWanterWidget::QtBeerWanterWidget(QWidget *parent)
  : QWidget(parent),
    m_timer(new QTimer),
    m_sprite(new QPixmap(":/Beer.png"))
{
  assert(!m_sprite.get()->isNull());

  this->setMouseTracking(true);

  m_beerwanter.reset(
    new BeerWanterMainDialog(
      QApplication::desktop()->width(),
      QApplication::desktop()->height(),
      m_sprite->width(),
      m_sprite->height(),
      520,
      520));

  //Ensure the window does not get resized
  this->setFixedHeight(m_beerwanter->GetWindowHeight());
  this->setFixedWidth(m_beerwanter->GetWindowWidth());

  m_timer->connect(m_timer.get(),SIGNAL(timeout()),this,SLOT(onTimer()));
  m_timer->start(20); //Framerate about (1000/20=) 50 fps
}
//---------------------------------------------------------------------------
const BeerWanterMainDialog * QtBeerWanterWidget::GetBeerWanter() const
{
  return m_beerwanter.get();
}
//---------------------------------------------------------------------------
void QtBeerWanterWidget::mouseMoveEvent(QMouseEvent * event)
{
  const int mouse_x = event->x();
  const int mouse_y = event->y();
  //#define DEBUG_SHOW_MOUSE_POSITION
  #ifdef DEBUG_SHOW_MOUSE_POSITION
  m_debug_text
    = "MOVE: ("
    + boost::lexical_cast<std::string>(mouse_x)
    + ","
    + boost::lexical_cast<std::string>(mouse_y)
    + ")";
  if (m_beerwanter->ClickWilBeSuccess())
  {
    m_debug_text += "-> CLICK WILL BE SUCCESS";
  }
  const int sprite_x = m_beerwanter->GetSpriteX();
  const int sprite_y = m_beerwanter->GetSpriteX();
  const int sprite_maxx = m_beerwanter->GetSpriteX() + m_beerwanter->GetSpriteWidth();
  const int sprite_maxy = m_beerwanter->GetSpriteY() + m_beerwanter->GetSpriteHeight();
  m_debug_text += ", Sprite: ("
    + boost::lexical_cast<std::string>(sprite_x)
    + ","
    + boost::lexical_cast<std::string>(sprite_y)
    + ")-("
    + boost::lexical_cast<std::string>(sprite_maxx)
    + ","
    + boost::lexical_cast<std::string>(sprite_maxy)
    + ")";
  #endif
  assert(event->type() == ::QMouseEvent::MouseMove);
  assert(event);
  m_beerwanter->SetCursorPos(mouse_x,mouse_y);
  this->repaint();
}
//---------------------------------------------------------------------------
void QtBeerWanterWidget::mousePressEvent(QMouseEvent *)
{
  //#define DEBUG_SHOW_MOUSE_CLICK_POSITION
  #ifdef DEBUG_SHOW_MOUSE_CLICK_POSITION
  const int mouse_x = event->x();
  const int mouse_y = event->y();
  m_debug_text
    = "CLICK: ("
    + boost::lexical_cast<std::string>(mouse_x)
    + ","
    + boost::lexical_cast<std::string>(mouse_y)
    + ")";
  #endif
  if (m_beerwanter->Click())
  {
    //Inform user of level-up
    emit LevelUp(m_beerwanter->GetWindowTitle());
  }
  this->repaint();
}
//---------------------------------------------------------------------------
void QtBeerWanterWidget::onTimer()
{
  m_beerwanter->ShakeCursor();

  const int mouse_x = m_beerwanter->GetCursorX();
  const int mouse_y = m_beerwanter->GetCursorY();
  //#define DEBUG_SHOW_MOUSE_TIMER_POSITION
  #ifdef DEBUG_SHOW_MOUSE_TIMER_POSITION
  m_debug_text
    = "ONTIMER: ("
    + boost::lexical_cast<std::string>(mouse_x)
    + ","
    + boost::lexical_cast<std::string>(mouse_y)
    + ")";
  #endif

  const QPoint base_pos = this->mapToGlobal(QPoint(0,0));
  #ifdef DEBUG_SHOW_MOUSE_TIMER_POSITION
  m_debug_text
    += "-> ("
    + boost::lexical_cast<std::string>(base_pos.x())
    + ","
    + boost::lexical_cast<std::string>(base_pos.y())
    + ")";
  #endif

  this->cursor().setPos(
    base_pos.x() + mouse_x,base_pos.y() + mouse_y);

  //Move window
  m_beerwanter->ShakeWindow();
  //QtBeerWanterWidget cannot shake itself
  emit DoShake(m_beerwanter->GetWindowX(),m_beerwanter->GetWindowY());
  this->repaint();
}
//---------------------------------------------------------------------------
void QtBeerWanterWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  QPixmap p(this->width(),this->height());
  MyPaint(
    p,
    //std::rand() % 256, std::rand() % 256, std::rand() % 256);
    255,255,255);
  painter.drawPixmap(0,0,p);

  //#define DEBUG_SHOW_BEERWANTER_INFO
  #ifdef DEBUG_SHOW_BEERWANTER_INFO
  painter.drawText(QRectF(0.0,0.0,this->width(),this->height()),m_debug_text.c_str());
  #endif

  assert(m_sprite);
  painter.drawPixmap(
    m_beerwanter->GetSpriteX(),
    m_beerwanter->GetSpriteY(),
    *m_sprite.get());
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void QtBeerWanterWidget::MyPaint(
  QPixmap& pixmap,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b,
  const unsigned char a) //Opaque
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
//---------------------------------------------------------------------------
