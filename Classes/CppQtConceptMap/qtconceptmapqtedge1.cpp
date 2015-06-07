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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapqtedge1.h"

#include <cassert>

#include <boost/lambda/lambda.hpp>

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPainter>

#include "conceptmapconcept.h"
#include "conceptmapedge.h"
#include "conceptmapnode.h"
#include "container.h"
#include "qtconceptmapqtnode.h"
#include "qtquadbezierarrowitem.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtEdge1::QtEdge1(
    const EdgePtr& edge,
    const From& from,
    const To& to
)
  : m_signal_base_changed{},
    m_signal_edge_changed{},
    m_signal_focus_in_event{},
    m_signal_key_down_pressed{},
    //m_arrow{new QtQuadBezierArrowItem(from,edge->HasTailArrow(),this,edge->HasHeadArrow(),to)},
    m_arrow{nullptr}, //Will be initialized below
    m_edge{}, //Will be initialized by setEdge
    m_from{from},
    m_qtnode{new QtNode(edge->GetNode())},
    m_to{to}
{
  #ifndef NDEBUG
  Test();
  #endif

  //Allow mouse tracking
  //OTOH: must be done by the other thing
  //this->setAcceptHoverEvents(true);

  //const_cast because Arrow constant
  //I just need to have an initialized m_qtnode
  const_cast<Arrow&>(m_arrow).reset(
    new QtQuadBezierArrowItem(
    from,edge->HasTailArrow(),
    this->GetQtNode().get(),
    edge->HasHeadArrow(),
    to
    )
  );

  //QtEdge is just the glue between a collection of things
  /*
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable
  );
  */

  GetQtNode()->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable
  );

  GetFrom()->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable
  );

  GetTo()->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable
  );

  assert(m_from);
  assert(m_to);
  assert(from != to);
  assert(m_from != m_to);
  //m_edge must be initialized before m_arrow
  //if 'from' or 'to' are CenterNodes, then no item must be put at the center
  //const bool is_connected_to_center_node
  //  = dynamic_cast<QtCenterNode*>(from) || dynamic_cast<QtCenterNode*>(to);
  //if (is_connected_to_center_node)
  //{
  //m_arrow.reset(new QtQuadBezierArrowItem(from,edge->HasTailArrow(),this,edge->HasHeadArrow(),to));
  //}
  //else
  //{
  //  m_arrow.reset(new QtQuadBezierArrowItem(from,edge->HasTailArrow(),this,edge->HasHeadArrow(),to));
  //}
  assert(m_arrow);




  m_arrow->m_signal_item_updated.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnArrowChanged,this,boost::lambda::_1)
  );

  m_qtnode->m_signal_pos_changed.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnNodePosChanged,this,boost::lambda::_1)
  );

  //TODO: Is this a redundant connection? (i.e. a subset of what m_signal_node_changed covers)
  m_qtnode->m_signal_text_changed.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnTextChanged,this,boost::lambda::_1)
  );



  m_from->m_signal_node_changed.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnMustUpdateScene,this)
  );
  m_to->m_signal_node_changed.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnMustUpdateScene,this)
  );

  SetEdge(edge);


  #ifdef TODO_ISSUE_212
  if (!is_connected_to_center_node)
  {
    //Only allow edges not connected to the center node to be edited
    assert(display_strategy);
    QtEditStrategy * const edit_concept = dynamic_cast<QtEditStrategy*>(display_strategy.get());
    if (edit_concept)
    {
      edit_concept->m_signal_request_edit.connect(
        boost::bind(
          &QtConceptMapElement::OnConceptRequestsEdit,
          this
        )
      );
    }
  }
  #else
  //if (QtEditStrategy * edit_concept = dynamic_cast<QtEditStrategy*>(display_strategy.get()))
  //{
  //  edit_concept->m_signal_request_edit.connect(
  //    boost::bind(
  //      &QtConceptMapElement::OnConceptRequestsEdit,
  //      this
  //    )
  //  );
  //}
  #endif

}

ribi::cmap::QtEdge1::~QtEdge1() noexcept
{
  m_arrow->m_signal_item_updated.disconnect(
    boost::bind(&ribi::cmap::QtEdge1::OnArrowChanged,this,boost::lambda::_1)
  );
  m_qtnode->m_signal_text_changed.disconnect(
    boost::bind(&ribi::cmap::QtEdge1::OnTextChanged,this,boost::lambda::_1)
  );

  SetEdge(nullptr);

  //assert(m_from);
  //assert(m_from->m_signal_node_changed.num_slots() > 0);

  //m_from->m_signal_node_changed.disconnect(
  //  boost::bind(&ribi::cmap::QtEdge1::OnMustUpdateScene,this)
  //);
  //assert(m_to);
  //m_to->m_signal_node_changed.disconnect(
  //  boost::bind(&ribi::cmap::QtEdge1::OnMustUpdateScene,this)
  //);


  //Disconnect signals
  /*
  #ifdef TODO_ISSUE_212
  if (!is_connected_to_center_node)
  {
    //Only allow edges not connected to the center node to be edited
    assert(m_display_strategy);
    QtEditStrategy * const edit_concept = dynamic_cast<QtEditStrategy*>(m_display_strategy.get());
    if (edit_concept)
    {
      edit_concept->m_signal_request_edit.disconnect(
        boost::bind(&QtConceptMapElement::OnConceptRequestsEdit,this)
      );
    }
  }
  #else
  if (QtEditStrategy * edit_concept = dynamic_cast<QtEditStrategy*>(display_strategy.get()))
  {
    edit_concept->m_signal_request_edit.disconnect(
      boost::bind(
        &QtConceptMapElement::OnConceptRequestsEdit,
        this
      )
    );
  }
  #endif
  */
}

QRectF ribi::cmap::QtEdge1::boundingRect() const
{


  return m_qtnode->boundingRect().translated(m_qtnode->GetCenterPos())
    .united(m_arrow->boundingRect())
  ;

  //Don't forget to update ::shape if you change ::boundingRect!

  //Some other candidates

  //return m_qtnode->boundingRect()
  //  .united(m_arrow->boundingRect());

  //return m_qtnode->boundingRect().translated(-m_qtnode->GetCenterPos())
  //   .united(m_arrow->boundingRect());

  //return m_qtnode->boundingRect()
  //  .united(m_arrow->boundingRect().translated(m_qtnode->GetCenterPos()));
}

void ribi::cmap::QtEdge1::DisableAll() noexcept
{
  this->setEnabled(false);
  this->setVisible(false);
  this->m_arrow->setEnabled(false);
  this->m_arrow->setVisible(false);
}

void ribi::cmap::QtEdge1::EnableAll() noexcept
{
  this->setEnabled(true);
  this->setVisible(true);
  this->m_arrow->setEnabled(true);
  this->m_arrow->setVisible(true);
}

/*
boost::shared_ptr<const ribi::cmap::Node> ribi::cmap::QtEdge1::GetNode() const noexcept
{
  const auto p = m_edge->GetNode();
  assert(p);
  return p;
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::QtEdge1::GetNode() noexcept
{
  const auto p = m_edge->GetNode();
  assert(p);
  return p;
}
*/
std::string ribi::cmap::QtEdge1::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::cmap::QtEdge1::GetVersionHistory() noexcept
{
  return {
    "201x-xx-xx: version 1.0: initial version"
    "2014-08-01: version 1.1: start of versioning"
  };
}

/*
void ribi::cmap::QtEdge1::dragEnterEvent(QGraphicsSceneDragDropEvent *) noexcept
{
  TRACE_FUNC();
  update();
}

void ribi::cmap::QtEdge1::dragLeaveEvent(QGraphicsSceneDragDropEvent *) noexcept
{
  TRACE_FUNC();
  update();
}

void ribi::cmap::QtEdge1::dragMoveEvent(QGraphicsSceneDragDropEvent *) noexcept
{
  TRACE_FUNC();
  //if (scene()) { scene()->update(); }
  update();
}
*/

void ribi::cmap::QtEdge1::focusInEvent(QFocusEvent*) noexcept
{
  m_signal_focus_in_event(this);
  //Lose focus of arrow
  //m_arrow->SetPen(QPen(QColor(0,0,0)));
  //m_display_strategy->SetContourPen(m_display_strategy->GetFocusPen()); //Updates itself
}
/*
void ribi::cmap::QtEdge1::focusOutEvent(QFocusEvent*) noexcept
{
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  //m_display_strategy->SetContourPen(m_display_strategy->GetContourPen()); //Updates itself
}
*/

/*
void ribi::cmap::QtEdge1::hoverMoveEvent(QGraphicsSceneHoverEvent*) noexcept
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}
*/

void ribi::cmap::QtEdge1::keyPressEvent(QKeyEvent *event) noexcept
{
  assert(m_arrow);
  assert(m_edge);
  m_signal_key_down_pressed(this,event->key());
  /*
  if (m_arrow->isEnabled())
  {
    m_arrow->keyPressEvent(event);
    m_edge->SetHeadArrow( m_arrow->HasHead() );
    m_edge->SetTailArrow( m_arrow->HasTail() );

    assert(m_edge->HasHeadArrow() == m_arrow->HasHead());
    assert(m_edge->HasTailArrow() == m_arrow->HasTail());
  }
  */
  QGraphicsItem::keyPressEvent(event);
}

void ribi::cmap::QtEdge1::mousePressEvent(QGraphicsSceneMouseEvent *event) noexcept
{  
  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );
  if (event->modifiers() & Qt::ShiftModifier)
  {
    if ((event->pos() - this->m_arrow->GetTail() + m_qtnode->GetCenterPos()).manhattanLength() < 20.0)
    {
      this->SetHasTailArrow( !m_arrow->HasTail() ); //FIX 2013-02-10
      //this->m_arrow->SetHasTail( !m_arrow->HasTail() ); //BUG 2013-02-10
      //this->update(); //Don't!
      //m_signal_item_updated(this); //Don't!
    }
    else if ((event->pos() - this->m_arrow->GetHead() + m_qtnode->GetCenterPos()).manhattanLength() < 20.0)
    {
      this->SetHasHeadArrow( !m_arrow->HasHead() );
      //this->update(); //Don't!
      //m_signal_item_updated(this); //Don't!
    }
  }

  //What is clicked on: the concept or the arrow? Assume concept
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  if (!m_qtnode->GetInnerRect().contains(event->pos()))
  {
    //If the concept is not clicked...
    //but the arrow is...
    QPointF pos_on_arrow = event->pos();
    pos_on_arrow += (m_qtnode->GetCenterPos());
    if (m_arrow->shape().contains(pos_on_arrow)
      || (event->pos() - this->m_arrow->GetTail() + m_qtnode->GetCenterPos()).manhattanLength() < 20.0
      || (event->pos() - this->m_arrow->GetHead() + m_qtnode->GetCenterPos()).manhattanLength() < 20.0
      )
    {
      //give focus to the arrow
      m_arrow->SetPen(m_arrow->GetFocusPen());
      return;
    }
  }
  //QtConceptMapElement::mousePressEvent(event);
}

void ribi::cmap::QtEdge1::OnConceptChanged(Node * const node) noexcept
{
  //Node changed, sync QtRoundedRectItem
  assert(node);
  assert(node == m_edge->GetNode().get());
  const std::string new_str{node->GetConcept()->GetName()};
  const std::vector<std::string> new_text{new_str};
  assert(new_text.size() == 1);
  m_qtnode->SetText(new_text);
  assert(m_qtnode->GetText() == new_text);
}

void ribi::cmap::QtEdge1::OnEdgeChanged(Edge * const edge) noexcept
{
  OnFromChanged(edge);
  OnNodeChanged(edge);
  OnHeadArrowChanged(edge);
  OnTailArrowChanged(edge);
  OnToChanged(edge);
}


void ribi::cmap::QtEdge1::OnFromChanged(Edge * const edge) noexcept
{
  this->GetFrom()->SetNode(edge->GetFrom());
  assert(edge->GetFrom() == this->GetFrom()->GetNode());
  m_signal_edge_changed(this);
  this->update(); //Obligatory: when the 'source/from' QtNode moves, this update causes the QtEdge keep pointing to
  //if (this->scene()) { this->scene()->update(); } // Not needed
}

void ribi::cmap::QtEdge1::OnHeadArrowChanged(Edge * const edge) noexcept
{
  SetHasHeadArrow(edge->HasHeadArrow());
  this->update(); //Obligatory
  m_signal_edge_changed(this);
}

/*
void ribi::cmap::QtEdge1::OnNodeChanged(QtNode * const node) noexcept
{
  m_qtnode->SetCenterX(edge->GetNode()->GetX());
  m_qtnode->SetCenterY(edge->GetNode()->GetY());
  m_qtnode->SetText( { edge->GetNode()->GetConcept()->GetName() } );
  this->update();
  m_signal_edge_changed(this);
}
*/

void ribi::cmap::QtEdge1::OnNodeChanged(Edge * const edge) noexcept
{
  m_qtnode->SetCenterX(edge->GetNode()->GetX());
  m_qtnode->SetCenterY(edge->GetNode()->GetY());
  m_qtnode->SetText( { edge->GetNode()->GetConcept()->GetName() } );
  this->update();
  if (this->scene()) { this->scene()->update(); }
  m_signal_edge_changed(this);
}

void ribi::cmap::QtEdge1::OnNodePosChanged(QtRoundedRectItem * const node) noexcept
{
  this->m_qtnode->SetCenterX(node->x());
  this->m_qtnode->SetCenterY(node->y());
  this->m_qtnode->update();
  this->update();
  m_signal_edge_changed(this);
}

void ribi::cmap::QtEdge1::OnTailArrowChanged(Edge * const edge) noexcept
{
  SetHasTailArrow(edge->HasTailArrow());
  assert(edge->HasTailArrow() == this->GetArrow()->HasTail());
  m_signal_edge_changed(this);
}

void ribi::cmap::QtEdge1::OnTextChanged(QtRoundedEditRectItem* item) noexcept
{
  const auto new_name = item->GetText()[0];
  const auto old_name = GetEdge()->GetNode()->GetConcept()->GetName();
  if (old_name != new_name)
  {
    this->GetEdge()->GetNode()->GetConcept()->SetName(new_name);
    m_signal_edge_changed(this);
  }
}

void ribi::cmap::QtEdge1::OnToChanged(Edge * const edge) noexcept
{
  this->GetTo()->SetNode(edge->GetTo());
  assert(edge->GetTo() == this->GetTo()->GetNode());
  m_signal_edge_changed(this);
  this->update(); //Obligatory: when the 'target/to' QtNode moves, this update causes the QtEdge keep pointing to
}


void ribi::cmap::QtEdge1::OnArrowChanged(const QtQuadBezierArrowItem* const item)
{
  GetEdge()->GetNode()->GetConcept()->SetName(
    Container().Concatenate(m_qtnode->GetText())
  );
  GetEdge()->SetHeadArrow(item->HasHead());
  GetEdge()->SetTailArrow(item->HasTail());
  this->update();

  //this->m_signal_item_has_updated(this);
}

void ribi::cmap::QtEdge1::OnMustUpdateScene()
{
  if (scene()) { scene()->update(); }
}

void ribi::cmap::QtEdge1::OnRequestSceneUpdate()
{
  if (scene()) { scene()->update(); }
  //this->m_signal_request_scene_update();
}


void ribi::cmap::QtEdge1::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) noexcept
{
  if (!this->m_arrow->scene())
  {
    assert(this->scene());
    this->scene()->addItem(m_arrow.get()); //Must be removed?

  }
  if (!this->m_qtnode->scene())
  {
    assert(this->scene());
    this->scene()->addItem(m_qtnode.get()); //Must be removed?

  }
  assert(this->scene());
  assert(this->m_arrow->scene());
  assert(this->m_qtnode->scene());
  assert(this->m_from->scene());

  if (m_arrow->isVisible())
  {
    //Translate
    //painter->translate(m_qtnode->GetCenterPos());

    //Paint
    m_arrow->paint(painter,option,widget);

    //Untranslate
    //painter->translate(-m_qtnode->GetCenterPos());
  }

  if (m_qtnode->isVisible())
  {
    //Translate
    painter->translate(m_qtnode->GetCenterPos());

    //Paint
    m_qtnode->paint(painter,option,widget);

    //Untranslate
    painter->translate(-m_qtnode->GetCenterPos());
  }

  const QPen pen{
    this->hasFocus() || this->isSelected()
    ? this->GetQtNode()->GetFocusPen()
    : this->GetQtNode()->GetContourPen()
  };
  m_arrow->SetPen(pen);
  m_qtnode->setPen(pen);

  #define FIXING_BUG_260
  #ifdef FIXING_BUG_260
  //if (show_bounding_rect)
  {
    const QPen prev_pen = painter->pen();
    const QBrush prev_brush = painter->brush();
    painter->setPen(QPen(QColor(96,0,0)));
    painter->setBrush(QBrush(QColor(255,0,0,32)));
    painter->drawRect(this->boundingRect().adjusted(1.0,1.0,-1.0,-1.0));
    painter->setPen(prev_pen);
    painter->setBrush(prev_brush);
  }
  #endif
}

void ribi::cmap::QtEdge1::SetEdge(const boost::shared_ptr<Edge>& edge) noexcept
{
  const bool verbose{false};

  if (m_edge == edge)
  {
    return;
  }

  if (verbose)
  {
    std::stringstream s;
    s << "Setting edge '" << edge->ToStr() << "'\n";
  }

  bool from_changed{true};
  bool has_head_changed{true};
  bool has_tail_changed{true};
  bool node_changed{true};
  bool to_changed{true};

  if (m_edge && edge)
  {
    const auto from_after = edge->GetFrom();
    const auto has_head_after = edge->HasHeadArrow();
    const auto has_tail_after = edge->HasTailArrow();
    const auto node_after = edge->GetNode();
    const auto to_after = edge->GetTo();

    const auto from_before = m_edge->GetFrom();
    const auto has_head_before = m_edge->HasHeadArrow();
    const auto has_tail_before = m_edge->HasTailArrow();
    const auto node_before = m_edge->GetNode();
    const auto to_before = m_edge->GetTo();

    from_changed = from_before != from_after;
    has_head_changed = has_head_before != has_head_after;
    has_tail_changed = has_tail_before != has_tail_after;
    node_changed = node_before != node_after;
    to_changed = to_before != to_after;


    if (verbose)
    {
      if (from_changed)
      {
        std::stringstream s;
        s
          << "From will change from "
          << from_before
          << " to "
          << from_after
          << '\n'
        ;
        TRACE(s.str());
      }
      if (has_head_changed)
      {
        std::stringstream s;
        s
          << "Has head will change from "
          << has_head_before
          << " to "
          << has_head_after
          << '\n'
        ;
        TRACE(s.str());
      }
      if (has_tail_changed)
      {
        std::stringstream s;
        s
          << "Has tail will change from "
          << has_tail_before
          << " to "
          << has_tail_after
          << '\n'
        ;
        TRACE(s.str());
      }
      if (node_changed)
      {
        std::stringstream s;
        s << "Node will change from " << node_before->ToStr()
          << " to " << node_after->ToStr() << '\n';
        TRACE(s.str());
      }
      if (to_changed)
      {
        std::stringstream s;
        s << "To will change from " << to_before
          << " to " << to_after << '\n';
        TRACE(s.str());
      }
    }
  }

  if (m_edge)
  {
    //Disconnect m_concept
    m_edge->m_signal_from_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge1::OnFromChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_head_arrow_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge1::OnHeadArrowChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_node_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge1::OnNodeChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_tail_arrow_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge1::OnTailArrowChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_to_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge1::OnToChanged,this,boost::lambda::_1)
    );
  }

  //Replace
  m_edge = edge;

  if (!m_edge) { return; }

  //Sync
  m_qtnode->SetCenterX(m_edge->GetNode()->GetX());
  m_qtnode->SetCenterY(m_edge->GetNode()->GetY());
  m_qtnode->SetText( { m_edge->GetNode()->GetConcept()->GetName() } );

  m_edge->m_signal_from_changed.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnFromChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_head_arrow_changed.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnHeadArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_node_changed.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnNodeChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_tail_arrow_changed.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnTailArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_to_changed.connect(
    boost::bind(&ribi::cmap::QtEdge1::OnToChanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (from_changed)
  {
    m_edge->m_signal_from_changed(m_edge.get());
  }
  if (has_head_changed)
  {
    m_edge->m_signal_head_arrow_changed(m_edge.get());
  }
  if (has_tail_changed)
  {
    m_edge->m_signal_tail_arrow_changed(m_edge.get());
  }
  if (node_changed)
  {
    m_edge->m_signal_node_changed(m_edge.get());
  }
  if (to_changed)
  {
    m_edge->m_signal_to_changed(m_edge.get());
  }

  assert( edge ==  m_edge);
  assert(*edge == *m_edge);
}

void ribi::cmap::QtEdge1::SetFrom(const From& from) noexcept
{
  m_from = from;
}

void ribi::cmap::QtEdge1::SetHasHeadArrow(const bool has_head_arrow) noexcept
{
  assert(m_arrow);
  assert(m_edge);
  this->m_edge->SetHeadArrow(has_head_arrow);
  this->m_arrow->SetHasHead(has_head_arrow);
}

void ribi::cmap::QtEdge1::SetHasTailArrow(const bool has_tail_arrow) noexcept
{
  assert(m_arrow);
  assert(m_edge);
  this->m_edge->SetTailArrow(has_tail_arrow);
  this->m_arrow->SetHasTail(has_tail_arrow);
}


void ribi::cmap::QtEdge1::SetTo(const To& to) noexcept
{
  m_to = to;
}

QPainterPath ribi::cmap::QtEdge1::shape() const noexcept
{
  return m_qtnode->shape().translated(m_qtnode->GetCenterPos())
    .united(m_arrow->shape())
  ;
}

std::string ribi::cmap::QtEdge1::ToStr() const noexcept
{
  std::stringstream s;
  s << (*this);
  return s.str();
}

std::ostream& ribi::cmap::operator<<(std::ostream& os, const QtEdge1& qtedge) noexcept
{
  os
    << (*qtedge.GetEdge())
  ;
  return os;
}

bool ribi::cmap::operator==(const QtEdge1& /*lhs*/, const QtEdge1& /*rhs*/) noexcept
{
  //A stub
  return true;
}
