//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttestqtroundedrectitemwidget.h"

#include <cassert>
#include <cmath>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>
#pragma GCC diagnostic pop

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>

#include "qtroundedrectitem.h"
#pragma GCC diagnostic pop

QtTestQtRoundedRectItemWidget::QtTestQtRoundedRectItemWidget(QWidget *parent)
  : QGraphicsView(new QGraphicsScene,parent)
{
  #ifdef __STRICT_ANSI__
  const double pi = boost::math::constants::pi<double>();
  #else
  const double pi = M_PI;
  #endif

  const int n_items = 16;
  for (int i=0; i!=n_items; ++i)
  {
    const double angle = 2.0 * pi * (static_cast<double>(i) / static_cast<double>(n_items));
    {
      const double ray = 200.0;
      const double x =  std::sin(angle) * ray;
      const double y = -std::cos(angle) * ray;
      QtRoundedRectItem * const item = new QtRoundedRectItem;
      item->setPos(x,y);
      item->SetRoundedRect(QRectF(-32.0,-32.0,64.0,64.0),16.0,16.0);
      scene()->addItem(item);
    }
    {
      const double ray = 120.0;
      const double x =  std::sin(angle) * ray;
      const double y = -std::cos(angle) * ray;
      QGraphicsRectItem * const item = new QGraphicsRectItem;
      item->setFlags(
          QGraphicsItem::ItemIsFocusable
        | QGraphicsItem::ItemIsMovable
        | QGraphicsItem::ItemIsSelectable);
      item->setPos(x,y);
      item->setRect(-16.0,-16.0,32.0,32.0);
      scene()->addItem(item);
    }
  }
}
