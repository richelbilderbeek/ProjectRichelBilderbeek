#ifndef QTWIDGET_H
#define QTWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsView>
#pragma GCC diagnostic pop

///Forward declaration
struct QtItem;

struct QtWidget : public QGraphicsView
{
  QtWidget();

  ///Respond to a click on a QtItem
  void OnItemMoveOver(QtItem * const item);
};

#endif // QTWIDGET_H
