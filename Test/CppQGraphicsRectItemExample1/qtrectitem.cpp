#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtrectitem.h"

#include <cassert>
#include <sstream>
#include <QGraphicsScene>
#include <QPainter>
#pragma GCC diagnostic pop

QtRectItem::QtRectItem(QGraphicsItem *parent)
 : QGraphicsRectItem(parent)
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  const double width  = 64.0; //pixels
  const double height = 32.0; //pixels
  this->setRect(-0.5 * width, -0.5 * height, width, height);
}
