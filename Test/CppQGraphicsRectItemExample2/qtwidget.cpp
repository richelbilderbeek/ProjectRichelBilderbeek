#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtwidget.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include "qtrectitem.h"
#pragma GCC diagnostic pop

QtWidget::QtWidget(QWidget *parent)
  : QGraphicsView(new QGraphicsScene,parent)
{
  const int n_items = 16;
  for (int i=0; i!=n_items; ++i)
  {
    const double angle = 2.0 * M_PI * (static_cast<double>(i) / static_cast<double>(n_items));
    const double ray = 150.0;
    const double x =  std::sin(angle) * ray;
    const double y = -std::cos(angle) * ray;

    QtRectItem * const item = new QtRectItem;
    item->setPos(x,y);
    scene()->addItem(item);
  }
}
