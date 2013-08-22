#ifndef QTTEXTPOSITIONITEM_H
#define QTTEXTPOSITIONITEM_H

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
    QGraphicsItem *parent = 0,
    QGraphicsScene *scene = 0);

  protected:
  ///Paint a QtTextPositionItem
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

  ///The rectangle that determines the edges of the item
  QRectF boundingRect() const;

  ///Show arrow at head
  const bool m_head;

  ///Show arrow at tail
  const bool m_tail;

};

#endif // QTTEXTPOSITIONITEM_H
