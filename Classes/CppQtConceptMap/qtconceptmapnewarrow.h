#ifndef QTCONCEPTMAPNEWARROW_H
#define QTCONCEPTMAPNEWARROW_H

#include <string>
#include <vector>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QBrush>
#include "qtarrowitem.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///QtNewArrow is the arrow shown before a new one is added
struct QtNewArrow : public QtArrowItem
{
  QtNewArrow(
    QtNode * const from,
    const QPointF& current_to);
  QtNewArrow(const QtNewArrow&) = delete;
  QtNewArrow& operator=(const QtNewArrow&) = delete;
  ///Obtain the source node
  const QtNode * GetFrom() const { return m_from; }
        QtNode * GetFrom()       { return m_from; }

  private:
  ///Must be suppplied
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option = 0, QWidget* widget = 0);

  ///The source node
  ///Cannot be const as the user might want to edit it
  QtNode * const m_from;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPNEWARROW_H
