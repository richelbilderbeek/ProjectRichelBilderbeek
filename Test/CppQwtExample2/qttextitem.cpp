#include "qttextitem.h"

QtTextItem::QtTextItem(const QString& text, QGraphicsItem* parent)
  : QGraphicsSimpleTextItem(parent)
{
  this->setText(text);
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
}

void QtTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsSimpleTextItem::mouseMoveEvent(event);
  m_signal_value(this->pos().y());
}
