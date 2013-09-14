#ifndef QTPVDBEDGEITEM_H
#define QTPVDBEDGEITEM_H

#include <boost/shared_ptr.hpp>
#include "qtpvdbeditconceptitem.h"
#include "qtpvdbconceptmapitem.h"

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

///The QtPvdbEdgeItem is a QtPvdbEditConceptItem that
///draws a bezier curve underneath itself, between head and tail arrowhead
///concept_item is the Strategy for displaying the ConceptItem
struct QtPvdbEdgeItem : public QtPvdbConceptMapItem
{

  QtPvdbEdgeItem(
    const boost::shared_ptr<ribi::pvdb::Edge> edge,
    const boost::shared_ptr<QtPvdbConceptItem> concept_item,
    QtPvdbNodeItem* const from,
    QtPvdbNodeItem* const to);
  QtPvdbEdgeItem(const QtPvdbEdgeItem&) = delete;
  QtPvdbEdgeItem& operator=(const QtPvdbEdgeItem&) = delete;

  QRectF boundingRect() const final;

  void DisableAll();
  void EnableAll();

  const boost::shared_ptr<const QtQuadBezierArrowItem>  GetArrow() const { return m_arrow; }
  const boost::shared_ptr<      QtQuadBezierArrowItem>& GetArrow()       { return m_arrow; }

  const boost::shared_ptr<const ribi::pvdb::Concept>  GetConcept() const;
  const boost::shared_ptr<      ribi::pvdb::Concept>  GetConcept()      ;

  const boost::shared_ptr<const QtPvdbConceptItem> GetConceptItem() const final { return m_concept_item; }
  const boost::shared_ptr<      QtPvdbConceptItem> GetConceptItem()       final { return m_concept_item; }

  const boost::shared_ptr<const pvdb::Edge>  GetEdge() const { return m_edge; }
  const boost::shared_ptr<      pvdb::Edge>& GetEdge()       { return m_edge; }

  ///The node item the arrow originates from
  const QtPvdbNodeItem * GetFrom() const { return m_from; }
        QtPvdbNodeItem * GetFrom()       { return m_from; }

  ///Get the name of the relation
  const std::string GetName() const;

  ///The node item the arrow targets
  const QtPvdbNodeItem * GetTo() const { return m_to; }
        QtPvdbNodeItem * GetTo()       { return m_to; }

  void SetConcept(const boost::shared_ptr<ribi::pvdb::Concept> concept);

  void SetHasHeadArrow(const bool has_head_arrow);
  void SetHasTailArrow(const bool has_tail_arrow);

  ///Set the name of the relation on the edge
  void SetName(const std::string& name);

  ///Set the X coordinat of the central concept
  void SetX(const double x);

  ///Set the Y coordinat of the central concept
  void SetY(const double y);

  ///No 'own/autonomous' signals, these are present in the ConceptItems

protected:
  void focusInEvent(QFocusEvent *event) final;
  void focusOutEvent(QFocusEvent *event) final;
  void keyPressEvent(QKeyEvent *event) final;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) final;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) final;
  QPainterPath shape() const final;

private:
  ///The arrow used for drawing
  ///Not 'const boost::shared_ptr<QtQuadBezierArrowItem> m_arrow;',
  ///because in the initialization
  ///m_edge must be initialized before m_arrow
  boost::shared_ptr<QtQuadBezierArrowItem> m_arrow;

  ///The Strategy for displaying the Concept
  const boost::shared_ptr<QtPvdbConceptItem> m_concept_item;

  const QPen m_contour_pen;
  const QPen m_focus_pen;

  ///The edge
  const boost::shared_ptr<ribi::pvdb::Edge> m_edge;

  ///The node item the arrow originates from
  QtPvdbNodeItem * const m_from;

  ///The node item the arrow targets
  QtPvdbNodeItem * const m_to;

  ///Called whenever the edge changes
  void OnEdgeChanged(const pvdb::Edge * const edge);

  ///Called whenever the arrow updates
  void OnItemHasUpdated();

  void OnRequestSceneUpdate();

  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBEDGEITEM_H
