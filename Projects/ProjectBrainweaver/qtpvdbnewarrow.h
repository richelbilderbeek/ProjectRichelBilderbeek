#ifndef QTPVDBNEWARROW_H
#define QTPVDBNEWARROW_H

#include <string>
#include <vector>

#include <QBrush>

#include "qtarrowitem.h"

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

///QtPvdbNewArrow is the arrow shown before a new one is added
struct QtPvdbNewArrow: public QtArrowItem
{
  QtPvdbNewArrow(
    QtPvdbNodeItem * const from,
    const QPointF& current_to);

  ///Obtain the source node
  const QtPvdbNodeItem * GetFrom() const { return m_from; }
        QtPvdbNodeItem * GetFrom()       { return m_from; }

  private:
  ///Must be suppplied
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option = 0, QWidget* widget = 0);

  ///The source node
  ///Cannot be const as the user might want to edit it
  QtPvdbNodeItem * const m_from;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBNEWARROW_H
