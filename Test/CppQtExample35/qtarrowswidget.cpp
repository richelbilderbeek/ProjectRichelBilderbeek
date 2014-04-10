#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "qtarrowitem.h"
#include "qtarrowswidget.h"
#pragma GCC diagnostic pop

QtArrowsWidget::QtArrowsWidget()
  : m_scene(new QGraphicsScene(this))
{

  this->setScene(m_scene);
  const int n_arrows = 16;
  for (int i=0; i!=n_arrows; ++i)
  {
    const double angle = 2.0 * boost::math::constants::pi<double>() * (static_cast<double>(i) / static_cast<double>(n_arrows));
    const double d_angle = (2.0 * boost::math::constants::pi<double>()) / 32.0;
    const double tail_x =  std::sin(angle) * 100.0;
    const double tail_y = -std::cos(angle) * 100.0;
    const bool tail = (std::rand() >> 4) % 2;

    const double mid_x =  std::sin(angle + d_angle) * 150.0;
    const double mid_y = -std::cos(angle + d_angle) * 150.0;

    const double head_x =  std::sin(angle) * 200.0;
    const double head_y = -std::cos(angle) * 200.0;
    const bool head = (std::rand() >> 4) % 2;

    QtArrowItem * item = new QtArrowItem(tail_x,tail_y,tail,mid_x,mid_y,head,head_x,head_y);
    m_scene->addItem(item);
  }
}

void QtArrowsWidget::keyPressEvent(QKeyEvent *event)
{
  const QList<QGraphicsItem *> v = m_scene->selectedItems();
  std::for_each(v.begin(),v.end(),
    [event](QGraphicsItem * item)
    {
      if (QtArrowItem * const arrow = dynamic_cast<QtArrowItem*>(item))
      {
        arrow->keyPressEvent(event);
      }
    }
  );
}
