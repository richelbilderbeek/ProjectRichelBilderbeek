#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbedgeitem.h"

#include <cassert>

#include <boost/lambda/lambda.hpp>
#include <boost/math/constants/constants.hpp>

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>

#include "pvdbconcept.h"
#include "pvdbedge.h"
#include "pvdbedgefactory.h"
#include "pvdbhelper.h"
#include "pvdbnode.h"
#include "pvdbnodefactory.h"
#include "qtpvdbbrushfactory.h"
#include "qtpvdbconceptitem.h"
#include "qtpvdbnodeitem.h"
#include "qtquadbezierarrowitem.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbEdgeItem::QtPvdbEdgeItem(
    const boost::shared_ptr<ribi::pvdb::Edge> edge,
    const boost::shared_ptr<QtPvdbConceptItem> concept_item,
    QtPvdbNodeItem* const from,
    QtPvdbNodeItem* const to)
  : m_arrow{},
    m_concept_item(concept_item),
    m_contour_pen(QPen(QColor(255,255,255))),
    m_focus_pen(concept_item->GetFocusPen()),
      m_edge(edge), //m_edge must be initialized before m_arrow
    m_from(from),
    m_to(to)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_concept_item);
  assert(m_edge);
  assert(m_from);
  assert(m_to);
  assert(from != to);
  assert(m_from != m_to);
  //m_edge must be initialized before m_arrow
  m_arrow.reset(new QtQuadBezierArrowItem(from,edge->HasTailArrow(),this,edge->HasHeadArrow(),to));
  assert(m_arrow);
  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );

  this->setAcceptHoverEvents(true);
  //this->setAcceptsHoverEvents(true); //Since Qt5?
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

  m_concept_item->SetMainBrush(QtPvdbBrushFactory::CreateBlueGradientBrush());
  m_concept_item->SetContourPen(QPen(QColor(255,255,255)));
  m_concept_item->SetTextPen(QPen(QColor(0,0,0)));

  //Name
  this->SetName(edge->GetConcept()->GetName());
  this->GetConceptItem()->SetName(edge->GetConcept()->GetName());
  //assert(m_edge->GetConcept()->GetName() == GetName()
  //    && m_edge->GetConcept()->GetName() == m_concept_item->GetText()
  //    && "Names/texts must be in sync");


  //Position
  this->SetPos(edge->GetX(),edge->GetY());
  this->GetConceptItem()->SetPos(edge->GetX(),edge->GetY());

  #ifndef NDEBUG
  const double epsilon = 0.000001;
  assert(std::abs(this->pos().x() - GetEdge()->GetX()) < epsilon);
  assert(std::abs(this->pos().x() - this->GetConceptItem()->x()) < epsilon);
  assert(std::abs(this->pos().y() - GetEdge()->GetY()) < epsilon);
  assert(std::abs(this->pos().y() - this->GetConceptItem()->y()) < epsilon);
  #endif

  //Bounding rectangle
  this->setRect(m_concept_item->boundingRect()); //NEW
  this->update();

  assert( ( m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
    || m_concept_item->boundingRect() != QtPvdbConceptMapItem::boundingRect() )
    && "Bounding rects of edge and concept item might differ");

  //Qt things


  //Signals
  m_arrow->m_signal_item_updated.connect(
    boost::bind(
      &ribi::pvdb::QtPvdbEdgeItem::OnItemHasUpdated,this));

  m_edge->m_signal_edge_changed.connect(
    boost::bind(
      &ribi::pvdb::QtPvdbEdgeItem::OnEdgeChanged,this,boost::lambda::_1));

  m_concept_item->m_signal_item_has_updated.connect(
    boost::bind(
      &ribi::pvdb::QtPvdbEdgeItem::OnItemHasUpdated,this));

  m_concept_item->m_signal_request_scene_update.connect(
    boost::bind(
      &ribi::pvdb::QtPvdbEdgeItem::OnRequestSceneUpdate,this));

  m_concept_item->m_signal_position_changed.connect(
    boost::bind(
      &ribi::pvdb::QtPvdbEdgeItem::SetPos,this,boost::lambda::_1,boost::lambda::_2));

  if (QtPvdbEditConceptItem * edit_concept = dynamic_cast<QtPvdbEditConceptItem*>(concept_item.get()))
  {
    edit_concept->m_signal_request_edit.connect(
      boost::bind(
        &QtPvdbConceptMapItem::OnConceptRequestsEdit,
        this
      )
    );
  }
  assert(this->acceptHoverEvents()); //Must remove the 's' in Qt5?
  assert(this->m_concept_item->acceptHoverEvents());
  assert(this->m_arrow->acceptHoverEvents()); //Must remove the 's' in Qt5?
}

QRectF ribi::pvdb::QtPvdbEdgeItem::boundingRect() const
{
  assert((m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
      || m_concept_item->boundingRect() != QtPvdbConceptMapItem::boundingRect())
    && "Bounding rects should be synced, but this member function is used to sync them,"
    && "so this must be checked on a higher level");

  return QtPvdbConceptMapItem::boundingRect() //2013-07-06: Bypassed going via m_concept_item
    .united(m_arrow->boundingRect().translated(-this->pos()));
  //return m_concept_item->boundingRect()
  //  .united(m_arrow->boundingRect().translated(-this->pos()));
}

void ribi::pvdb::QtPvdbEdgeItem::DisableAll()
{
  this->setEnabled(false);
  this->setVisible(false);
  this->m_concept_item->setEnabled(false);
  this->m_concept_item->setVisible(false);
  this->m_arrow->setEnabled(false);
  this->m_arrow->setVisible(false);
}

void ribi::pvdb::QtPvdbEdgeItem::EnableAll()
{
  this->setEnabled(true);
  this->setVisible(true);
  this->m_concept_item->setEnabled(true);
  this->m_concept_item->setVisible(true);
  this->m_arrow->setEnabled(true);
  this->m_arrow->setVisible(true);
}

const boost::shared_ptr<const ribi::pvdb::Concept> ribi::pvdb::QtPvdbEdgeItem::GetConcept() const
{
  const boost::shared_ptr<const ribi::pvdb::Concept> p = m_edge->GetConcept();
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::pvdb::Concept> ribi::pvdb::QtPvdbEdgeItem::GetConcept()
{
  const boost::shared_ptr<ribi::pvdb::Concept> p = m_edge->GetConcept();
  assert(p);
  return p;
}

const std::string ribi::pvdb::QtPvdbEdgeItem::GetName() const
{
  return m_edge->GetConcept()->GetName();
}

void ribi::pvdb::QtPvdbEdgeItem::focusInEvent(QFocusEvent*)
{
  //Lose focus of arrow
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  m_concept_item->SetContourPen(m_focus_pen); //Updates itself
  assert(!m_concept_item->hasFocus());
}

void ribi::pvdb::QtPvdbEdgeItem::focusOutEvent(QFocusEvent*)
{
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  m_concept_item->SetContourPen(m_contour_pen); //Updates itself
  assert(!m_concept_item->hasFocus());
}

void ribi::pvdb::QtPvdbEdgeItem::keyPressEvent(QKeyEvent *event)
{
  assert(m_arrow);
  assert(m_edge);
  m_concept_item->keyPressEvent(event);
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
  QtPvdbConceptMapItem::keyPressEvent(event);
}

void ribi::pvdb::QtPvdbEdgeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{  
  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );
  if (event->modifiers() & Qt::ShiftModifier)
  {
    if ((event->pos() - this->m_arrow->GetTail() + this->pos()).manhattanLength() < 20.0)
    {
      this->SetHasTailArrow( !m_arrow->HasTail() ); //FIX 2013-02-10
      //this->m_arrow->SetHasTail( !m_arrow->HasTail() ); //BUG 2013-02-10
      //this->update(); //Don't!
      //m_signal_item_updated(this); //Don't!
    }
    else if ((event->pos() - this->m_arrow->GetHead() + this->pos()).manhattanLength() < 20.0)
    {
      this->SetHasHeadArrow( !m_arrow->HasHead() ); //FIX 2013-02-10
      //this->m_arrow->SetHasHead( !m_arrow->HasHead() ); //BUG 2013-02-10
      //this->update(); //Don't!
      //m_signal_item_updated(this); //Don't!
    }
  }

  //What is clicked on: the concept or the arrow? Assume concept
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  if (!this->rect().contains(event->pos()))
  {
    //If the concept is not clicked...
    //but the arrow is...
    QPointF pos_on_arrow = event->pos();
    pos_on_arrow += (this->pos());
    if (m_arrow->shape().contains(pos_on_arrow)
      || (event->pos() - this->m_arrow->GetTail() + this->pos()).manhattanLength() < 20.0
      || (event->pos() - this->m_arrow->GetHead() + this->pos()).manhattanLength() < 20.0
      )
    {
      //give focus to the arrow
      m_arrow->SetPen(m_arrow->GetFocusPen());
      return;
    }
  }
  QtPvdbConceptMapItem::mousePressEvent(event);
}

void ribi::pvdb::QtPvdbEdgeItem::OnEdgeChanged(const pvdb::Edge * const edge)
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
  m_concept_item->SetName(edge->GetConcept()->GetName());
  this->GetEdge()->SetX(edge->GetX());
  this->GetEdge()->SetY(edge->GetY());

  //assert(m_edge->GetConcept()->GetName() == GetName()
  //    && m_edge->GetConcept()->GetName() == m_concept_item->GetText()
  //    && "Names/texts must be in sync before");

  //this->SetName(m_concept_item->GetText());
  this->SetName(edge->GetConcept()->GetName()); //2013-09-15


  //assert(m_edge->GetConcept()->GetName() == GetName()
  //    && m_edge->GetConcept()->GetName() == m_concept_item->GetText()
  //    && "Names/texts must be in sync after");

  this->setRect(m_concept_item->boundingRect());

  assert( ( m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
    || m_concept_item->boundingRect() != QtPvdbConceptMapItem::boundingRect() )
    && "Bounding rects of edge and concept item might differ");

}

void ribi::pvdb::QtPvdbEdgeItem::OnItemHasUpdated()
{
  this->SetName(m_concept_item->GetName());

  assert(m_edge->GetConcept()->GetName() == GetName()
      && m_edge->GetConcept()->GetName() == m_concept_item->GetName()
      && "Names/texts must be in sync after");

  //this->setRect(QtPvdbConceptMapItem::boundingRect());
  this->setRect(m_concept_item->boundingRect());
  assert( ( m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
    || m_concept_item->boundingRect() != QtPvdbConceptMapItem::boundingRect() )
    && "Bounding rects might differ between edge and concept item");

  this->update();
  this->m_signal_item_has_updated(this);
}

void ribi::pvdb::QtPvdbEdgeItem::OnRequestSceneUpdate()
{
  this->m_signal_request_scene_update();
}


void ribi::pvdb::QtPvdbEdgeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  m_concept_item->SetName(this->GetConcept()->GetName());

  //Only QtPvdbEditConceptItem actually modifies the position of the concept items
  if (dynamic_cast<QtPvdbEditConceptItem*>(m_concept_item.get()))
  {
    //Notifies the GUI-independent collaborators
    this->m_concept_item->SetPos(x(),y());
  }

  assert(this->pos() == m_arrow->GetMidItem()->pos());
  painter->translate(-this->pos());
  m_arrow->paint(painter,option,widget);
  painter->translate(this->pos());

  assert(m_concept_item);
  if (this->hasFocus() || this->isSelected())
  {
    //Does the arrow or the concept have focus?
    if (m_arrow->GetPen() != m_arrow->GetFocusPen())
    {
      m_concept_item->SetContourPen(m_focus_pen);
    }
    else
    {
      m_concept_item->SetContourPen(m_contour_pen);
    }
  }
  else
  {
    m_concept_item->SetContourPen(m_contour_pen);
  }
  if (m_concept_item->isVisible())
  {
    //Edges connect to the center node do not display their concept item
    m_concept_item->paint(painter,option,widget);
  }
}

void ribi::pvdb::QtPvdbEdgeItem::SetConcept(const boost::shared_ptr<ribi::pvdb::Concept> concept) //NEW 2013-01-07
{
  this->m_edge->SetConcept(concept);
}

void ribi::pvdb::QtPvdbEdgeItem::SetHasHeadArrow(const bool has_head_arrow)
{
  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );

  this->m_edge->SetHeadArrow(has_head_arrow);
  this->m_arrow->SetHasHead(has_head_arrow);

  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );
}

void ribi::pvdb::QtPvdbEdgeItem::SetHasTailArrow(const bool has_tail_arrow)
{
  assert(m_arrow);
  assert(m_edge);
  assert(m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert(m_arrow->HasHead() == m_edge->HasHeadArrow() );

  this->m_edge->SetTailArrow(has_tail_arrow);
  this->m_arrow->SetHasTail(has_tail_arrow);

  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );
}

void ribi::pvdb::QtPvdbEdgeItem::SetName(const std::string& name)
{
  m_edge->GetConcept()->SetName(name);
}

void ribi::pvdb::QtPvdbEdgeItem::SetX(const double x)
{
  if ( x != this->pos().x()
    || x != this->GetEdge()->GetX()
    || x != this->GetConceptItem()->pos().x()
  )
  {
    this->setX(x);
    this->GetEdge()->SetX(x);
    this->GetConceptItem()->setX(x);
    if (!(std::abs(x - this->GetEdge()->GetX()) < 0.000001))
    {
      TRACE(x);
      TRACE(GetEdge()->GetX());
    }
    assert(std::abs(x - this->pos().x()) < 0.000001);
    assert(std::abs(x - this->GetEdge()->GetX()) < 0.000001);
    assert(std::abs(x - this->GetConceptItem()->pos().x()) < 0.000001);
  }
  assert(std::abs(x - this->pos().x()) < 0.000001);
  assert(std::abs(x - this->GetEdge()->GetX()) < 0.000001);
  assert(std::abs(x - this->GetConceptItem()->pos().x()) < 0.000001);
}

void ribi::pvdb::QtPvdbEdgeItem::SetY(const double y)
{
  if ( y != this->pos().y()
    || y != this->GetEdge()->GetY()
    || y != this->GetConceptItem()->pos().y()
    )
  {
    this->setY(y);
    this->GetEdge()->SetY(y);
    this->GetConceptItem()->setY(y);
    assert(std::abs(y - this->pos().y()) < 0.000001);
    assert(std::abs(y - this->GetEdge()->GetY()) < 0.000001);
    assert(std::abs(y - this->GetConceptItem()->pos().y()) < 0.000001);
  }
  assert(std::abs(y - this->pos().y()) < 0.000001);
  assert(std::abs(y - this->GetEdge()->GetY()) < 0.000001);
  assert(std::abs(y - this->GetConceptItem()->pos().y()) < 0.000001);
}

QPainterPath ribi::pvdb::QtPvdbEdgeItem::shape() const
{
  return m_concept_item->shape()
    .united(m_arrow->shape().translated(-this->pos()));
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbEdgeItem::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test SetX and SetY being in sync
  {
    const boost::shared_ptr<ribi::pvdb::Node> node_from = pvdb::NodeFactory::GetTests()[0];
    const boost::shared_ptr<ribi::pvdb::Node> node_to = pvdb::NodeFactory::GetTests()[0];
    const boost::shared_ptr<QtPvdbConceptItem> qtconcept_item_from(new QtPvdbEditConceptItem(node_from->GetConcept()));
    const boost::shared_ptr<QtPvdbConceptItem> qtconcept_item_to(new QtPvdbEditConceptItem(node_to->GetConcept()));
    const boost::shared_ptr<QtPvdbNodeItem> qtnode_from(new QtPvdbNodeItem(node_from,qtconcept_item_from));
    const boost::shared_ptr<QtPvdbNodeItem> qtnode_to(new QtPvdbNodeItem(node_to,qtconcept_item_to));
    const std::size_t n_edges = pvdb::EdgeFactory::GetTests(node_from,node_to).size();
    for (std::size_t edge_index=0; edge_index!=n_edges; ++edge_index)
    {
      const std::vector<boost::shared_ptr<ribi::pvdb::Edge> > edges = pvdb::EdgeFactory::GetTests(node_from,node_to);
      boost::shared_ptr<ribi::pvdb::Edge> edge = edges[edge_index];
      assert(edge);
      boost::shared_ptr<QtPvdbConceptItem> qtconcept_item(new QtPvdbEditConceptItem(edge->GetConcept()));
      boost::shared_ptr<QtPvdbEdgeItem> qtedge(
        new QtPvdbEdgeItem(edge,qtconcept_item,qtnode_from.get(),qtnode_to.get()));
      const double epsilon = 0.000001;
      assert(qtconcept_item->GetConcept() == qtedge->GetConcept());
      assert(qtconcept_item->GetConcept() == edge->GetConcept());
      assert(edge == qtedge->GetEdge());
      {
        const double edge_x = edge->GetX();
        const double qtedge_x = qtedge->pos().x();
        const double qtconcept_item_x = qtedge->GetConceptItem()->pos().x();
        if(!(edge_x == qtedge_x && qtedge_x == qtconcept_item_x))
        {
          TRACE(edge_x);
          TRACE(qtedge_x);
          TRACE(qtconcept_item_x);
        }
        assert(edge_x == qtedge_x && qtedge_x == qtconcept_item_x
         && "X coordinat must be in sync");
        const double edge_y = edge->GetY();
        const double qtedge_y = qtedge->pos().y();
        const double qtconcept_item_y = qtedge->GetConceptItem()->pos().y();
        assert(edge_y == qtedge_y && qtedge_y == qtconcept_item_y
         && "Y coordinat must be in sync");
      }
      {
        const double pi = boost::math::constants::pi<double>();
        const double e = boost::math::constants::e<double>();
        const double new_x = pi;
        const double new_y = e;

        //Change via edge
        edge->SetX(new_x);
        edge->SetY(new_y);

        const double edge_x = edge->GetX();
        const double qtedge_x = qtedge->pos().x();
        const double qtconcept_item_x = qtedge->GetConceptItem()->pos().x();
        if(!(std::abs(new_x - edge_x) < epsilon
          && std::abs(new_x - qtconcept_item_x) < epsilon
          && std::abs(new_x - qtedge_x) < epsilon))
        {
         TRACE(new_x);
         TRACE(edge_x);
         TRACE(qtedge_x);
         TRACE(qtconcept_item_x);
        }

        assert(
            std::abs(new_x - edge_x) < epsilon
         && std::abs(new_x - qtconcept_item_x) < epsilon
         && std::abs(new_x - qtedge_x) < epsilon
         && "X coordinat must be in sync");
        const double edge_y = edge->GetY();
        const double qtedge_y = qtedge->pos().y();
        const double qtconcept_item_y = qtedge->GetConceptItem()->pos().y();
        assert(edge_y == qtedge_y && qtedge_y == qtconcept_item_y
         && "Y coordinat must be in sync");
      }
      {
        const double new_x = 123.456;
        const double new_y = 654.321;

        //Change via Qt edge
        qtedge->SetPos(new_x,new_y);

        const double edge_x = edge->GetX();
        const double qtedge_x = qtedge->pos().x();
        const double qtconcept_item_x = qtedge->GetConceptItem()->pos().x();
        assert(
            std::abs(new_x - edge_x) < epsilon
         && std::abs(new_x - qtconcept_item_x) < epsilon
         && std::abs(new_x - qtedge_x) < epsilon
         && "X coordinat must be in sync");
        const double edge_y = edge->GetY();
        const double qtedge_y = qtedge->pos().y();
        const double qtconcept_item_y = qtedge->GetConceptItem()->pos().y();
        assert(
            std::abs(new_y - edge_y) < epsilon
         && std::abs(new_y - qtconcept_item_y) < epsilon
         && std::abs(new_y - qtedge_y) < epsilon
         && "Y coordinat must be in sync");
      }
      {
        const double new_x = -1234.5678;
        const double new_y = -8765.4321;

        //Change via Qt concept item
        qtedge->GetConceptItem()->SetPos(new_x,new_y);

        const double edge_x = edge->GetX();
        const double qtedge_x = qtedge->pos().x();
        const double qtconcept_item_x = qtedge->GetConceptItem()->pos().x();
        assert(
            std::abs(new_x - edge_x) < epsilon
         && std::abs(new_x - qtconcept_item_x) < epsilon
         && std::abs(new_x - qtedge_x) < epsilon
         && "X coordinat must be in sync");
        const double edge_y = edge->GetY();
        const double qtedge_y = qtedge->pos().y();
        const double qtconcept_item_y = qtedge->GetConceptItem()->pos().y();
        assert(
            std::abs(new_y - edge_y) < epsilon
         && std::abs(new_y - qtconcept_item_y) < epsilon
         && std::abs(new_y - qtedge_y) < epsilon
         && "Y coordinat must be in sync");
      }
    }
  }
  //Test text on edge being in sync
  {
    const boost::shared_ptr<ribi::pvdb::Node> node_from = pvdb::NodeFactory::GetTests()[0];
    const boost::shared_ptr<ribi::pvdb::Node> node_to = pvdb::NodeFactory::GetTests()[0];
    const boost::shared_ptr<QtPvdbConceptItem> qtconcept_item_from(new QtPvdbEditConceptItem(node_from->GetConcept()));
    const boost::shared_ptr<QtPvdbConceptItem> qtconcept_item_to(new QtPvdbEditConceptItem(node_to->GetConcept()));
    const boost::shared_ptr<QtPvdbNodeItem> qtnode_from(new QtPvdbNodeItem(node_from,qtconcept_item_from));
    const boost::shared_ptr<QtPvdbNodeItem> qtnode_to(new QtPvdbNodeItem(node_to,qtconcept_item_to));
    const std::size_t n_edges = pvdb::EdgeFactory::GetTests(node_from,node_to).size();
    for (std::size_t edge_index=0; edge_index!=n_edges; ++edge_index)
    {
      const std::vector<boost::shared_ptr<ribi::pvdb::Edge> > edges = pvdb::EdgeFactory::GetTests(node_from,node_to);
      boost::shared_ptr<ribi::pvdb::Edge> edge = edges[edge_index];
      assert(edge);
      boost::shared_ptr<QtPvdbConceptItem> qtconcept_item(new QtPvdbEditConceptItem(edge->GetConcept()));
      boost::shared_ptr<QtPvdbEdgeItem> qtedge(
        new QtPvdbEdgeItem(edge,qtconcept_item,qtnode_from.get(),qtnode_to.get()));
      assert(qtconcept_item->GetConcept() == qtedge->GetConcept());
      assert(qtconcept_item->GetConcept() == edge->GetConcept());
      assert(edge == qtedge->GetEdge());
      {
        const std::string edge_name = edge->GetConcept()->GetName();
        const std::string qtedge_name = qtedge->GetName();
        const std::string qtconcept_text = qtconcept_item->GetName();

        if(!(edge_name == qtedge_name && qtedge_name == qtconcept_text))
        {
          TRACE(edge_name);
          TRACE(qtedge_name);
          TRACE(qtconcept_text);
        }
        assert(edge_name == qtedge_name && qtedge_name == qtconcept_text
         && "Names/texts must be in sync");
      }
      {
        const std::string edge_name_before = edge->GetConcept()->GetName();
        const std::string qtedge_name_before = qtedge->GetName();
        const std::string qtconcept_text_before = qtconcept_item->GetName();
        assert(edge_name_before == qtedge_name_before && qtedge_name_before == qtconcept_text_before
         && "Names/texts must be in sync");

        //Change via edge's concept
        edge->GetConcept()->SetName( edge->GetConcept()->GetName() + " made longer");

        const std::string edge_name_after = edge->GetConcept()->GetName();
        const std::string qtedge_name_after = qtedge->GetName();
        const std::string qtconcept_text_after = qtconcept_item->GetName();

        assert(edge_name_after == qtedge_name_after && qtedge_name_after == qtconcept_text_after
         && "Names/texts must be in sync");
      }
      {
        const std::string edge_name_before = edge->GetConcept()->GetName();
        const std::string qtedge_name_before = qtedge->GetName();
        const std::string qtconcept_text_before = qtconcept_item->GetName();
        assert(edge_name_before == qtedge_name_before && qtedge_name_before == qtconcept_text_before
         && "Names/texts must be in sync");

        //Change via Qt edge
        qtedge->SetName(qtedge->GetName() + " and made longer again");

        const std::string edge_name_after = edge->GetConcept()->GetName();
        const std::string qtedge_name_after = qtedge->GetName();
        const std::string qtconcept_text_after = qtconcept_item->GetName();

        assert(edge_name_after == qtedge_name_after && qtedge_name_after == qtconcept_text_after
         && "Names/texts must be in sync");
      }
      {
        const std::string edge_name_before = edge->GetConcept()->GetName();
        const std::string qtedge_name_before = qtedge->GetName();
        const std::string qtconcept_text_before = qtconcept_item->GetName();
        assert(edge_name_before == qtedge_name_before && qtedge_name_before == qtconcept_text_before
         && "Names/texts must be in sync");

        //Change via Qt concept item
        qtedge->GetConceptItem()->SetName(qtedge->GetConceptItem()->GetName() + " and again");

        const std::string edge_name_after = edge->GetConcept()->GetName();
        const std::string qtedge_name_after = qtedge->GetName();
        const std::string qtconcept_text_after = qtconcept_item->GetName();
        if (!(edge_name_after == qtedge_name_after && qtedge_name_after == qtconcept_text_after))
        {
          TRACE(edge_name_after);
          TRACE(qtedge_name_after);
          TRACE(qtconcept_text_after);
        }

        assert(edge_name_after == qtedge_name_after && qtedge_name_after == qtconcept_text_after
         && "Names/texts must be in sync");
      }
    }
  }

  //Test boundingRects being in sync
  {
    const boost::shared_ptr<ribi::pvdb::Node> node_from = pvdb::NodeFactory::GetTests()[0];
    const boost::shared_ptr<ribi::pvdb::Node> node_to = pvdb::NodeFactory::GetTests()[0];
    const boost::shared_ptr<QtPvdbConceptItem> qtconcept_item_from(new QtPvdbEditConceptItem(node_from->GetConcept()));
    const boost::shared_ptr<QtPvdbConceptItem> qtconcept_item_to(new QtPvdbEditConceptItem(node_to->GetConcept()));
    const boost::shared_ptr<QtPvdbNodeItem> qtnode_from(new QtPvdbNodeItem(node_from,qtconcept_item_from));
    const boost::shared_ptr<QtPvdbNodeItem> qtnode_to(new QtPvdbNodeItem(node_to,qtconcept_item_to));
    const std::size_t n_edges = pvdb::EdgeFactory::GetTests(node_from,node_to).size();
    for (std::size_t edge_index=0; edge_index!=n_edges; ++edge_index)
    {
      const std::vector<boost::shared_ptr<ribi::pvdb::Edge> > edges = pvdb::EdgeFactory::GetTests(node_from,node_to);
      boost::shared_ptr<ribi::pvdb::Edge> edge = edges[edge_index];
      assert(edge);
      boost::shared_ptr<QtPvdbConceptItem> qtconcept_item(new QtPvdbEditConceptItem(edge->GetConcept()));
      boost::shared_ptr<QtPvdbEdgeItem> qtedge(
        new QtPvdbEdgeItem(edge,qtconcept_item,qtnode_from.get(),qtnode_to.get()));
      //const double epsilon = 0.000001;
      assert(qtconcept_item->GetConcept() == qtedge->GetConcept());
      assert(qtconcept_item->GetConcept() == edge->GetConcept());
      assert(edge == qtedge->GetEdge());
      {
        const QRectF qtedge_rect = qtedge->boundingRect();
        const QRectF qtconcept_rect = qtconcept_item->boundingRect();

        assert(qtedge->GetName() == qtconcept_item->GetName());

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
        edge->GetConcept()->SetName( edge->GetConcept()->GetName() + " made longer");

        const QRectF qtedge_rect_after = qtedge->boundingRect();
        const QRectF qtconcept_rect_after = qtconcept_item->boundingRect();

        assert(qtedge_rect_after.width() >= qtconcept_rect_after.width()
          && "The complete edge (including nodes will be at least as wide as the concept only");
        assert(qtedge_rect_after.height() >= qtconcept_rect_after.height()
          && "The complete edge (including nodes will be at least as high as the concept only");
        assert(qtedge_rect_after.width() > qtedge_rect_before.width()
         && "bounding rects must be bigger");
        assert(qtconcept_rect_after.width() > qtconcept_rect_before.width()
         && "bounding rects must be bigger");
      }
      {
        const QRectF qtedge_rect_before = qtedge->boundingRect();
        const QRectF qtconcept_rect_before = qtconcept_item->boundingRect();
        assert(qtedge_rect_before.width() >= qtconcept_rect_before.width()
          && "The complete edge (including nodes will be at least as wide as the concept only");
        assert(qtedge_rect_before.height() >= qtconcept_rect_before.height()
          && "The complete edge (including nodes will be at least as high as the concept only");

        //Change via Qt edge
        qtedge->SetName(qtedge->GetName() + " and made longer again");

        const QRectF qtedge_rect_after = qtedge->boundingRect();
        const QRectF qtconcept_rect_after = qtconcept_item->boundingRect();


        assert(qtedge_rect_after.width() >= qtconcept_rect_after.width()
          && "The complete edge (including nodes will be at least as wide as the concept only");
        assert(qtedge_rect_after.height() >= qtconcept_rect_after.height()
          && "The complete edge (including nodes will be at least as high as the concept only");
        const double edge_area_after  = qtedge_rect_after.width()  * qtedge_rect_after.height();
        const double edge_area_before = qtedge_rect_before.width() * qtedge_rect_before.height();
        assert(edge_area_after + 1.0 >= edge_area_before //Add 1 pixel to be sure
         && "bounding rects must get bigger");
        const double concept_area_after  = qtconcept_rect_after.width()  * qtconcept_rect_after.height();
        const double concept_area_before = qtconcept_rect_before.width() * qtconcept_rect_before.height();
        assert(concept_area_after + 1.0 >= concept_area_before
         && "bounding rects must get bigger");
      }
      {
        const QRectF qtedge_rect_before = qtedge->boundingRect();
        const QRectF qtconcept_rect_before = qtconcept_item->boundingRect();
        assert(qtedge_rect_before.width() >= qtconcept_rect_before.width()
          && "The complete edge (including nodes will be at least as wide as the concept only");
        assert(qtedge_rect_before.height() >= qtconcept_rect_before.height()
          && "The complete edge (including nodes will be at least as high as the concept only");

        //Change via Qt concept item
        qtedge->GetConceptItem()->SetName(qtedge->GetConceptItem()->GetName() + " and again");

        const QRectF qtedge_rect_after = qtedge->boundingRect();
        const QRectF qtconcept_rect_after = qtconcept_item->boundingRect();

        assert(qtedge_rect_after.width() >= qtconcept_rect_after.width()
          && "The complete edge (including nodes will be at least as wide as the concept only");
        assert(qtedge_rect_after.height() >= qtconcept_rect_after.height()
          && "The complete edge (including nodes will be at least as high as the concept only");
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


}
#endif
