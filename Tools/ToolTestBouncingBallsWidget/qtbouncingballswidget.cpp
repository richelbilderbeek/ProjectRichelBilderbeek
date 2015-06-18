#include <QTimer>
#include <QGraphicsScene>
#include "qtbouncingball.h"
#include "qtbouncingballswidget.h"


QtBouncingBallsWidget::QtBouncingBallsWidget(QWidget *parent)
  : QGraphicsView(parent),
    m_scene(new QGraphicsScene(this->rect(),this))
{
  this->setScene(m_scene);

  for (int i=0; i!=3; ++i)
  {
    QtBouncingBall * const ball = new QtBouncingBall(0,m_scene);
    ball->setPos(
      static_cast<double>((i - 1) * 32) + (0.5 * static_cast<double>(width())),
      static_cast<double>((i - 1) * 32) + (0.5 * static_cast<double>(height())));
  }

  {
    QTimer * const timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),m_scene,SLOT(advance()));
    timer->setInterval(20);
    timer->start();
  }

  //Turn off the scrollbars, as they look ugly
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


void QtBouncingBallsWidget::resizeEvent(QResizeEvent *)
{
  m_scene->setSceneRect(this->rect());
}
