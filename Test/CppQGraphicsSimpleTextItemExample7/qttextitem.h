#ifndef QTTEXTITEM_H
#define QTTEXTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <QGraphicsSimpleTextItem>
#pragma GCC diagnostic pop

struct QtTextItem : public QGraphicsSimpleTextItem
{
  QtTextItem(QGraphicsItem *parent = 0);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // QTTEXTITEM_H
