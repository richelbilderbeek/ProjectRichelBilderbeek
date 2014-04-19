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
  this->setFlag(QGraphicsItem::ItemIsMovable);
  this->setFlag(QGraphicsItem::ItemIsSelectable);
}


QPainterPath QtArrowItem::shape() const
{
  //Thanks to norobro for posting this code at 
  //http://www.qtcentre.org/threads/49201-Increase-margin-for-detecting-tooltip-events-of-QGraphicsLineItem
  QPainterPath path;
  QPainterPathStroker stroker;
  path.moveTo(line().p1());
  path.lineTo(line().p2());
  stroker.setWidth(10);
  return stroker.createStroke(path);
}

QRectF QtArrowItem::boundingRect() const
{
  return shape().boundingRect();
}

void QtArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  //painter->setRenderHint(QPainter::Antialiasing);
  if (this->isSelected())
  {
    QPen thick_pen;
    thick_pen.setWidth(3);
    thick_pen.setColor(QColor(255,0,0));
    painter->setPen(thick_pen);
  }
  else
  {
    QPen pen;
    pen.setWidth(1);
    painter->setPen(pen);
  }
  painter->drawLine(this->line());

}
