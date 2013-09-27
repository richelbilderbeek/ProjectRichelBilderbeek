#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsView>
#include <QTimer>
#include "qtgravitywidget.h"
#include "qtgravitywidgetitem.h"
#pragma GCC diagnostic pop

QtGravityWidget::QtGravityWidget(QWidget *parent)
  : QGraphicsView(parent),
    m_scene(new QGraphicsScene(this->rect(),this))
{
  this->setScene(m_scene);
  //Create the item
  {
    QtGravityWidgetItem * const item = new QtGravityWidgetItem(0,m_scene);
    item->setPos(static_cast<double>(width()) * 0.5,static_cast<double>(height()) * 0.5);
  }
  //Create the main QTimer
  {
    QTimer * const timer = new QTimer(this);
    timer->setInterval(20);
    QObject::connect(timer,SIGNAL(timeout()),m_scene,SLOT(advance()));
    timer->start();
  }

  //Turn off the scrollbars, as they look ugly
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


void QtGravityWidget::resizeEvent(QResizeEvent *)
{
  m_scene->setSceneRect(this->rect());
}


