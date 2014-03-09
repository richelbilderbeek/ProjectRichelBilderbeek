#include "qtwidget.h"

#include <cassert>
#include <cmath>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsScene>
#include "qttextitem.h"
#pragma GCC diagnostic pop

QtWidget::QtWidget(QWidget *parent)
  : QGraphicsView(new QGraphicsScene,parent)
{
  const int n_items = 16;
  for (int i=0; i!=n_items; ++i)
  {
    const double angle = 2.0 * M_PI * (static_cast<double>(i+0) / static_cast<double>(n_items));
    const double ray = 150.0;
    const double x =  std::sin(angle) * ray;
    const double y = -std::cos(angle) * ray;

    QtTextItem * const item = new QtTextItem;
    item->setPos(x,y);
    scene()->addItem(item);
  }
}
