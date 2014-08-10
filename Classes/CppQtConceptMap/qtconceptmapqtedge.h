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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <QGraphicsItem>
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///The QtEdge is a QtConceptMapElement that
///draws a curve underneath itself, between head and tail arrowhead
///concept_item is the Strategy for displaying the ConceptItem
//struct QtEdge : public QtConceptMapElement
struct QtEdge : public QGraphicsItem
{
  typedef QGraphicsItem Base;

  typedef boost::shared_ptr<QtQuadBezierArrowItem> Arrow;
  typedef boost::shared_ptr<const QtQuadBezierArrowItem> ReadOnlyArrow;
  typedef boost::shared_ptr<Node> NodePtr;
  typedef boost::shared_ptr<const Node> ReadOnlyNodePtr;
  typedef boost::shared_ptr<QtNode> QtNodePtr;
  typedef boost::shared_ptr<const QtNode> ReadOnlyQtNodePtr;
  typedef boost::shared_ptr<Edge> EdgePtr;
  typedef boost::shared_ptr<const Edge> ReadOnlyEdgePtr;

  QtEdge(
    const EdgePtr& edge,
    QtNode* const from,
    QtNode* const to
  );
  QtEdge(const QtEdge&) = delete;
  QtEdge& operator=(const QtEdge&) = delete;
  ~QtEdge() noexcept;

  QRectF boundingRect() const override final;

  void DisableAll() noexcept;
  void EnableAll() noexcept;

  ReadOnlyArrow GetArrow() const noexcept { return m_arrow; }
  const Arrow& GetArrow() noexcept { return m_arrow; }

  ///Get the Node at the center of the Edge
  //TODO: Remove, use GetQtNode stead
  //ReadOnlyNodePtr GetNode() const noexcept;
  //NodePtr GetNode() noexcept;

  ReadOnlyEdgePtr GetEdge() const noexcept { return m_edge; }
  EdgePtr GetEdge() noexcept { return m_edge; }

  ///The node item the arrow originates from
  const QtNode * GetFrom() const noexcept { return m_from; }
        QtNode * GetFrom()       noexcept { return m_from; }

  ///The node item the arrow targets
  const QtNode * GetTo() const noexcept { return m_to; }
        QtNode * GetTo()       noexcept { return m_to; }

  boost::shared_ptr<      QtNode> GetQtNode()       noexcept { return m_qtnode; }
  boost::shared_ptr<const QtNode> GetQtNode() const noexcept { return m_qtnode; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  void SetEdge(const EdgePtr& edge) noexcept;

  void SetFrom(QtNode * const from) noexcept; //TODO #215: Replace 'QtNode * const from' to 'boost::shared_ptr<QtNode> from'

  void SetHasHeadArrow(const bool has_head_arrow) noexcept;
  void SetHasTailArrow(const bool has_tail_arrow) noexcept;

  void SetTo(QtNode * const to) noexcept;

  std::string ToStr() const noexcept;

  mutable boost::signals2::signal<void (QtEdge *)> m_signal_base_changed;
  mutable boost::signals2::signal<void (QtEdge *)> m_signal_edge_changed;

protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) noexcept override final;
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) noexcept override final;
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event) noexcept override final;
  void focusInEvent(QFocusEvent *event) noexcept override final;
  void focusOutEvent(QFocusEvent *event) noexcept override final;
  void keyPressEvent(QKeyEvent *event) noexcept override final;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) noexcept override final;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) noexcept override final;
  QPainterPath shape() const noexcept override final;

private:
  ///The arrow used for drawing
  const Arrow m_arrow;

  ///The edge
  boost::shared_ptr<Edge> m_edge;

  ///The node item the arrow originates from
  QtNode * m_from;

  ///The QtNode around Edge its Node
  const boost::shared_ptr<QtNode> m_qtnode;

  ///The node item the arrow targets
  QtNode * m_to;

  /*
  double GetX() const noexcept { return Base::GetX(); }
  double GetY() const noexcept { return Base::GetY(); }
  QPointF GetPos() const noexcept { return Base::GetPos(); }
  void SetPos(const double x,const double y) noexcept { Base::SetPos(x,y); }
  void SetX(const double x) noexcept { Base::SetX(x); }
  void SetY(const double y) noexcept { Base::SetY(y); }
  void SetText(const std::vector<std::string>& text) noexcept { Base::SetText(text); }
  */
  ///Called whenever the edge changes
  void OnEdgeChanged(Edge * const edge) noexcept;
  void OnConceptChanged(Node * const node) noexcept;
  void OnFromChanged(Edge * const edge) noexcept;
  void OnHeadArrowChanged(Edge * const edge) noexcept;
  void OnNodeChanged(Edge * const edge) noexcept;
  void OnTailArrowChanged(Edge * const edge) noexcept;
  void OnTextChanged(QtRoundedEditRectItem* item) noexcept;
  void OnToChanged(Edge * const edge) noexcept;

  //void OnXchanged(Edge * const edge) noexcept;
  //void OnYchanged(Edge * const edge) noexcept;

  ///Called whenever the arrow updates
  void OnArrowChanged(const QtQuadBezierArrowItem* const item);

  void OnMustUpdateScene();
  void OnRequestSceneUpdate();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const QtEdge& qtedge) noexcept;

bool operator==(const QtEdge& lhs, const QtEdge& rhs) noexcept;

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPEDGEITEM_H
