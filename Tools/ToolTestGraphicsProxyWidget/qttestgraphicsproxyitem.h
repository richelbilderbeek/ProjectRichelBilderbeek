#ifndef QTBOUNCINGBALL_H
#define QTBOUNCINGBALL_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#pragma GCC diagnostic pop
struct QGraphicsScene;

struct QtTestGraphicsProxyItem : public QGraphicsProxyWidget
{
  QtTestGraphicsProxyItem(QGraphicsItem *parent, Qt::WindowFlags wFlags);
};

#endif // QTBOUNCINGBALL_H
