#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbnodeitem.h"

#include <cassert>
#include <climits>

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
  #ifndef NDEBUG
  Test();
  #endif
  assert(node);
  assert(m_concept_item);
  assert(m_node);
  assert(m_concept_item->GetConcept().get() == m_node->GetConcept().get());

  this->setAcceptHoverEvents(true);
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

  this->setRect(m_concept_item->boundingRect());
  assert(m_concept_item->boundingRect() == this->boundingRect()
    && "Bounding rects must by synced");
  //assert(m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
  //  && "Bounding rects must by synced");


  this->setPos(m_node->GetX(),m_node->GetY());
  assert(this->pos().x() == m_node->GetX());
  assert(this->pos().y() == m_node->GetY());
  m_concept_item->SetPos(m_node->GetX(),m_node->GetY());

  m_concept_item->m_signal_position_changed.connect(
    boost::bind(&QtPvdbNodeItem::SetPos,this,boost::lambda::_1,boost::lambda::_2));

  m_node->m_signal_node_changed.connect(
    boost::bind(&QtPvdbNodeItem::OnNodeChanged,this,boost::lambda::_1));

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

  assert(flags() & QGraphicsItem::ItemIsFocusable);
  assert(flags() & QGraphicsItem::ItemIsSelectable);
  assert(flags() & QGraphicsItem::ItemIsMovable);
  assert(this->pos().x() == m_node->GetX());
  assert(this->pos().y() == m_node->GetY());
  assert(this->acceptHoverEvents()); //Must remove the 's' in Qt5?
  assert(this->m_concept_item->acceptHoverEvents()); //Must remove the 's' in Qt5?
}

QRectF QtPvdbNodeItem::boundingRect() const
{
  //TRACE(m_concept_item->boundingRect().width());
  //TRACE(QtPvdbConceptMapItem::boundingRect().width());

  //Cannot check here
  //assert(m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
  //  && "Bounding rects must by synced");
  return m_concept_item->boundingRect();
  //return QtPvdbConceptMapItem::boundingRect(); //2013-05-20: Bypassed going via m_concept_item
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

  //Cannot check here, as setRect triggers this member function
  //assert(m_concept_item->boundingRect() == QtPvdbConceptMapItem::boundingRect()
  //  && "Bounding rects must by synced");
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

void QtPvdbNodeItem::OnNodeChanged(const pvdb::Node * node)
{
  //Keep the coordinats synced
  this->SetPos(node->GetX(),node->GetY());
}

void QtPvdbNodeItem::OnRequestsSceneUpdate()
{
  this->m_signal_request_scene_update();
}

void QtPvdbNodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{

  assert(m_concept_item);
  assert(!m_concept_item->hasFocus());
  assert(!m_concept_item->isSelected());

  this->m_concept_item->SetText(this->GetConcept()->GetName());


  //Only QtPvdbEditConceptItem actually modifies the position of the concept items
  if (dynamic_cast<QtPvdbEditConceptItem*>(m_concept_item.get()))
  {
    //Notifies the GUI-independent collaborators
    this->m_concept_item->SetPos(x(),y());
  }

  assert(this->boundingRect() == m_concept_item->boundingRect()
    && "Keep bounding rects in sync (but is this check still relevent?) 2013-07-06");

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

void QtPvdbNodeItem::SetX(const double x)
{
  #ifndef NDEBUG
  const double epsilon = 0.000001;
  #endif
  if ( x != this->pos().x()
    || x != GetNode()->GetX()
    || x != m_concept_item->pos().x())
  {
    //Use Qt setX, otherwise an infinite recursion occurs
    this->setX(x);
    this->GetNode()->SetX(x);
    m_concept_item->setX(x);
    assert(std::abs(x - this->pos().x()) < epsilon);
    assert(std::abs(x - GetNode()->GetX()) < epsilon);
    assert(std::abs(x - m_concept_item->pos().x()) < epsilon);
  }
  assert(std::abs(x - this->pos().x()) < epsilon);
  assert(std::abs(x - GetNode()->GetX()) < epsilon);
  assert(std::abs(x - m_concept_item->pos().x()) < epsilon);
}

void QtPvdbNodeItem::SetY(const double y)
{
  #ifndef NDEBUG
  const double epsilon = 0.000001;
  #endif
  if ( y != this->pos().y()
    || y != GetNode()->GetY()
    || y != m_concept_item->pos().y())
  {
    //Use Qt setY, otherwise an infinite recursion occurs
    this->setY(y);
    this->GetNode()->SetY(y);
    m_concept_item->setY(y);
    assert(std::abs(y - this->pos().y()) < epsilon);
    assert(std::abs(y - GetNode()->GetY()) < epsilon);
    assert(std::abs(y - m_concept_item->pos().y()) < epsilon);
  }
  assert(std::abs(y - this->pos().y()) < epsilon);
  assert(std::abs(y - GetNode()->GetY()) < epsilon);
  assert(std::abs(y - m_concept_item->pos().y()) < epsilon);
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
    const std::size_t n_nodes = pvdb::NodeFactory::GetTests().size();
    for (std::size_t node_index=0; node_index!=n_nodes; ++node_index)
    {
      const auto nodes = pvdb::NodeFactory::GetTests();
      boost::shared_ptr<pvdb::Node> node = nodes[node_index];
      assert(node);
      boost::shared_ptr<QtPvdbConceptItem> qtconcept_item(new QtPvdbEditConceptItem(node->GetConcept()));
      boost::shared_ptr<QtPvdbNodeItem> qtnode(new QtPvdbNodeItem(node,qtconcept_item));
      assert(qtconcept_item->GetConcept() == qtnode->GetConcept());
      assert(qtconcept_item->GetConcept() == node->GetConcept());
      assert(node == qtnode->GetNode());
      const double epsilon = 0.00001;
      {
        const double node_x = node->GetX();
        const double qtnode_x = qtnode->pos().x();
        const double qtconcept_item_x = qtnode->GetConceptItem()->pos().x();
        if (!(node_x == qtnode_x && qtnode_x == qtconcept_item_x))
        {
          TRACE(node_x);
          TRACE(qtnode_x);
          TRACE(qtconcept_item_x);
        }

        assert(node_x == qtnode_x && qtnode_x == qtconcept_item_x
         && "X coordinat must be in sync");
        const double node_y = node->GetY();
        const double qtnode_y = qtnode->pos().y();
        const double qtconcept_item_y = qtnode->GetConceptItem()->pos().y();
        assert(node_y == qtnode_y && qtnode_y == qtconcept_item_y
         && "Y coordinat must be in sync");
      }
      {
        const double new_x = 12.34;
        const double new_y = 43.21;

        //Change via node
        assert(node);
        node->SetX(new_x);
        node->SetY(new_y);

        const double node_x = node->GetX();
        const double qtnode_x = qtnode->pos().x();
        const double qtconcept_item_x = qtnode->GetConceptItem()->pos().x();
        if (!(node_x == qtnode_x && qtnode_x == qtconcept_item_x))
        {
          TRACE(node_x);
          TRACE(qtnode_x);
          TRACE(qtconcept_item_x);
        }
        assert(node_x == qtnode_x && qtnode_x == qtconcept_item_x
         && "X coordinat must be in sync");
        const double node_y = node->GetY();
        const double qtnode_y = qtnode->pos().y();
        const double qtconcept_item_y = qtnode->GetConceptItem()->pos().y();
        assert(node_y == qtnode_y && qtnode_y == qtconcept_item_y
         && "Y coordinat must be in sync");
      }
      {
        const double new_x = 123.456;
        const double new_y = 654.321;

        //Change via Qt node
        qtnode->SetPos(new_x,new_y);

        const double node_x = node->GetX();
        const double qtnode_x = qtnode->pos().x();
        const double qtconcept_item_x = qtnode->GetConceptItem()->pos().x();
        assert(node_x == qtnode_x && qtnode_x == qtconcept_item_x
         && "X coordinat must be in sync");
        const double node_y = node->GetY();
        const double qtnode_y = qtnode->pos().y();
        const double qtconcept_item_y = qtnode->GetConceptItem()->pos().y();
        assert(node_y == qtnode_y && qtnode_y == qtconcept_item_y
         && "Y coordinat must be in sync");
      }
      {
        const double new_x = -1234.5678;
        const double new_y = -8765.4321;
        //Change via Qt concept item
        qtnode->GetConceptItem()->SetPos(new_x,new_y);

        const double node_x = node->GetX();
        const double qtnode_x = qtnode->pos().x();
        const double qtconcept_item_x = qtnode->GetConceptItem()->pos().x();
        assert(
             std::abs(new_x - node_x) < epsilon
          && std::abs(new_x - qtnode_x) < epsilon
          && std::abs(new_x - qtconcept_item_x) < epsilon
          && "X coordinat must be in sync");
        const double node_y = node->GetY();
        const double qtnode_y = qtnode->pos().y();
        const double qtconcept_item_y = qtnode->GetConceptItem()->pos().y();
        assert(
             std::abs(new_y - node_y) < epsilon
          && std::abs(new_y - qtnode_y) < epsilon
          && std::abs(new_y - qtconcept_item_y) < epsilon
          && "Y coordinat must be in sync");
      }
    }
  }
}
#endif
