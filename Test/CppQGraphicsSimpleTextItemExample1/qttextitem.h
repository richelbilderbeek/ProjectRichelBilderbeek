#ifndef QTTEXTITEM_H
#define QTTEXTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsSimpleTextItem>
#pragma GCC diagnostic pop

struct QtTextItem : public QGraphicsSimpleTextItem
{
  QtTextItem(QGraphicsItem *parent = 0);
};

#endif // QTTEXTITEM_H
