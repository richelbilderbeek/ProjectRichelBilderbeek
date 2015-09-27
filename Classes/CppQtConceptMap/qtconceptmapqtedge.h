//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

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
//#include "qtconceptmapqtedge.h"

#pragma GCC diagnostic pop

namespace ribi {

struct QtRoundedRectItem;

namespace cmap {

///The QtEdge is a QtConceptMapElement that
///draws a curve underneath itself, between head and tail arrowhead
///concept_item is the Strategy for displaying the ConceptItem
//struct QtEdge : public QtConceptMapElement
struct QtEdge : public QGraphicsItem
{
  using Base = QGraphicsItem;

  using Arrow = boost::shared_ptr<QtQuadBezierArrowItem>;
  using ReadOnlyArrow = boost::shared_ptr<const QtQuadBezierArrowItem> ;
  using NodePtr = boost::shared_ptr<Node>;
  using ReadOnlyNodePtr = boost::shared_ptr<const Node>;
  using QtNodePtr =  QtNode *;
  using ReadOnlyQtNodePtr = const QtNode *;
  using EdgePtr = boost::shared_ptr<Edge>;
  using ReadOnlyEdgePtr = boost::shared_ptr<const Edge>;

  using From = QtNodePtr;
  using ReadOnlyFrom = ReadOnlyQtNodePtr;
  using To = QtNodePtr;
  using ReadOnlyTo = ReadOnlyQtNodePtr;

  QtEdge(
    const EdgePtr& edge,
    const From& from,
    const To& to
  );
  QtEdge(const QtEdge&) = delete;
  QtEdge& operator=(const QtEdge&) = delete;
  ~QtEdge() noexcept;

  QRectF boundingRect() const override final;

  void DisableAll() noexcept;
  void EnableAll() noexcept;

  ReadOnlyArrow GetArrow() const noexcept { return m_arrow; }
  const Arrow& GetArrow() noexcept { return m_arrow; }

  ReadOnlyEdgePtr GetEdge() const noexcept { return m_edge; }
  EdgePtr GetEdge() noexcept { return m_edge; }

  ///The node item the arrow originates from
  ReadOnlyFrom GetFrom() const noexcept { return m_from; }
  From GetFrom() noexcept { return m_from; }

  ///The node item the arrow targets
  ReadOnlyTo GetTo() const noexcept { return m_to; }
  To GetTo() noexcept { return m_to; }

  boost::shared_ptr<      QtNode> GetQtNode()       noexcept { return m_qtnode; }
  boost::shared_ptr<const QtNode> GetQtNode() const noexcept { return m_qtnode; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  bool isSelected() const;

  void SetEdge(const EdgePtr& edge) noexcept;

  void SetFrom(const From& from) noexcept;

  void SetHasHeadArrow(const bool has_head_arrow) noexcept;
  void SetHasTailArrow(const bool has_tail_arrow) noexcept;

  void SetSelected(bool selected);

  void SetShowBoundingRect(const bool show_bounding_rect) const noexcept { m_show_bounding_rect = show_bounding_rect; }

  void SetTo(const To& to) noexcept;

  std::string ToStr() const noexcept;

  mutable boost::signals2::signal<void (QtEdge *)> m_signal_base_changed;
  mutable boost::signals2::signal<void (QtEdge *)> m_signal_edge_changed;
  mutable boost::signals2::signal<void (QtEdge *)> m_signal_selected_changed;
  mutable boost::signals2::signal<void (QtEdge *,const int key)> m_signal_key_down_pressed;

protected:
  /*
  void dragEnterEvent(QGraphicsSceneDragDropEvent *) noexcept override final;
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) noexcept override final;
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event) noexcept override final;
  */
  void focusInEvent(QFocusEvent *event) noexcept override final;
  void focusOutEvent(QFocusEvent *event) noexcept override final;
  /*
  void hoverMoveEvent(QGraphicsSceneHoverEvent *event) noexcept override final;
  */
  void keyPressEvent(QKeyEvent *event) noexcept override final;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) noexcept override final;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) noexcept override final;
  QPainterPath shape() const noexcept override final;

private:
  ///The arrow used for drawing
  Arrow m_arrow;

  ///The edge
  boost::shared_ptr<Edge> m_edge;

  ///The node item the arrow originates from
  From m_from;

  ///The QtNode around Edge its Node
  const boost::shared_ptr<QtNode> m_qtnode;

  ///Show the bounding rectangle
  mutable bool m_show_bounding_rect;

  ///The node item the arrow targets
  To m_to;

  ///Called whenever the edge changes
  void OnEdgeChanged(Edge * const edge) noexcept;
  void OnConceptChanged(Node * const node) noexcept;
  void OnFromChanged(Edge * const edge) noexcept;
  void OnHeadArrowChanged(Edge * const edge) noexcept;
  void OnNodeChanged(Edge * const edge) noexcept;
  void OnNodePosChanged(QtRoundedRectItem * const node) noexcept;
  void OnTailArrowChanged(Edge * const edge) noexcept;
  void OnTextChanged(QtRoundedEditRectItem* item) noexcept;
  void OnToChanged(Edge * const edge) noexcept;

  ///Called whenever the arrow updates
  void OnArrowChanged(const QtQuadBezierArrowItem* const item);

  void OnMustUpdateScene();
  void OnRequestSceneUpdate();

  void setSelected(bool selected) = delete;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const QtEdge& qtedge) noexcept;

bool operator==(const QtEdge& lhs, const QtEdge& rhs) noexcept;

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPEDGEITEM_H
