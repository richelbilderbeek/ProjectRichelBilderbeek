#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtwidget.h"
#include <QGraphicsScene>
#include "qtrectitem.h"
#pragma GCC diagnostic pop

QtWidget::QtWidget(QWidget *parent)
  : QGraphicsView(new QGraphicsScene,parent)
{
  const int n_items = 20;
  for (int i=0; i!=n_items; ++i)
  {
    const double x = static_cast<double>(i % 2) * 200.0;
    const double y = static_cast<double>(i / 2) * 40;
    QPen pen;
    pen.setWidth(i);
    QtRectItem * const item = new QtRectItem;
    item->setPos(x,y);
    item->setPen(pen);
    scene()->addItem(item);
  }
}
