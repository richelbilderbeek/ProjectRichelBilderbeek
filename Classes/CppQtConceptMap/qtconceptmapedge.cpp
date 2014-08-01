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
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable
  );



  SetEdge(edge);

  //Bounding rectangle
  //this->setRect(m_display_strategy->boundingRect()); //NEW
  //this->update();

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

void ribi::cmap::QtEdge::DisableAll() noexcept
{
  this->setEnabled(false);
  this->setVisible(false);
  this->m_arrow->setEnabled(false);
  this->m_arrow->setVisible(false);
}

void ribi::cmap::QtEdge::EnableAll() noexcept
{
  this->setEnabled(true);
  this->setVisible(true);
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

std::string ribi::cmap::QtEdge::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::cmap::QtEdge::GetVersionHistory() noexcept
{
  return {
    "201x-xx-xx: version 1.0: initial version"
    "2014-08-01: version 1.1: start of versioning"
  };
}

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

void ribi::cmap::QtEdge::OnConceptChanged(Node * const node) noexcept
{
  //Node changed, sync QtRoundedRectItem
  assert(node);
  assert(node == m_edge->GetNode().get());
  const std::string new_str{node->GetConcept()->GetName()};
  const std::vector<std::string> new_text{new_str};
  assert(new_text.size() == 1);
  this->SetText(new_text);
  assert(GetText() == new_text);
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

  //Replace
  m_edge = edge;

  //Sync
  SetX(edge->GetNode()->GetX());
  SetY(edge->GetNode()->GetY());
  SetText( { edge->GetNode()->GetConcept()->GetName() } );

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
}

void ribi::cmap::QtEdge::SetNode(const boost::shared_ptr<Node>& node) noexcept
{
  const bool verbose{false};

  assert(node);
  if (m_edge->GetNode() == node)
  {
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
    //?Need to worry about Node its signals?
    //m_edge->GetNode().m_signal_something.disconnect(
    //m_edge->m_signal_node_changed.disconnect(
    //  boost::bind(&ribi::cmap::QtEdge::OnNodeChanged,this,boost::lambda::_1)
    //);
    m_edge->GetNode()->m_signal_concept_changed.disconnect(
      boost::bind(&ribi::cmap::QtEdge::OnConceptChanged,this,boost::lambda::_1)
    );

  }

  //Replace m_edge its node by the new one
  //m_edge->SetNode(node);

  //Sync
  this->SetText( {node->GetConcept()->GetName()} );

  assert(m_edge->GetNode() == node_after );


  //?Need to worry about Node its signals?
  //m_edge->GetNode().m_signal_something.connect(
  //m_edge->m_signal_node_changed.connect(
  //  boost::bind(&ribi::cmap::QtEdge::OnNodeChanged,this,boost::lambda::_1)
  //);

  //m_edge->GetNode()->m_signal_concept_changed(m_edge->GetNode().get());
  m_edge->m_signal_node_changed(m_edge.get());


  assert( node ==  m_edge->GetNode());
  assert(*node == *m_edge->GetNode());
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

void ribi::cmap::QtEdge::SetTo(QtNode * const to) noexcept
{
  m_to = to;
}

QPainterPath ribi::cmap::QtEdge::shape() const
{
  return
    QtConceptMapElement::shape()
    .united(m_arrow->shape().translated(-this->GetPos()));
}

#ifndef NDEBUG
void ribi::cmap::QtEdge::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtEdge::Test");
  const bool verbose{true};
  const int node_test_index{0};
  const int edge_test_index{0};
  const boost::shared_ptr<Node> node_from{cmap::NodeFactory().GetTest(node_test_index)};
  const boost::shared_ptr<Node> node_to{cmap::NodeFactory().GetTest(node_test_index)};
  const boost::shared_ptr<QtNode> qtnode_from{new QtNode(node_from)};
  const boost::shared_ptr<QtNode> qtnode_to{new QtNode(node_to)};
  const boost::shared_ptr<Edge> edge{EdgeFactory().GetTest(edge_test_index,node_from,node_to)};
  const boost::shared_ptr<QtEdge> qtedge{new QtEdge(edge,qtnode_from.get(),qtnode_to.get())};
  const boost::shared_ptr<QtRoundedEditRectItem> qtitem{boost::dynamic_pointer_cast<QtRoundedEditRectItem>(qtedge)};
  if (verbose) { TRACE("X of QtEdge and QtRoundedEditRectItem must match at creation"); }
  {
    const double edge_x{edge->GetNode()->GetX()};
    const double qtedge_x{qtitem->GetX()};
    assert(edge_x == qtedge_x);
  }
  if (verbose) { TRACE("Y of QtEdge and QtRoundedEditRectItem must match at creation"); }
  {
    const double edge_y{edge->GetNode()->GetY()};
    const double qtedge_y{qtitem->GetY()};
    assert(edge_y == qtedge_y);
  }
  if (verbose) { TRACE("Text of QtEdge must be one line"); }
  {
    assert(qtitem->GetText().size() == 1);
  }
  if (verbose) { TRACE("Text of QtEdge and QtRoundedEditRectItem must match at creation"); }
  {
    const std::string qtitem_name{qtitem->GetText()[0]};
    const std::string qtedge_name{qtedge->GetNode()->GetConcept()->GetName()};
    if (qtitem_name != qtedge_name)
    {
      TRACE(qtitem_name);
      TRACE(qtedge_name);
    }
    assert(qtitem_name == qtedge_name);
  }
  if (verbose) { TRACE("If X is set via QtEdge, QtRoundedEditRectItem must sync"); }
  {
    const double old_x{qtedge->GetX()};
    const double new_x{old_x + 10.0};
    qtedge->SetX(new_x);
    assert(std::abs(qtitem->GetX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("If Y is set via QtEdge, QtRoundedEditRectItem must sync"); }
  {
    const double old_y{qtedge->GetY()};
    const double new_y{old_y + 10.0};
    qtedge->SetY(new_y);
    assert(std::abs(qtitem->GetY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("If X is set via QtRoundedEditRectItem, QtEdge must sync"); }
  {
    const double old_x{qtitem->GetX()};
    const double new_x{old_x + 10.0};
    qtitem->SetX(new_x);
    assert(std::abs(qtedge->GetX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("If Y is set via QtRoundedEditRectItem, QtEdge must sync"); }
  {
    const double old_y{qtitem->GetY()};
    const double new_y{old_y + 10.0};
    qtitem->SetY(new_y);
    assert(std::abs(qtedge->GetY() - new_y) < 2.0);
  }
  //Test text on edge being in sync
  if (verbose) { TRACE("If text is set via QtEdge, QtRoundedEditRectItem must sync"); }
  {
    const std::string qtedge_name_old{qtedge->GetNode()->GetConcept()->GetName()};
    const std::string qtedge_name_new{qtedge_name_old + "(modified)"};
    const auto concept = qtedge->GetNode()->GetConcept();
    concept->SetName(qtedge_name_new);
    assert(qtitem->GetText()[0] == qtedge_name_new);
  }
  assert(!"Refactor");
  if (verbose) { TRACE("If text is set via QtRoundedEditRectItem, QtEdge must sync"); }
  {
    const std::string qtedge_name_old{qtitem->GetText()[0]};
    const std::string qtedge_name_new{qtedge_name_old + "(modified)"};
    qtitem->SetText( { qtedge_name_new } );
    assert(qtedge->GetNode()->GetConcept()->GetName() == qtedge_name_new);
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

  if (verbose) { TRACE("QtEdge must accept hover events"); }
  {
    assert(qtedge->acceptHoverEvents()); //Must remove the 's' in Qt5?
  }
  if (verbose) { TRACE("QtEdge its arrow must accept hover events"); }
  {
    assert(qtedge->GetArrow()->acceptHoverEvents()); //Must remove the 's' in Qt5?
  }

  assert(!"Check in");
  TRACE("Finished ribi::cmap::QtEdge::Test successfully");
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
