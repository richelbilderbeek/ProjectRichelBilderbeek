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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapedge.h"

#include <cassert>

#include <boost/lambda/lambda.hpp>
#include <boost/math/constants/constants.hpp>

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>

#include "conceptmapconcept.h"
#include "conceptmapedge.h"
#include "container.h"
#include "conceptmapedgefactory.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapelement.h"
#include "qtconceptmapnode.h"
#include "qtquadbezierarrowitem.h"
#include "trace.h"

#include "qtconceptmapcenternode.h"

#pragma GCC diagnostic pop

ribi::cmap::QtEdge::QtEdge(
    const boost::shared_ptr<Edge>& edge,
    QtNode* const from,
    QtNode* const to)
  : m_signal_base_changed{},
    m_signal_edge_changed{},
    m_arrow{new QtQuadBezierArrowItem(from,edge->HasTailArrow(),this,edge->HasHeadArrow(),to)},
    m_edge{}, //Will be initialized by setEdge
    m_from{from},
    m_to{to}
{
  #ifndef NDEBUG
  Test();
  #endif
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

  this->setAcceptHoverEvents(true);
  //this->setAcceptsHoverEvents(true); //Since Qt5?
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);


  this->SetEdge(edge);

  //Bounding rectangle
  //this->setRect(m_display_strategy->boundingRect()); //NEW
  this->update();

  //assert( ( m_display_strategy->boundingRect() == QtConceptMapElement::boundingRect()
  //  || m_display_strategy->boundingRect() != QtConceptMapElement::boundingRect() )
  //  && "Bounding rects of edge and concept item might differ");

  //Qt things


  //Signals
  /*
  m_arrow->m_signal_item_updated.connect(
    boost::bind(&ribi::cmap::QtEdge::OnItemHasUpdated,this)
  );

  //Edge
  m_edge->m_signal_node_changed.connect(
    boost::bind(
      &ribi::cmap::QtEdge::OnNodeChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_from_changed.connect(
    boost::bind(
      &ribi::cmap::QtEdge::OnFromChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_head_arrow_changed.connect(
    boost::bind(
      &ribi::cmap::QtEdge::OnHeadArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_tail_arrow_changed.connect(
    boost::bind(
      &ribi::cmap::QtEdge::OnTailArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_to_changed.connect(
    boost::bind(
      &ribi::cmap::QtEdge::OnToChanged,this,boost::lambda::_1)
  );
  //m_edge->m_signal_x_changed.connect(
  //  boost::bind(
  //    &ribi::cmap::QtEdge::OnXchanged,this,boost::lambda::_1)
  //);
  //m_edge->m_signal_y_changed.connect(
  //  boost::bind(
  //    &ribi::cmap::QtEdge::OnYchanged,this,boost::lambda::_1)
  //);

  //DisplayStrategy
  m_display_strategy->m_signal_item_has_updated.connect(
    boost::bind(
      &ribi::cmap::QtEdge::OnItemHasUpdated,this));

  m_display_strategy->m_signal_request_scene_update.connect(
    boost::bind(
      &ribi::cmap::QtEdge::OnRequestSceneUpdate,this));

  m_display_strategy->m_signal_position_changed.connect(
    boost::bind(
      &ribi::cmap::QtEdge::SetPos,this,boost::lambda::_1,boost::lambda::_2));

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
  if (QtEditStrategy * edit_concept = dynamic_cast<QtEditStrategy*>(display_strategy.get()))
  {
    edit_concept->m_signal_request_edit.connect(
      boost::bind(
        &QtConceptMapElement::OnConceptRequestsEdit,
        this
      )
    );
  }
  #endif
  */
  assert(this->acceptHoverEvents()); //Must remove the 's' in Qt5?
  //assert(this->m_display_strategy->acceptHoverEvents());
  assert(this->m_arrow->acceptHoverEvents()); //Must remove the 's' in Qt5?
}

ribi::cmap::QtEdge::~QtEdge()
{
  //Disconnect signals
  /*
  assert(m_from);
  assert(m_to);
  const bool is_connected_to_center_node
    = dynamic_cast<QtCenterNode*>(m_from) || dynamic_cast<QtCenterNode*>(m_to);

  m_arrow->m_signal_item_updated.disconnect(
    boost::bind(&ribi::cmap::QtEdge::OnItemHasUpdated,this)
  );

  //Edge
  m_edge->m_signal_from_changed.disconnect(
    boost::bind(
      &ribi::cmap::QtEdge::OnFromChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_head_arrow_changed.disconnect(
    boost::bind(
      &ribi::cmap::QtEdge::OnHeadArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_node_changed.disconnect(
    boost::bind(
      &ribi::cmap::QtEdge::OnNodeChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_tail_arrow_changed.disconnect(
    boost::bind(
      &ribi::cmap::QtEdge::OnTailArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_to_changed.disconnect(
    boost::bind(
      &ribi::cmap::QtEdge::OnToChanged,this,boost::lambda::_1)
  );
  //m_edge->m_signal_x_changed.disconnect(
  //  boost::bind(
  //    &ribi::cmap::QtEdge::OnXchanged,this,boost::lambda::_1)
  //);
  //m_edge->m_signal_y_changed.disconnect(
  //  boost::bind(
  //    &ribi::cmap::QtEdge::OnYchanged,this,boost::lambda::_1)
  //);

  //DisplayStrategy
  m_display_strategy->m_signal_item_has_updated.disconnect(
    boost::bind(&ribi::cmap::QtEdge::OnItemHasUpdated,this)
  );

  m_display_strategy->m_signal_request_scene_update.disconnect(
    boost::bind(&ribi::cmap::QtEdge::OnRequestSceneUpdate,this)
  );

  m_display_strategy->m_signal_position_changed.disconnect(
    boost::bind(&ribi::cmap::QtEdge::SetPos,this,boost::lambda::_1,boost::lambda::_2)
  );

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

QRectF ribi::cmap::QtEdge::boundingRect() const
{
  //assert((m_display_strategy->boundingRect() == QtConceptMapElement::boundingRect()
  //    || m_display_strategy->boundingRect() != QtConceptMapElement::boundingRect())
  //  && "Bounding rects should be synced, but this member function is used to sync them,"
  //  && "so this must be checked on a higher level");

  return QtConceptMapElement::boundingRect() //Bypassed going via m_concept_item
    .united(m_arrow->boundingRect().translated(-this->GetPos()));
  //return m_concept_item->boundingRect()
  //  .united(m_arrow->boundingRect().translated(-this->pos()));
}

void ribi::cmap::QtEdge::CheckMe() const noexcept
{
  #ifndef NDEBUG
  //const double epsilon = 0.000001;
  //assert(std::abs(this->GetPos().x() - GetEdge()->GetNode()->GetX()) < epsilon);
  //assert(std::abs(this->GetPos().y() - GetEdge()->GetNode()->GetY()) < epsilon);
  #endif
}

void ribi::cmap::QtEdge::DisableAll() noexcept
{
  this->setEnabled(false);
  this->setVisible(false);
  //this->m_display_strategy->setEnabled(false);
  //this->m_display_strategy->setVisible(false);
  this->m_arrow->setEnabled(false);
  this->m_arrow->setVisible(false);
}

void ribi::cmap::QtEdge::EnableAll() noexcept
{
  this->setEnabled(true);
  this->setVisible(true);
  //this->m_display_strategy->setEnabled(true);
  //this->m_display_strategy->setVisible(true);
  this->m_arrow->setEnabled(true);
  this->m_arrow->setVisible(true);
}

boost::shared_ptr<const ribi::cmap::Node> ribi::cmap::QtEdge::GetNode() const noexcept
{
  const auto p = m_edge->GetNode();
  assert(p);
  return p;
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::QtEdge::GetNode() noexcept
{
  const auto p = m_edge->GetNode();
  assert(p);
  return p;
}

/*
std::string ribi::cmap::QtEdge::GetName() const noexcept
{
  return m_edge->GetNode()->GetConcept()->GetName();
}
*/

void ribi::cmap::QtEdge::focusInEvent(QFocusEvent*) noexcept
{
  //Lose focus of arrow
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  //m_display_strategy->SetContourPen(m_display_strategy->GetFocusPen()); //Updates itself
}

void ribi::cmap::QtEdge::focusOutEvent(QFocusEvent*) noexcept
{
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  //m_display_strategy->SetContourPen(m_display_strategy->GetContourPen()); //Updates itself
}

void ribi::cmap::QtEdge::keyPressEvent(QKeyEvent *event) noexcept
{
  assert(m_arrow);
  assert(m_edge);
  //m_display_strategy->keyPressEvent(event);
  switch (event->key())
  {
    case Qt::Key_F1:
    case Qt::Key_F2:
    return;
  }
  if (m_arrow->isEnabled())
  {
    m_arrow->keyPressEvent(event);
    m_edge->SetHeadArrow( m_arrow->HasHead() );
    m_edge->SetTailArrow( m_arrow->HasTail() );

    assert(m_edge->HasHeadArrow() == m_arrow->HasHead());
    assert(m_edge->HasTailArrow() == m_arrow->HasTail());
  }
  QtConceptMapElement::keyPressEvent(event);
}

void ribi::cmap::QtEdge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{  
  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );
  if (event->modifiers() & Qt::ShiftModifier)
  {
    if ((event->pos() - this->m_arrow->GetTail() + this->GetPos()).manhattanLength() < 20.0)
    {
      this->SetHasTailArrow( !m_arrow->HasTail() ); //FIX 2013-02-10
      //this->m_arrow->SetHasTail( !m_arrow->HasTail() ); //BUG 2013-02-10
      //this->update(); //Don't!
      //m_signal_item_updated(this); //Don't!
    }
    else if ((event->pos() - this->m_arrow->GetHead() + this->GetPos()).manhattanLength() < 20.0)
    {
      this->SetHasHeadArrow( !m_arrow->HasHead() ); //FIX 2013-02-10
      //this->m_arrow->SetHasHead( !m_arrow->HasHead() ); //BUG 2013-02-10
      //this->update(); //Don't!
      //m_signal_item_updated(this); //Don't!
    }
  }

  //What is clicked on: the concept or the arrow? Assume concept
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  if (!this->GetRect().contains(event->pos()))
  {
    //If the concept is not clicked...
    //but the arrow is...
    QPointF pos_on_arrow = event->pos();
    pos_on_arrow += (this->GetPos());
    if (m_arrow->shape().contains(pos_on_arrow)
      || (event->pos() - this->m_arrow->GetTail() + this->GetPos()).manhattanLength() < 20.0
      || (event->pos() - this->m_arrow->GetHead() + this->GetPos()).manhattanLength() < 20.0
      )
    {
      //give focus to the arrow
      m_arrow->SetPen(m_arrow->GetFocusPen());
      return;
    }
  }
  QtConceptMapElement::mousePressEvent(event);
}



void ribi::cmap::QtEdge::OnFromChanged(Edge * const edge) noexcept
{
  this->GetFrom()->SetNode(edge->GetFrom());
  assert(edge->GetFrom() == this->GetFrom()->GetNode());
}

void ribi::cmap::QtEdge::OnHeadArrowChanged(Edge * const edge) noexcept
{
  SetHasHeadArrow(edge->HasHeadArrow());
  assert(edge->HasHeadArrow() == this->GetArrow()->HasHead());
}

void ribi::cmap::QtEdge::OnNodeChanged(Edge * const edge) noexcept
{
  this->SetNode(edge->GetNode());
  this->SetX(edge->GetNode()->GetX());
  this->SetY(edge->GetNode()->GetY());
  //SetNode(edge->GetNode());
  assert(edge->GetNode() == this->GetNode());
}

void ribi::cmap::QtEdge::OnTailArrowChanged(Edge * const edge) noexcept
{
  SetHasTailArrow(edge->HasTailArrow());
  assert(edge->HasTailArrow() == this->GetArrow()->HasTail());
}

void ribi::cmap::QtEdge::OnToChanged(Edge * const edge) noexcept
{
  this->GetTo()->SetNode(edge->GetTo());
  assert(edge->GetTo() == this->GetTo()->GetNode());
}

/*
void ribi::cmap::QtEdge::OnXchanged(Edge * const edge) noexcept
{
  SetX(edge->GetX());
  assert(edge->GetX() == this->GetX());
}

void ribi::cmap::QtEdge::OnYchanged(Edge * const edge) noexcept
{
  SetY(edge->GetY());
  assert(edge->GetY() == this->GetY());
}
*/

/*
void ribi::cmap::QtEdge::OnEdgeChanged(Edge * const edge) noexcept
{
  assert(m_arrow);
  assert(m_edge);
  assert(edge == m_edge.get());
  this->SetPos(edge->GetX(),edge->GetY());
  //m_edge is changed, so change m_arrow
  m_arrow->SetHasHead(edge->HasHeadArrow());
  m_arrow->SetHasTail(edge->HasTailArrow());
  assert( m_arrow->HasTail() == GetEdge()->HasTailArrow() );
  assert( m_arrow->HasHead() == GetEdge()->HasHeadArrow() );
  m_display_strategy->SetName(edge->GetConcept()->GetName());
  this->GetEdge()->SetX(edge->GetX());
  this->GetEdge()->SetY(edge->GetY());

  //assert(m_edge->GetConcept()->GetName() == GetName()
  //    && m_edge->GetConcept()->GetName() == m_concept_item->GetText()
  //    && "Names/texts must be in sync before");

  //this->SetName(m_concept_item->GetText());
  this->SetName(edge->GetConcept()->GetName());


  //assert(m_edge->GetConcept()->GetName() == GetName()
  //    && m_edge->GetConcept()->GetName() == m_concept_item->GetText()
  //    && "Names/texts must be in sync after");

  this->setRect(m_display_strategy->boundingRect());

  assert( ( m_display_strategy->boundingRect() == QtConceptMapElement::boundingRect()
    || m_display_strategy->boundingRect() != QtConceptMapElement::boundingRect() )
    && "Bounding rects of edge and concept item might differ");

}
*/


void ribi::cmap::QtEdge::OnItemHasUpdated()
{
  this->GetNode()->GetConcept()->SetName(
    Container().ToStr(this->GetText())
  );

  //assert(m_edge->GetNode()->GetConcept()->GetName() == GetNode()->GetConcept()->GetName()
  //    && m_edge->GetNode()->GetConcept()->GetName() == m_display_strategy->GetName()
  //    && "Names/texts must be in sync after");

  //this->setRect(QtConceptMapItem::boundingRect());
  //this->setRect(m_display_strategy->boundingRect());


  //assert( ( m_display_strategy->boundingRect() == QtConceptMapElement::boundingRect()
  //  || m_display_strategy->boundingRect() != QtConceptMapElement::boundingRect() )
  //  && "Bounding rects might differ between edge and concept item");

  this->update();
  //this->m_signal_item_has_updated(this);
}

void ribi::cmap::QtEdge::OnRequestSceneUpdate()
{
  //this->m_signal_request_scene_update();
}


void ribi::cmap::QtEdge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) noexcept
{
  //m_display_strategy->SetName(this->GetNode()->GetConcept()->GetName());
  //CAN BE REMOVED? this->SetText( { GetNode()->GetConcept()->GetName() } );

  //Only QtEditStrategy actually modifies the position of the concept items
  //if (dynamic_cast<QtEditStrategy*>(m_display_strategy.get()))
  //{
  //  //Notifies the GUI-independent collaborators
  //  this->m_display_strategy->SetPos(x(),y());
  //}
  assert(m_arrow);
  assert(!m_arrow->GetMidItem() || this->GetPos() == m_arrow->GetMidItem()->pos());
  painter->translate(-this->GetPos());
  m_arrow->paint(painter,option,widget);
  painter->translate(this->GetPos());

  //assert(m_display_strategy);
  if (this->hasFocus() || this->isSelected())
  {
    //Does the arrow or the concept have focus?
    //if (m_arrow->GetPen() != m_arrow->GetFocusPen())
    //{
    //  m_display_strategy->SetContourPen(m_display_strategy->GetFocusPen());
    //}
    ///else
    //{
    //  m_display_strategy->SetContourPen(m_display_strategy->GetContourPen());
    //}
  }
  else
  {
    //m_display_strategy->SetContourPen(m_display_strategy->GetContourPen());
  }
  //if (m_display_strategy->isVisible())
  //{
  //  //Edges connect to the center node do not display their concept item
  //  m_display_strategy->paint(painter,option,widget);
  //}
}

void ribi::cmap::QtEdge::SetEdge(const boost::shared_ptr<Edge>& edge) noexcept
{
  const bool verbose{false};

  assert(edge);
  if (m_edge == edge)
  {
    CheckMe();
    return;
  }

  if (verbose)
  {
    std::stringstream s;
    s << "Setting edge '" << edge->ToStr() << "'\n";
  }

  const auto from_after = edge->GetFrom();
  const auto has_head_after = edge->HasHeadArrow();
  const auto has_tail_after = edge->HasTailArrow();
  const auto node_after = edge->GetNode();
  const auto to_after = edge->GetTo();

  bool from_changed{true};
  bool has_head_changed{true};
  bool has_tail_changed{true};
  bool node_changed{true};
  bool to_changed{true};

  if (m_edge)
  {
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
    //Disconnect m_concept
    m_edge->m_signal_from_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge::OnFromChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_head_arrow_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge::OnHeadArrowChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_node_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge::OnNodeChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_tail_arrow_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge::OnTailArrowChanged,this,boost::lambda::_1)
    );
    m_edge->m_signal_to_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge::OnToChanged,this,boost::lambda::_1)
    );

  }

  //Replace m_edge by the new one
  m_edge = edge;

  assert(m_edge->GetFrom() == from_after );
  assert(m_edge->HasHeadArrow() == has_head_after );
  assert(m_edge->HasTailArrow() == has_tail_after );
  assert(m_edge->GetNode() == node_after );
  assert(m_edge->GetTo() == to_after);


  m_edge->m_signal_from_changed.connect(
    boost::bind(&ribi::cmap::QtEdge::OnFromChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_head_arrow_changed.connect(
    boost::bind(&ribi::cmap::QtEdge::OnHeadArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_node_changed.connect(
    boost::bind(&ribi::cmap::QtEdge::OnNodeChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_tail_arrow_changed.connect(
    boost::bind(&ribi::cmap::QtEdge::OnTailArrowChanged,this,boost::lambda::_1)
  );
  m_edge->m_signal_to_changed.connect(
    boost::bind(&ribi::cmap::QtEdge::OnToChanged,this,boost::lambda::_1)
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
  CheckMe();
}

void ribi::cmap::QtEdge::SetNode(const boost::shared_ptr<Node>& node) noexcept //NEW 2013-01-07
{
  const bool verbose{false};

  assert(node);
  if (m_edge->GetNode() == node)
  {
    CheckMe();
    return;
  }

  if (verbose)
  {
    std::stringstream s;
    s << "Setting node '" << node->ToStr() << "'\n";
  }

  const auto node_after = node;

  if (m_edge->GetNode())
  {
    const auto node_before = m_edge->GetNode();

    if (verbose)
    {
      std::stringstream s;
      s << "Node will change from " << node_before->ToStr()
        << " to " << node_after->ToStr() << '\n';
      TRACE(s.str());
    }
    m_edge->m_signal_node_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge::OnNodeChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_edge its node by the new one
  m_edge->SetNode(node);

  assert(m_edge->GetNode() == node_after );

  m_edge->m_signal_node_changed.connect(
    boost::bind(&ribi::cmap::QtEdge::OnNodeChanged,this,boost::lambda::_1)
  );

  m_edge->m_signal_node_changed(m_edge.get());

  assert( node ==  m_edge->GetNode());
  assert(*node == *m_edge->GetNode());
  CheckMe();

}

void ribi::cmap::QtEdge::SetFrom(QtNode * const from) noexcept
{
  m_from = from;
}

void ribi::cmap::QtEdge::SetHasHeadArrow(const bool has_head_arrow) noexcept
{
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );

  this->m_edge->SetHeadArrow(has_head_arrow);
  this->m_arrow->SetHasHead(has_head_arrow);

  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );
}

void ribi::cmap::QtEdge::SetHasTailArrow(const bool has_tail_arrow) noexcept
{
  assert(m_arrow);
  assert(m_edge);
  assert(m_arrow->HasTail() == m_edge->HasTailArrow() );

  this->m_edge->SetTailArrow(has_tail_arrow);
  this->m_arrow->SetHasTail(has_tail_arrow);

  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
}

/*
void ribi::cmap::QtEdge::SetName(const std::string& name) noexcept
{
  m_edge->GetNode()->GetConcept()->SetName(name);
}
*/

void ribi::cmap::QtEdge::SetTo(QtNode * const to) noexcept
{
  m_to = to;
}

void ribi::cmap::QtEdge::SetX(const double x) noexcept
{
  if ( x != this->GetPos().x()
    || x != this->GetEdge()->GetNode()->GetX()
  //  || x != this->GetDisplayStrategy()->pos().x()
  )
  {
    this->setX(x);
    this->GetEdge()->GetNode()->SetX(x);
    //this->GetDisplayStrategy()->setX(x);
    if (!(std::abs(x - this->GetEdge()->GetNode()->GetX()) < 0.000001))
    {
      TRACE(x);
      TRACE(GetEdge()->GetNode()->GetX());
    }
    assert(std::abs(x - this->GetPos().x()) < 0.000001);
    assert(std::abs(x - this->GetEdge()->GetNode()->GetX()) < 0.000001);
    //assert(std::abs(x - this->GetDisplayStrategy()->pos().x()) < 0.000001);
  }
  assert(std::abs(x - this->GetPos().x()) < 0.000001);
  assert(std::abs(x - this->GetEdge()->GetNode()->GetX()) < 0.000001);
  //assert(std::abs(x - this->GetDisplayStrategy()->pos().x()) < 0.000001);
}

void ribi::cmap::QtEdge::SetY(const double y) noexcept
{
  if ( y != this->GetPos().y()
    || y != this->GetEdge()->GetNode()->GetY()
    //|| y != this->GetDisplayStrategy()->pos().y()
    )
  {
    this->setY(y);
    this->GetEdge()->GetNode()->SetY(y);
    //this->GetDisplayStrategy()->setY(y);
    assert(std::abs(y - this->GetPos().y()) < 0.000001);
    assert(std::abs(y - this->GetEdge()->GetNode()->GetY()) < 0.000001);
    //assert(std::abs(y - this->GetDisplayStrategy()->pos().y()) < 0.000001);
  }
  assert(std::abs(y - this->GetPos().y()) < 0.000001);
  assert(std::abs(y - this->GetEdge()->GetNode()->GetY()) < 0.000001);
  //assert(std::abs(y - this->GetDisplayStrategy()->pos().y()) < 0.000001);
}

QPainterPath ribi::cmap::QtEdge::shape() const
{
  return
    QtConceptMapElement::shape()
    //m_display_strategy->shape()
    .united(m_arrow->shape().translated(-this->GetPos()));
}

#ifndef NDEBUG
void ribi::cmap::QtEdge::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test SetX and SetY being in sync
  {
    const boost::shared_ptr<Node> node_from = cmap::NodeFactory().GetTests()[0];
    const boost::shared_ptr<Node> node_to = cmap::NodeFactory().GetTests()[0];
    //const boost::shared_ptr<QtEditStrategy> qtconcept_item_from(new QtEditStrategy(node_from->GetConcept()));
    //const boost::shared_ptr<QtEditStrategy> qtconcept_item_to(new QtEditStrategy(node_to->GetConcept()));
    const boost::shared_ptr<QtNode> qtnode_from(new QtNode(node_from));
    const boost::shared_ptr<QtNode> qtnode_to(new QtNode(node_to));
    const std::size_t n_edges = EdgeFactory().GetTests(node_from,node_to).size();
    for (std::size_t edge_index=0; edge_index!=n_edges; ++edge_index)
    {
      const std::vector<boost::shared_ptr<ribi::cmap::Edge> > edges = EdgeFactory().GetTests(node_from,node_to);
      boost::shared_ptr<Edge> edge = edges[edge_index];
      assert(edge);
      //boost::shared_ptr<QtEditStrategy> qtconcept_item(new QtEditStrategy(edge->GetNode()->GetConcept()));
      boost::shared_ptr<QtEdge> qtedge(
        new QtEdge(edge,qtnode_from.get(),qtnode_to.get()));
      //assert(qtconcept_item->GetConcept() == qtedge->GetNode()->GetConcept());
      //assert(qtconcept_item->GetConcept() == edge->GetNode()->GetConcept());
      assert(edge == qtedge->GetEdge());
      {
        const double edge_x = edge->GetNode()->GetX();
        const double qtedge_x = qtedge->GetPos().x();
        //const double qtconcept_item_x = qtedge->GetDisplayStrategy()->pos().x();
        if(!(edge_x == qtedge_x
        //  && qtedge_x == qtconcept_item_x
        ))
        {
          TRACE(edge_x);
          TRACE(qtedge_x);
          //TRACE(qtconcept_item_x);
        }
        assert(edge_x == qtedge_x
         && "X coordinat must be in sync");
        const double edge_y = edge->GetNode()->GetY();
        const double qtedge_y = qtedge->GetPos().y();
        //const double qtconcept_item_y = qtedge->GetDisplayStrategy()->pos().y();
        assert(edge_y == qtedge_y
         && "Y coordinat must be in sync");
      }
      #ifdef DISABLE_TEST_TEMP_20140729
      const double epsilon = 0.000001;
      {
        const double pi = boost::math::constants::pi<double>();
        const double e = boost::math::constants::e<double>();
        const double new_x = pi;
        const double new_y = e;

        //Change via edge
        edge->GetNode()->SetX(new_x);
        edge->GetNode()->SetY(new_y);

        const double edge_x = edge->GetNode()->GetX();
        const double qtedge_x = qtedge->GetPos().x();

        if(!(std::abs(new_x - edge_x) < epsilon
           && std::abs(new_x - qtedge_x) < epsilon))
        {
         TRACE(new_x);
         TRACE(edge_x);
         TRACE(qtedge_x);

        }

        assert(
            std::abs(new_x - edge_x) < epsilon
         && std::abs(new_x - qtedge_x) < epsilon
         && "X coordinat must be in sync");
        const double edge_y = edge->GetNode()->GetY();
        const double qtedge_y = qtedge->GetPos().y();
        assert(edge_y == qtedge_y
         && "Y coordinat must be in sync");
      }
      {
        const double new_x = 123.456;
        const double new_y = 654.321;

        //Change via Qt edge
        qtedge->GetNode()->SetPos(new_x,new_y);

        const double edge_x = edge->GetNode()->GetX();
        const double qtedge_x = qtedge->GetPos().x();

        assert(
            std::abs(new_x - edge_x) < epsilon
         && std::abs(new_x - qtedge_x) < epsilon
         && "X coordinat must be in sync");
        const double edge_y = edge->GetNode()->GetY();
        const double qtedge_y = qtedge->GetPos().y();

        assert(
            std::abs(new_y - edge_y) < epsilon
         && std::abs(new_y - qtedge_y) < epsilon
         && "Y coordinat must be in sync");
      }
      #endif // DISABLE_TEST_TEMP_20140729
    }
  }
  //Test text on edge being in sync
  {
    const boost::shared_ptr<Node> node_from = cmap::NodeFactory().GetTests()[0];
    const boost::shared_ptr<Node> node_to = cmap::NodeFactory().GetTests()[0];

    const boost::shared_ptr<QtNode> qtnode_from(new QtNode(node_from));
    const boost::shared_ptr<QtNode> qtnode_to(new QtNode(node_to));
    const std::size_t n_edges = EdgeFactory().GetTests(node_from,node_to).size();
    for (std::size_t edge_index=0; edge_index!=n_edges; ++edge_index)
    {
      const std::vector<boost::shared_ptr<ribi::cmap::Edge>> edges = EdgeFactory().GetTests(node_from,node_to);
      boost::shared_ptr<Edge> edge = edges[edge_index];
      assert(edge);

      boost::shared_ptr<QtEdge> qtedge(
        new QtEdge(edge,qtnode_from.get(),qtnode_to.get()));

      assert(edge == qtedge->GetEdge());
      {
        const std::string edge_name = edge->GetNode()->GetConcept()->GetName();
        const std::string qtedge_name = qtedge->GetNode()->GetConcept()->GetName();


        if(edge_name != qtedge_name)
        {
          TRACE(edge_name);
          TRACE(qtedge_name);
        }
        assert(edge_name == qtedge_name
         && "Names/texts must be in sync");
      }
      {
        const std::string edge_name_before = edge->GetNode()->GetConcept()->GetName();
        const std::string qtedge_name_before = qtedge->GetNode()->GetConcept()->GetName();

        assert(edge_name_before == qtedge_name_before && "Names/texts must be in sync");

        //Change via edge's concept
        edge->GetNode()->GetConcept()->SetName( edge->GetNode()->GetConcept()->GetName() + " made longer");

        const std::string edge_name_after = edge->GetNode()->GetConcept()->GetName();
        const std::string qtedge_name_after = qtedge->GetNode()->GetConcept()->GetName();


        assert(edge_name_after == qtedge_name_after && "Names/texts must be in sync");
      }
      {
        const std::string edge_name_before = edge->GetNode()->GetConcept()->GetName();
        const std::string qtedge_name_before = qtedge->GetNode()->GetConcept()->GetName();

        assert(edge_name_before == qtedge_name_before && "Names/texts must be in sync");

        //Change via Qt edge
        qtedge->GetNode()->GetConcept()->SetName(qtedge->GetNode()->GetConcept()->GetName() + " and made longer again");

        const std::string edge_name_after = edge->GetNode()->GetConcept()->GetName();
        const std::string qtedge_name_after = qtedge->GetNode()->GetConcept()->GetName();

        assert(edge_name_after == qtedge_name_after
         && "Names/texts must be in sync");
      }

    }
  }

  //Test boundingRects being in sync
  /*
  {
    const boost::shared_ptr<Node> node_from = cmap::NodeFactory().GetTests()[0];
    const boost::shared_ptr<Node> node_to = cmap::NodeFactory().GetTests()[0];

    const boost::shared_ptr<QtNode> qtnode_from(new QtNode(node_from));
    const boost::shared_ptr<QtNode> qtnode_to(new QtNode(node_to));
    const std::size_t n_edges = EdgeFactory().GetTests(node_from,node_to).size();
    for (std::size_t edge_index=0; edge_index!=n_edges; ++edge_index)
    {
      const std::vector<boost::shared_ptr<ribi::cmap::Edge> > edges = EdgeFactory().GetTests(node_from,node_to);
      boost::shared_ptr<Edge> edge = edges[edge_index];
      assert(edge);
      //boost::shared_ptr<QtEditStrategy> qtconcept_item(new QtEditStrategy(edge->GetNode()->GetConcept()));
      boost::shared_ptr<QtEdge> qtedge(
        new QtEdge(edge,qtnode_from.get(),qtnode_to.get()));
      //const double epsilon = 0.000001;
      assert(edge == qtedge->GetEdge());
      {
        const QRectF qtedge_rect = qtedge->boundingRect();
        const QRectF qtconcept_rect = qtconcept_item->boundingRect();

        assert(qtedge->GetNode()->GetConcept()->GetName() == qtconcept_item->GetName());

        assert(qtedge_rect.width() >= qtconcept_rect.width()
          && "The complete edge (including nodes will be at least as wide as the concept only");
        assert(qtedge_rect.height() >= qtconcept_rect.height()
          && "The complete edge (including nodes will be at least as high as the concept only");
      }
      {
        const QRectF qtedge_rect_before = qtedge->boundingRect();
        const QRectF qtconcept_rect_before = qtconcept_item->boundingRect();

        assert(qtedge_rect_before.width() >= qtconcept_rect_before.width()
          && "The complete edge (including nodes will be at least as wide as the concept only");
        assert(qtedge_rect_before.height() >= qtconcept_rect_before.height()
          && "The complete edge (including nodes will be at least as high as the concept only");

        //Change via edge's concept
        edge->GetNode()->GetConcept()->SetName( edge->GetNode()->GetConcept()->GetName() + " made longer");

        const QRectF qtedge_rect_after = qtedge->boundingRect();
        const QRectF qtconcept_rect_after = qtconcept_item->boundingRect();

        assert(qtedge_rect_after.width() * qtedge_rect_after.height()
          >=
            qtconcept_rect_after.width() * qtconcept_rect_after.height()
          && "The complete edge (including nodes will have an area at least the size of the concept its area");
        assert(
          (qtedge_rect_after.width() * qtedge_rect_after.height()) + 1.0
          >=
          qtedge_rect_before.width() * qtedge_rect_before.height()
         && "bounding rect area must be bigger");
      }
      {
        const QRectF qtedge_rect_before = qtedge->boundingRect();
        const QRectF qtconcept_rect_before = qtconcept_item->boundingRect();
        assert(qtedge_rect_before.width() >= qtconcept_rect_before.width()
          && "The complete edge (including nodes) will be at least as wide as the concept only");
        assert(qtedge_rect_before.height() >= qtconcept_rect_before.height()
          && "The complete edge (including nodes) will be at least as high as the concept only");

        //Change via Qt edge
        qtedge->GetNode()->GetConcept()->SetName(qtedge->GetNode()->GetConcept()->GetName() + " and made longer again");

        const QRectF qtedge_rect_after = qtedge->boundingRect();
        const QRectF qtconcept_rect_after = qtconcept_item->boundingRect();


        assert(
          qtedge_rect_after.width() * qtedge_rect_after.height()
          >=
          qtconcept_rect_after.width() * qtconcept_rect_after.height()
          && "The complete edge its area (including nodes) will be at least the concept its area");
        const double edge_area_after  = qtedge_rect_after.width()  * qtedge_rect_after.height();
        const double edge_area_before = qtedge_rect_before.width() * qtedge_rect_before.height();
        assert(edge_area_after + 1.0 >= edge_area_before //Add 1 pixel to be sure
         && "bounding rects must get bigger");
        const double concept_area_after  = qtconcept_rect_after.width()  * qtconcept_rect_after.height();
        const double concept_area_before = qtconcept_rect_before.width() * qtconcept_rect_before.height();
        assert(concept_area_after + 1.0 >= concept_area_before
         && "bounding rects must get bigger");
      }

    }
  }
  */


}
#endif

std::string ribi::cmap::QtEdge::ToStr() const noexcept
{
  std::stringstream s;
  s << (*this);
  return s.str();
}

std::ostream& ribi::cmap::operator<<(std::ostream& os, const QtEdge& qtedge) noexcept
{
  os
    << (*qtedge.GetEdge())
  ;
  return os;
}
