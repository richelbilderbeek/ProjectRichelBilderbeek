#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "qtarrowitem.h"
#include "qtarrowswidget.h"
#pragma GCC diagnostic pop

QtArrowsWidget::QtArrowsWidget()
{
  QGraphicsScene * const scene = new QGraphicsScene(this);
  this->setScene(scene);

  const int n_lines = 10;
  for (int i=0; i!=n_lines; ++i)
  {
    const double x1 = ((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 600.0) - 300.0;
    const double y1 = ((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 400.0) - 200.0;
    const bool tail = (std::rand() >> 4) % 2;
    const double x2 = ((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 600.0) - 300.0;
    const double y2 = ((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 400.0) - 200.0;
    const bool head = (std::rand() >> 4) % 2;

    QtArrowItem * item = new QtArrowItem(x1,y1,tail,x2,y2,head);
    scene->addItem(item);
  }
}
