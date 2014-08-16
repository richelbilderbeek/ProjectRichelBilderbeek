#ifndef QTRECTITEM_H
#define QTRECTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsRectItem>
#pragma GCC diagnostic pop

struct QtRectItem : public QGraphicsRectItem
{
  QtRectItem(QGraphicsItem *parent = 0);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // QTRECTITEM_H
