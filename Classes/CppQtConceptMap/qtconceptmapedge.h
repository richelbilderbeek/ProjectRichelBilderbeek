//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#ifndef QTCONCEPTMAPEDGEITEM_H
#define QTCONCEPTMAPEDGEITEM_H

#define NO_QTEDGE_20140609
#ifndef NO_QTEDGE_20140609


#include <boost/shared_ptr.hpp>
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapelement.h"

#include "qtconceptmapfwd.h"

namespace ribi {
namespace cmap {

///The QtEdge is a QtConceptMapElement that
///draws a curve underneath itself, between head and tail arrowhead
///concept_item is the Strategy for displaying the ConceptItem
struct QtEdge : public QtConceptMapElement
{

  QtEdge(
    const boost::shared_ptr<Edge> edge,
    const boost::shared_ptr<QtItemDisplayStrategy> display_strategy,
    QtNode* const from,
    QtNode* const to);
  QtEdge(const QtEdge&) = delete;
  QtEdge& operator=(const QtEdge&) = delete;
  ~QtEdge() noexcept;

  QRectF boundingRect() const final;

  void DisableAll();
  void EnableAll();

  boost::shared_ptr<const QtQuadBezierArrowItem>  GetArrow() const noexcept { return m_arrow; }
  boost::shared_ptr<      QtQuadBezierArrowItem>& GetArrow()       noexcept { return m_arrow; }

  ///Get the Node at the center of the Edge
  boost::shared_ptr<const Node>  GetNode() const noexcept;
  boost::shared_ptr<      Node>  GetNode()       noexcept;

  boost::shared_ptr<const QtItemDisplayStrategy> GetDisplayStrategy() const noexcept final { return m_display_strategy; }
  boost::shared_ptr<      QtItemDisplayStrategy> GetDisplayStrategy()       noexcept final { return m_display_strategy; }

        boost::shared_ptr<const Edge>  GetEdge() const noexcept { return m_edge; }
  const boost::shared_ptr<      Edge>& GetEdge()       noexcept { return m_edge; }

  ///The node item the arrow originates from
  const QtNode * GetFrom() const noexcept { return m_from; }
        QtNode * GetFrom()       noexcept { return m_from; }

  ///Get the name of the relation
  //std::string GetName() const noexcept;

  ///The node item the arrow targets
  const QtNode * GetTo() const noexcept { return m_to; }
        QtNode * GetTo()       noexcept { return m_to; }

  void SetNode(const boost::shared_ptr<Node>& node);

  void SetFrom(QtNode * const from) noexcept; //TODO #215: Replace 'QtNode * const from' to 'boost::shared_ptr<QtNode> from'

  void SetHasHeadArrow(const bool has_head_arrow) noexcept;
  void SetHasTailArrow(const bool has_tail_arrow) noexcept;

  ///Set the name of the relation on the edge
  //void SetName(const std::string& name) noexcept;

  void SetTo(QtNode * const to) noexcept;

  ///Set the X coordinat of the central concept
  void SetX(const double x) noexcept;

  ///Set the Y coordinat of the central concept
  void SetY(const double y) noexcept;

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
  const boost::shared_ptr<QtItemDisplayStrategy> m_display_strategy;

  //const QPen m_contour_pen;
  //const QPen m_focus_pen;

  ///The edge
  const boost::shared_ptr<Edge> m_edge;

  ///The node item the arrow originates from
  QtNode * m_from;

  ///The node item the arrow targets
  QtNode * m_to;

  ///Called whenever the edge changes
  void OnFromChanged(Edge * const edge) noexcept;
  void OnHeadArrowChanged(Edge * const edge) noexcept;
  void OnNodeChanged(Edge * const edge) noexcept;
  void OnTailArrowChanged(Edge * const edge) noexcept;
  void OnToChanged(Edge * const edge) noexcept;
  //void OnXchanged(Edge * const edge) noexcept;
  //void OnYchanged(Edge * const edge) noexcept;

  ///Called whenever the arrow updates
  void OnItemHasUpdated();

  void OnRequestSceneUpdate();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif //~ NO_QTEDGE_20140609

#endif // QTCONCEPTMAPEDGEITEM_H
