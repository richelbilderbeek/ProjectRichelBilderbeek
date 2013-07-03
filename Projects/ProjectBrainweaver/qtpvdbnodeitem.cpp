#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbnodeitem.h"

#include <cassert>
#include <boost/lambda/lambda.hpp>
#include <boost/signals2.hpp>
#include <QKeyEvent>
#include <QPen>

#include "pvdbnode.h"
#include "pvdbnodefactory.h"
#include "qtpvdbbrushfactory.h"
#include "qtpvdbeditconceptitem.h"
#include "qtpvdbrateconceptitem.h"
#include "pvdbconcept.h"
#include "qtpvdbconceptitem.h"
#include "trace.h"

QtPvdbNodeItem::QtPvdbNodeItem(
  const boost::shared_ptr<pvdb::Node> node,
  const boost::shared_ptr<QtPvdbConceptItem> concept_item)
  : m_concept_item(concept_item),
    m_contour_pen(concept_item->GetContourPen()),
    m_focus_pen(concept_item->GetFocusPen()),
    m_node(node)
{
  assert(node);
  assert(m_concept_item);
  assert(m_node);
  assert(m_concept_item->GetConcept().get() == m_node->GetConcept().get());

  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

  assert(flags() & QGraphicsItem::ItemIsFocusable);
  assert(flags() & QGraphicsItem::ItemIsSelectable);
  assert(flags() & QGraphicsItem::ItemIsMovable);


  this->setPos(m_node->GetX(),m_node->GetY());
  assert(this->pos().x() == m_node->GetX());
  assert(this->pos().y() == m_node->GetY());

  this->setRect(m_concept_item->boundingRect());
  assert(m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
    && "Bounding rects must by synced");


  m_concept_item->m_signal_item_has_updated.connect(
    boost::bind(
      &QtPvdbNodeItem::OnItemHasUpdated,this));


  m_concept_item->m_signal_request_scene_update.connect(
    boost::bind(
      &QtPvdbNodeItem::OnRequestsSceneUpdate,
      this
    )
  );

  if (QtPvdbEditConceptItem * edit_concept = dynamic_cast<QtPvdbEditConceptItem*>(concept_item.get()))
  {
    edit_concept->m_signal_request_edit.connect(
      boost::bind(
        &QtPvdbConceptMapItem::OnConceptRequestsEdit,
        this
      )
    );
  }

  if (QtPvdbRateConceptItem * rate_concept = dynamic_cast<QtPvdbRateConceptItem*>(concept_item.get()))
  {
    rate_concept->m_signal_request_rate_concept.connect(
      boost::bind(
        &QtPvdbNodeItem::OnItemRequestsRateConcept,
        this
      )
    );
    rate_concept->m_signal_request_rate_examples.connect(
      boost::bind(
        &QtPvdbNodeItem::OnItemRequestsRateExamples,
        this
      )
    );
  }

  assert(this->pos().x() == m_node->GetX());
  assert(this->pos().y() == m_node->GetY());
}

QRectF QtPvdbNodeItem::boundingRect() const
{
  //TRACE(m_concept_item->boundingRect().width());
  //TRACE(QtPvdbConceptMapItem::boundingRect().width());
  assert(m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
    && "Bounding rects must by synced");
  //return m_concept_item->boundingRect(); //.adjusted(-1.0,-1.0,1.0,1.0); //2013-01-25: Added adjusted
  return QtPvdbConceptMapItem::boundingRect(); //2013-05-20: Bypassed going via m_concept_item
}

QBrush QtPvdbNodeItem::brush() const
{
  return m_concept_item->brush();
}

void QtPvdbNodeItem::DisableAll()
{
  this->setEnabled(false);
  this->setVisible(false);
  this->m_concept_item->setEnabled(false);
  this->m_concept_item->setVisible(false);
}

void QtPvdbNodeItem::EnableAll()
{
  this->setEnabled(true);
  this->setVisible(true);
  this->m_concept_item->setEnabled(true);
  this->m_concept_item->setVisible(true);
}

void QtPvdbNodeItem::focusInEvent(QFocusEvent*)
{
  m_concept_item->SetContourPen(m_focus_pen); //Updates itself
  assert(!m_concept_item->hasFocus());
}

void QtPvdbNodeItem::focusOutEvent(QFocusEvent*)
{
  m_concept_item->SetContourPen(m_contour_pen); //Updates itself
  //m_signal_item_has_updated(0); //2013-01-20: causes Examples to get hidden //BUG
}

const boost::shared_ptr<const pvdb::Concept> QtPvdbNodeItem::GetConcept() const
{
  const boost::shared_ptr<const pvdb::Concept> p = m_node->GetConcept();
  assert(p);
  return p;
}

const boost::shared_ptr<pvdb::Concept> QtPvdbNodeItem::GetConcept()
{
  const boost::shared_ptr<pvdb::Concept> p = m_node->GetConcept();
  assert(p);
  return p;
}

void QtPvdbNodeItem::keyPressEvent(QKeyEvent *event)
{
  assert(m_concept_item);
  assert(m_concept_item->GetConcept());
  /*
  if (event->key() == Qt::Key_F2)
  {
    this->setEnabled(false);
    this->setVisible(false);
    assert(this);
    assert(GetConcept());
    this->GetConcept()->SetName( this->GetConcept()->GetName() + "*");
    this->setEnabled(true);
    this->setVisible(true);
  }
  */
  m_concept_item->keyPressEvent(event);
  switch (event->key())
  {
    case Qt::Key_F1:
    case Qt::Key_F2:
    return;
  }
  QtPvdbConceptMapItem::keyPressEvent(event);
}

void QtPvdbNodeItem::OnItemHasUpdated()
{
  this->setRect(m_concept_item->boundingRect());
  assert(m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
    && "Bounding rects must by synced");
  this->update();
  this->m_signal_item_has_updated(this);
}

void QtPvdbNodeItem::OnItemRequestsRateConcept()
{
  m_signal_node_requests_rate_concept(this);
}

void QtPvdbNodeItem::OnItemRequestsRateExamples()
{
  m_signal_node_requests_rate_examples(this);
}

void QtPvdbNodeItem::OnRequestsSceneUpdate()
{
  this->m_signal_request_scene_update();
}

void QtPvdbNodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
  this->m_concept_item->SetText(this->GetConcept()->GetName());

  assert(m_concept_item);
  assert(!m_concept_item->hasFocus());
  assert(!m_concept_item->isSelected());
  //assert(this->boundingRect() == m_concept_item->boundingRect()); //2013-01-25: Don't care

  m_concept_item->paint(painter,item,widget);

  //Check if item can move (as the center node cannot)
  if (this->flags() & QGraphicsItem::ItemIsMovable)
  {
    //Item can move, check for collision
    const QList<QGraphicsItem*> others = collidingItems();
    std::for_each(others.begin(),others.end(),
      [this](const QGraphicsItem* const other_item)
      {
        assert(other_item);
        if (const QtPvdbNodeItem* const other_node = dynamic_cast<const QtPvdbNodeItem*>(other_item))
        {
          const double dx = x() - other_node->x() > 0.0 ? 1.0 : -1.0;
          const double dy = y() - other_node->y() > 0.0 ? 1.0 : -1.0;
          //assert(this->flags() & QGraphicsItem::ItemIsMovable); //Not true for center node
          this->setPos( this->x()  + dx, this->y()  + dy);
        }
      }
    );
  }
}

void QtPvdbNodeItem::SetConcept(const boost::shared_ptr<pvdb::Concept> concept)
{
  this->m_node->SetConcept(concept);
}

void QtPvdbNodeItem::SetName(const std::string& name)
{
  m_node->GetConcept()->SetName(name);
}

#ifndef NDEBUG
void QtPvdbNodeItem::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test SetX and SetY being in sync
  {
    boost::shared_ptr<pvdb::Node> node = pvdb::NodeFactory::GetTests()
    boost::shared_ptr<QtPvdbNodeItem> qtnode(new QtPvdbNodeItem(node,qtconcept_item);
  }
}
#endif
