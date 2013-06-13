#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbedgeitem.h"

#include <cassert>

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>

#include "pvdbconcept.h"
#include "pvdbedge.h"
#include "qtpvdbbrushfactory.h"
#include "qtpvdbconceptitem.h"
#include "qtpvdbnodeitem.h"
#include "qtquadbezierarrowitem.h"
#include "trace.h"

QtPvdbEdgeItem::QtPvdbEdgeItem(
    const boost::shared_ptr<pvdb::Edge> edge,
    const boost::shared_ptr<QtPvdbConceptItem> concept_item,
    QtPvdbNodeItem* const from,
    QtPvdbNodeItem* const to)
  : m_concept_item(concept_item),
    m_contour_pen(QPen(QColor(255,255,255))),
    m_focus_pen(concept_item->GetFocusPen()),
    m_edge(edge), //m_edge must be initialized before m_arrow
    m_from(from),
    m_to(to)
{
  //m_edge must be initialized before m_arrow
  assert(m_concept_item);
  assert(m_edge);
  assert(m_from);
  assert(m_to);
  assert(from != to);
  assert(m_from != m_to);
  m_arrow.reset(new QtQuadBezierArrowItem(from,edge->HasTailArrow(),this,edge->HasHeadArrow(),to));
  assert(m_arrow);
  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );

  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->setPos(edge->GetX(),edge->GetY());

  m_concept_item->SetMainBrush(QtPvdbBrushFactory::CreateBlueGradientBrush());
  m_concept_item->SetContourPen(QPen(QColor(255,255,255)));
  m_concept_item->SetTextPen(QPen(QColor(0,0,0)));

  m_arrow->m_signal_item_updated.connect(
    boost::bind(
      &QtPvdbEdgeItem::OnItemHasUpdated,this));

  m_edge->m_signal_changed.connect(
    boost::bind(
      &QtPvdbEdgeItem::OnEdgeChanged,this));

  m_concept_item->m_signal_item_has_updated.connect(
    boost::bind(
      &QtPvdbEdgeItem::OnItemHasUpdated,this));

  m_concept_item->m_signal_request_scene_update.connect(
    boost::bind(
      &QtPvdbEdgeItem::OnRequestSceneUpdate,this));

  if (QtPvdbEditConceptItem * edit_concept = dynamic_cast<QtPvdbEditConceptItem*>(concept_item.get()))
  {
    edit_concept->m_signal_request_edit.connect(
      boost::bind(
        &QtPvdbConceptMapItem::OnConceptRequestsEdit,
        this
      )
    );
  }

}

QRectF QtPvdbEdgeItem::boundingRect() const
{
  return m_concept_item->boundingRect()
    .united(m_arrow->boundingRect().translated(-this->pos()));
}

void QtPvdbEdgeItem::DisableAll()
{
  this->setEnabled(false);
  this->setVisible(false);
  this->m_concept_item->setEnabled(false);
  this->m_concept_item->setVisible(false);
  this->m_arrow->setEnabled(false);
  this->m_arrow->setVisible(false);
}

void QtPvdbEdgeItem::EnableAll()
{
  this->setEnabled(true);
  this->setVisible(true);
  this->m_concept_item->setEnabled(true);
  this->m_concept_item->setVisible(true);
  this->m_arrow->setEnabled(true);
  this->m_arrow->setVisible(true);
}

const boost::shared_ptr<const pvdb::Concept> QtPvdbEdgeItem::GetConcept() const
{
  const boost::shared_ptr<const pvdb::Concept> p = m_edge->GetConcept();
  assert(p);
  return p;
}

const boost::shared_ptr<pvdb::Concept>  QtPvdbEdgeItem::GetConcept()
{
  const boost::shared_ptr<pvdb::Concept> p = m_edge->GetConcept();
  assert(p);
  return p;
}

void QtPvdbEdgeItem::focusInEvent(QFocusEvent*)
{
  //Lose focus of arrow
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  m_concept_item->SetContourPen(m_focus_pen); //Updates itself
  assert(!m_concept_item->hasFocus());
}

void QtPvdbEdgeItem::focusOutEvent(QFocusEvent*)
{
  m_arrow->SetPen(QPen(QColor(0,0,0)));
  m_concept_item->SetContourPen(m_contour_pen); //Updates itself
  assert(!m_concept_item->hasFocus());
}

void QtPvdbEdgeItem::keyPressEvent(QKeyEvent *event)
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

void QtPvdbEdgeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void QtPvdbEdgeItem::OnEdgeChanged()
{
  assert(m_arrow);
  assert(m_edge);
  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );
  this->SetHasHeadArrow(m_edge->HasHeadArrow()); //FIX 2013-02-10
  this->SetHasTailArrow(m_edge->HasTailArrow()); //FIX 2013-02-10
  //m_arrow->SetHasHead(m_edge->HasHeadArrow()); //BUG 2013-02-10
  //m_arrow->SetHasTail(m_edge->HasTailArrow()); //BUG 2013-02-10
  m_concept_item->SetText(m_edge->GetConcept()->GetName());
}

void QtPvdbEdgeItem::OnItemHasUpdated()
{
  this->update();
  this->m_signal_item_has_updated(this);
}

void QtPvdbEdgeItem::OnRequestSceneUpdate()
{
  this->m_signal_request_scene_update();
}


void QtPvdbEdgeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  m_concept_item->SetText(this->GetConcept()->GetName()); //NEW 2013-01-08

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
  m_concept_item->paint(painter,option,widget);
}

void QtPvdbEdgeItem::SetConcept(const boost::shared_ptr<pvdb::Concept> concept) //NEW 2013-01-07
{
  this->m_edge->SetConcept(concept);
}

void QtPvdbEdgeItem::SetHasHeadArrow(const bool has_head_arrow)
{
  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );

  this->m_edge->SetHeadArrow(has_head_arrow);
  this->m_arrow->SetHasHead(has_head_arrow);

  assert( m_arrow->HasTail() == m_edge->HasTailArrow() );
  assert( m_arrow->HasHead() == m_edge->HasHeadArrow() );
}

void QtPvdbEdgeItem::SetHasTailArrow(const bool has_tail_arrow)
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

void QtPvdbEdgeItem::SetName(const std::string& name)
{
  m_edge->GetConcept()->SetName(name);
}


QPainterPath QtPvdbEdgeItem::shape() const
{
  return m_concept_item->shape()
    .united(m_arrow->shape().translated(-this->pos()));
}

