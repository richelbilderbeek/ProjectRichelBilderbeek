#include "qttextitem.h"

#include <cassert>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <QGraphicsScene>
#pragma GCC diagnostic pop

QtTextItem::QtTextItem(QGraphicsItem *parent)
 : QGraphicsSimpleTextItem(parent)
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

}

void QtTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  std::stringstream s;
  s << "(" << static_cast<int>(this->pos().x()) << "," << static_cast<int>(this->pos().y()) << ")";
  this->setText(s.str().c_str());
  QGraphicsSimpleTextItem::paint(painter,option,widget);
}
