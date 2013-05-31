#include <cassert>
#include <QTimer>
#include <QGraphicsScene>
#include "qttestgraphicsproxyitem.h"
#include "qttestgraphicsproxywidget.h"
#include "somedialog.h"


QtTestGraphicsProxyWidget::QtTestGraphicsProxyWidget(QWidget *parent)
  : QGraphicsView(parent),
    m_scene(new QGraphicsScene(this->rect(),this))
{
  this->setScene(m_scene);

  for (int i=0; i!=3; ++i)
  {
    //QtTestGraphicsProxyItem * const item = new QtTestGraphicsProxyItem(0,0);
    //item->setWidget(new SomeDialog);
    //m_scene->addItem(item);
    SomeDialog * const dialog = new SomeDialog; //Adding 'this' as parent results in an error!
    //m_dialogs.push_back(dialog);
    QGraphicsProxyWidget * const proxy = new QGraphicsProxyWidget(0,Qt::Window);
    proxy->setWidget(dialog);

    //MUST DO THIS?
    proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    //m_scene->addWidget(dialog);
    m_scene->addItem(proxy);
    assert(proxy);
    proxy->setPos((i+1) * 100, (i+1)* 100);
    proxy->rotate((i+1) * 10.0);
    //m_proxies.push_back(proxy);


    //item->setPos(
    //  static_cast<double>((i - 1) * 32) + (0.5 * static_cast<double>(width())),
    //  static_cast<double>((i - 1) * 32) + (0.5 * static_cast<double>(height())));
  }

  //{
  //  QTimer * const timer = new QTimer(this);
  //  QObject::connect(timer,SIGNAL(timeout()),m_scene,SLOT(advance()));
  //  timer->setInterval(20);
  //  timer->start();
  //}

  //Turn off the scrollbars, as they look ugly
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


void QtTestGraphicsProxyWidget::resizeEvent(QResizeEvent *)
{
  m_scene->setSceneRect(this->rect());
}
