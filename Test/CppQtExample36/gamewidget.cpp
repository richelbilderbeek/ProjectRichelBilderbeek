#include "gamewidget.h"

#include <QBrush>
#include <QColor>
#include <QDialog>
#include <QPainter>
#include <QTimer>

GameWidget::GameWidget() : m_x(0), m_y(0)
{
  ///Create the heartbeat of the program
  QTimer * const timer = new QTimer(this);
  QObject::connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
  timer->setInterval(20);
  timer->start();
}

void GameWidget::OnTimer()
{
  ++m_x;
  ++m_y;
  this->repaint();
  if (m_x > 256) { m_x = 0; m_y = 0; }
}

void GameWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  QPixmap pixmap(":/PicBeer.png");
  painter.drawPixmap(this->rect(),pixmap);
  painter.drawPixmap(100-m_x    ,100+m_y    ,120,120,pixmap);
  painter.drawPixmap(100-m_x+100,100-m_y    ,120,120,pixmap);
  painter.drawPixmap(100+m_x    ,100+m_y+100,120,120,pixmap);
  painter.drawPixmap(100+m_x+100,100-m_y+100,120,120,pixmap);
}
