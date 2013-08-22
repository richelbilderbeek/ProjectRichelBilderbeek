#include <cassert>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "qtarrowitem.h"
#include "qtarrowswidget.h"

QtArrowsWidget::QtArrowsWidget()
{
  QGraphicsScene * const scene = new QGraphicsScene(this);
  this->setScene(scene);

  const int n_arrows = 16;
  for (int i=0; i!=n_arrows; ++i)
  {
    const double angle = 2.0 * M_PI * (static_cast<double>(i) / static_cast<double>(n_arrows));
    const double x1 =  std::sin(angle) * 100.0;
    const double y1 = -std::cos(angle) * 100.0;
    const bool tail = (std::rand() >> 4) % 2;
    const double x2 =  std::sin(angle) * 200.0;
    const double y2 = -std::cos(angle) * 200.0;
    //const double x2 = ((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 600.0) - 300.0;
    //const double y2 = ((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 400.0) - 200.0;
    const bool head = (std::rand() >> 4) % 2;

    QtArrowItem * item = new QtArrowItem(x1,y1,tail,x2,y2,head);
    scene->addItem(item);
  }
}
