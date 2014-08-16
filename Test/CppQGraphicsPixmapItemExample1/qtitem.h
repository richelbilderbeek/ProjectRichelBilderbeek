#ifndef QTITEM_H
#define QTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsPixmapItem>
#pragma GCC diagnostic pop

///A QGraphicsPixmapItem that loads its pixmap from resources
struct QtItem : public QGraphicsPixmapItem
{
  QtItem(QGraphicsItem *parent = 0);
};

#endif // QTITEM_H
