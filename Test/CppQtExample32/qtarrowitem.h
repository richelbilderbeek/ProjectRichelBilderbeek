#ifndef QTARROWITEM_H
#define QTARROWITEM_H

#include <QGraphicsLineItem>

struct QtArrowItem : public QGraphicsLineItem
{
  QtArrowItem(
    const double x1,
    const double y1,
    const bool tail,
    const double x2,
    const double y2,
    const bool head,
    QGraphicsItem *parent = 0);

  protected:
  ///Paint a QtTextPositionItem
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

  ///The rectangle that containg the item, used for rough calculations like
  ///collision detection
  QRectF boundingRect() const;

  ///More precise shape compared to boundingRect
  ///In this example, it is redefined to ease selecting those thin lines
  QPainterPath shape() const;

  ///Show arrow at head
  const bool m_head;

  ///Show arrow at tail
  const bool m_tail;

};

#endif // QTARROWITEM_H
