#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QCursor>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "qtarrowitem.h"
#pragma GCC diagnostic pop

QtArrowItem::QtArrowItem(
  const double x1,
  const double y1,
  const bool tail,
  const double x2,
  const double y2,
  const bool head,
  QGraphicsItem *parent)
  : QGraphicsLineItem(x1,y1,x2,y2,parent),
    m_head(head),
    m_tail(tail)
{
  this->setFlags(QGraphicsItem::ItemIsMovable);
}

QRectF QtArrowItem::boundingRect() const
{
  return QRectF(this->line().p1(),this->line().p2());
}

void QtArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->drawLine(this->line());
}
