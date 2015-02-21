#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttankbattalionarenawidget.h"

#include <cassert>
#include <iostream>

#include <boost/make_shared.hpp>

#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QPainter>

#include "tankbattalionarena.h"
#include "tankbattaliongamewidget.h"
#include "tankbattalionhelper.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::taba::QtArenaWidget::QtArenaWidget(QWidget *parent)
 : QWidget(parent),
   m_widget{new GameWidget}
{
  {
    QTimer * const timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(20);
    timer->start();
  }

}


void ribi::taba::QtArenaWidget::keyPressEvent(QKeyEvent * e)
{
  const bool verbose = false;
  switch (e->key())
  {
    case Qt::Key_Up:
      if (verbose) { TRACE("Pressed up"); }
      m_widget->PressKey(Key::up);
      break;
    case Qt::Key_Right:
      if (verbose) { TRACE("Pressed right"); }
      m_widget->PressKey(Key::right);
      break;
    case Qt::Key_Down:
      if (verbose) { TRACE("Pressed down"); }
      m_widget->PressKey(Key::down);
      break;
    case Qt::Key_Left:
      if (verbose) { TRACE("Pressed left"); }
      m_widget->PressKey(Key::left);
      break;
  }
}

void ribi::taba::QtArenaWidget::keyReleaseEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up   : m_widget->ReleaseKey(Key::up); break;
    case Qt::Key_Right: m_widget->ReleaseKey(Key::right); break;
    case Qt::Key_Down : m_widget->ReleaseKey(Key::down); break;
    case Qt::Key_Left : m_widget->ReleaseKey(Key::left); break;
  }
}

void ribi::taba::QtArenaWidget::OnTimer()
{
  m_widget->OnTimer();
  repaint();
}

void ribi::taba::QtArenaWidget::paintEvent(QPaintEvent *)
{
  //168 wide / 8 = 21
  //176 heigh / 8 = 22
  //Bricks are 8x8, sprites are 16x16
  QPainter painter(this);

}


void ribi::taba::QtArenaWidget::resizeEvent(QResizeEvent *)
{
  const int block_width  = 8;
  const int block_height = 8;
  const auto n_rows = m_widget->GetArena()->GetRows();
  const auto n_cols = m_widget->GetArena()->GetColumns();
  this->setGeometry(0,0,
    n_cols * block_width,
    n_rows * block_height
  );
}
