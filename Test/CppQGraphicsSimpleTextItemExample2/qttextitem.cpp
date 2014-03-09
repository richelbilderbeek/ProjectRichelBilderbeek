#include "qttextitem.h"

#include <sstream>

QtTextItem::QtTextItem(QGraphicsItem *parent)
 : QGraphicsSimpleTextItem(parent)
{
  this->setFlags(
      QGraphicsItem::ItemIsSelectable
    | QGraphicsItem::ItemIsMovable);

}

void QtTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  std::stringstream s;
  s << "(" << static_cast<int>(this->pos().x()) << "," << static_cast<int>(this->pos().y()) << ")";
  this->setText(s.str().c_str());
  QGraphicsSimpleTextItem::paint(painter,option,widget);
}
