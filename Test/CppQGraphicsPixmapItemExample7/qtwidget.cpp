#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/lambda/bind.hpp>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

#include "qthighlighter.h"
#include "qtitem.h"
#include "qtwidget.h"
#pragma GCC diagnostic pop

QtWidget::QtWidget()
  : m_highlighter(new QtHighlighter(this))
{
  QGraphicsScene * const scene = new QGraphicsScene(this);
  this->setScene(scene);
  const int n_items = 8;
  for (int i=0; i!=n_items; ++i)
  {
    QtItem * const item = new QtItem;
    //Scatter those items around a bit
    item->setPos(
      - 128 + (std::rand() % 256),
      - 128 + (std::rand() % 256));

    scene->addItem(item);
  }

  ///Without this line, mouseMoveEvent will not be called
  this->setMouseTracking(true);
}

void QtWidget::mouseMoveEvent(QMouseEvent *event)
{
  //Rotate the first item found under the cursor
  {
    //Find the items under the cursor
    QList<QGraphicsItem *> all_items = this->scene()->items();
    std::vector<QGraphicsItem *> items; //The items under the cursor
    const QPointF pos = this->mapToScene(event->pos());

    std::for_each(all_items.begin(),all_items.end(),
      [this,&items,pos](QGraphicsItem * item)
      {
        const QRectF rect = item->boundingRect().translated(item->pos());
        if (rect.contains(pos))
        {
          items.push_back(item);
        }
      }
    );
    //Rotate the possible first item found
    if (!items.empty())
    {
      m_highlighter->SetItem(items[0]);
    }
    else
    {
      m_highlighter->SetItem(nullptr);
    }
  }

  //Let QGraphicsView handle the default mouseMoveEvents, for example
  //the moving of the items
  QGraphicsView::mouseMoveEvent(event);
}
