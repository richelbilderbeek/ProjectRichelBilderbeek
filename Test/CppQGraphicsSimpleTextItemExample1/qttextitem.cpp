#include "qttextitem.h"

QtTextItem::QtTextItem(QGraphicsItem *parent)
 : QGraphicsSimpleTextItem(parent)
{
  this->setFlags(
      QGraphicsItem::ItemIsSelectable
    | QGraphicsItem::ItemIsMovable);

  this->setText("Hello World");
}
