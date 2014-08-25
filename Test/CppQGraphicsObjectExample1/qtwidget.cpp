#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/bind.hpp>
#include <boost/lambda/bind.hpp>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "qtitem.h"
#include "qtwidget.h"
#pragma GCC diagnostic pop

QtWidget::QtWidget()
{
  QGraphicsScene * const scene = new QGraphicsScene(this);
  this->setScene(scene);

  const int n_items = 64;
  for (int i=0; i!=n_items; ++i)
  {
    QtItem * const item = new QtItem;
    item->m_clicked_signal.connect(
      boost::bind(
        &QtWidget::OnItemClick,this, boost::lambda::_1));
    //Scatter those items around a bit
    item->setPos(
      - 128 + (std::rand() % 256),
      - 128 + (std::rand() % 256));

    scene->addItem(item);
  }
}

void QtWidget::OnItemClick(QtItem * const item)
{
  item->setRotation( item->rotation() + 15.0);
}
