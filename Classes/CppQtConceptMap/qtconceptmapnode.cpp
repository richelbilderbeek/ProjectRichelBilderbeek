#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapnode.h"

#include <cassert>
#include <climits>

#include <boost/lambda/lambda.hpp>
#include <boost/signals2.hpp>
#include <QKeyEvent>
#include <QPen>

#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapratestrategy.h"
#include "conceptmapconcept.h"
#include "qtitemdisplaystrategy.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtNode::QtNode(
  const boost::shared_ptr<ribi::cmap::Node> node,
  const boost::shared_ptr<QtItemDisplayStrategy> concept_item)
  : m_signal_node_requests_rate_concept{},
    m_signal_node_requests_rate_examples{},
    m_display_strategy(concept_item),
    m_contour_pen(concept_item->GetContourPen()),
    m_focus_pen(concept_item->GetFocusPen()),
    m_node(node)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(node);
  assert(m_display_strategy);
  assert(m_node);
  assert(m_display_strategy->GetConcept().get() == m_node->GetConcept().get());

  this->setAcceptHoverEvents(true);
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

  this->setRect(m_display_strategy->boundingRect());
  assert(m_display_strategy->boundingRect() == this->boundingRect()
    && "Bounding rects must by synced");
  //assert(m_concept_item->boundingRect() == QtConceptMapItem::boundingRect()
  //  && "Bounding rects must by synced");


  this->setPos(m_node->GetX(),m_node->GetY());
  assert(this->pos().x() == m_node->GetX());
  assert(this->pos().y() == m_node->GetY());
  m_display_strategy->SetPos(m_node->GetX(),m_node->GetY());

  m_display_strategy->m_signal_position_changed.connect(
    boost::bind(&ribi::cmap::QtNode::SetPos,this,boost::lambda::_1,boost::lambda::_2));

  m_node->m_signal_node_changed.connect(
    boost::bind(&ribi::cmap::QtNode::OnNodeChanged,this,boost::lambda::_1));

  m_display_strategy->m_signal_item_has_updated.connect(
    boost::bind(
      &ribi::cmap::QtNode::OnItemHasUpdated,this));

  m_display_strategy->m_signal_request_scene_update.connect(
    boost::bind(
      &ribi::cmap::QtNode::OnRequestsSceneUpdate,
      this
    )
  );

  if (QtEditStrategy * edit_concept = dynamic_cast<QtEditStrategy*>(concept_item.get()))
  {
    edit_concept->m_signal_request_edit.connect(
      boost::bind(
        &QtConceptMapElement::OnConceptRequestsEdit,
        this
      )
    );
  }

  if (QtRateStrategy * rate_concept = dynamic_cast<QtRateStrategy*>(concept_item.get()))
  {
    rate_concept->m_signal_request_rate_concept.connect(
      boost::bind(
        &ribi::cmap::QtNode::OnItemRequestsRateConcept,
        this
      )
    );
    rate_concept->m_signal_request_rate_examples.connect(
      boost::bind(
        &ribi::cmap::QtNode::OnItemRequestsRateExamples,
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
  assert(this->m_display_strategy->acceptHoverEvents()); //Must remove the 's' in Qt5?
}

QRectF ribi::cmap::QtNode::boundingRect() const
{
  //TRACE(m_concept_item->boundingRect().width());
  //TRACE(QtConceptMapItem::boundingRect().width());

  //Cannot check here
  //assert(m_concept_item->boundingRect() == QtConceptMapItem::boundingRect()
  //  && "Bounding rects must by synced");
  return m_display_strategy->boundingRect();
  //return QtConceptMapItem::boundingRect(); //2013-05-20: Bypassed going via m_concept_item
}

QBrush ribi::cmap::QtNode::brush() const
{
  return m_display_strategy->brush();
}

void ribi::cmap::QtNode::DisableAll()
{
  this->setEnabled(false);
  this->setVisible(false);
  this->m_display_strategy->setEnabled(false);
  this->m_display_strategy->setVisible(false);
}

void ribi::cmap::QtNode::EnableAll()
{
  this->setEnabled(true);
  this->setVisible(true);
  this->m_display_strategy->setEnabled(true);
  this->m_display_strategy->setVisible(true);
}

void ribi::cmap::QtNode::focusInEvent(QFocusEvent*)
{
  m_display_strategy->SetContourPen(m_focus_pen); //Updates itself
  assert(!m_display_strategy->hasFocus());
}

void ribi::cmap::QtNode::focusOutEvent(QFocusEvent*)
{
  m_display_strategy->SetContourPen(m_contour_pen); //Updates itself
  //m_signal_item_has_updated(0); //2013-01-20: causes Examples to get hidden //BUG
}

const boost::shared_ptr<const ribi::cmap::Concept> ribi::cmap::QtNode::GetConcept() const
{
  const boost::shared_ptr<const ribi::cmap::Concept> p = m_node->GetConcept();
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::cmap::Concept> ribi::cmap::QtNode::GetConcept()
{
  const boost::shared_ptr<ribi::cmap::Concept> p = m_node->GetConcept();
  assert(p);
  return p;
}

/*
void ribi::cmap::QtNode::hoverMoveEvent(QGraphicsSceneHoverEvent * e)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
  //m_concept_item->hoverMoveEvent(e);
  //Won't cause a hover, because the concept item
  //is not visible??
}
*/

void ribi::cmap::QtNode::keyPressEvent(QKeyEvent *event)
{
  assert(m_display_strategy);
  assert(m_display_strategy->GetConcept());
  m_display_strategy->keyPressEvent(event);
  switch (event->key())
  {
    case Qt::Key_F1:
    case Qt::Key_F2:
    return;
  }
  QtConceptMapElement::keyPressEvent(event);
}

void ribi::cmap::QtNode::OnItemHasUpdated()
{
  this->setRect(m_display_strategy->boundingRect());

  //Cannot check here, as setRect triggers this member function
  //assert(m_concept_item->boundingRect() == QtConceptMapItem::boundingRect()
  //  && "Bounding rects must by synced");
  this->update();
  this->m_signal_item_has_updated(this);
}

void ribi::cmap::QtNode::OnItemRequestsRateConcept()
{
  m_signal_node_requests_rate_concept(this);
}

void ribi::cmap::QtNode::OnItemRequestsRateExamples()
{
  m_signal_node_requests_rate_examples(this);
}

void ribi::cmap::QtNode::OnNodeChanged(const cmap::Node * node)
{
  assert(node);
  //Keep the coordinats synced
  this->SetPos(node->GetX(),node->GetY());
}

void ribi::cmap::QtNode::OnRequestsSceneUpdate()
{
  this->m_signal_request_scene_update();
}

void ribi::cmap::QtNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{

  assert(m_display_strategy);
  assert(!m_display_strategy->hasFocus());
  assert(!m_display_strategy->isSelected());

  this->m_display_strategy->SetName(this->GetConcept()->GetName());


  //Only QtEditStrategy actually modifies the position of the concept items
  if (dynamic_cast<QtEditStrategy*>(m_display_strategy.get()))
  {
    //Notifies the GUI-independent collaborators
    this->m_display_strategy->SetPos(x(),y());
  }

  assert(this->boundingRect() == m_display_strategy->boundingRect()
    && "Keep bounding rects in sync (but is this check still relevent?) 2013-07-06");

  m_display_strategy->paint(painter,item,widget);

  //Check if item can move (as the center node cannot)
  if (this->flags() & QGraphicsItem::ItemIsMovable)
  {
    //Item can move, check for collision
    const QList<QGraphicsItem*> others = collidingItems();
    std::for_each(others.begin(),others.end(),
      [this](const QGraphicsItem* const other_item)
      {
        assert(other_item);
        if (const QtNode* const other_node = dynamic_cast<const QtNode*>(other_item))
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

void ribi::cmap::QtNode::SetConcept(const boost::shared_ptr<ribi::cmap::Concept> concept)
{
  this->m_node->SetConcept(concept);
}

void ribi::cmap::QtNode::SetName(const std::string& name)
{
  m_node->GetConcept()->SetName(name);
}

void ribi::cmap::QtNode::SetX(const double x)
{
  #ifndef NDEBUG
  const double epsilon = 0.000001;
  #endif
  if ( x != this->pos().x()
    || x != GetNode()->GetX()
    || x != m_display_strategy->pos().x())
  {
    //Use Qt setX, otherwise an infinite recursion occurs
    this->setX(x);
    this->GetNode()->SetX(x);
    m_display_strategy->setX(x);
    assert(std::abs(x - this->pos().x()) < epsilon);
    assert(std::abs(x - GetNode()->GetX()) < epsilon);
    assert(std::abs(x - m_display_strategy->pos().x()) < epsilon);
  }
  assert(std::abs(x - this->pos().x()) < epsilon);
  assert(std::abs(x - GetNode()->GetX()) < epsilon);
  assert(std::abs(x - m_display_strategy->pos().x()) < epsilon);
}

void ribi::cmap::QtNode::SetY(const double y)
{
  #ifndef NDEBUG
  const double epsilon = 0.000001;
  #endif
  if ( y != this->pos().y()
    || y != GetNode()->GetY()
    || y != m_display_strategy->pos().y())
  {
    //Use Qt setY, otherwise an infinite recursion occurs
    this->setY(y);
    this->GetNode()->SetY(y);
    m_display_strategy->setY(y);
    assert(std::abs(y - this->pos().y()) < epsilon);
    assert(std::abs(y - GetNode()->GetY()) < epsilon);
    assert(std::abs(y - m_display_strategy->pos().y()) < epsilon);
  }
  assert(std::abs(y - this->pos().y()) < epsilon);
  assert(std::abs(y - GetNode()->GetY()) < epsilon);
  assert(std::abs(y - m_display_strategy->pos().y()) < epsilon);
}

#ifndef NDEBUG
void ribi::cmap::QtNode::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtNode::Test");

  //Test SetX and SetY being in sync
  {
    const std::size_t n_nodes = cmap::NodeFactory::GetTests().size();
    for (std::size_t node_index=0; node_index!=n_nodes; ++node_index)
    {
      const auto nodes = cmap::NodeFactory::GetTests();
      boost::shared_ptr<ribi::cmap::Node> node = nodes[node_index];
      assert(node);
      boost::shared_ptr<QtEditStrategy> qtconcept_item(new QtEditStrategy(node->GetConcept()));
      boost::shared_ptr<QtNode> qtnode(new QtNode(node,qtconcept_item));
      assert(qtconcept_item->GetConcept() == qtnode->GetConcept());
      assert(qtconcept_item->GetConcept() == node->GetConcept());
      assert(node == qtnode->GetNode());
      const double epsilon = 0.00001;
      {
        const double node_x = node->GetX();
        const double qtnode_x = qtnode->pos().x();
        const double qtconcept_item_x = qtnode->GetDisplayStrategy()->pos().x();
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
        const double qtconcept_item_y = qtnode->GetDisplayStrategy()->pos().y();
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
        const double qtconcept_item_x = qtnode->GetDisplayStrategy()->pos().x();
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
        const double qtconcept_item_y = qtnode->GetDisplayStrategy()->pos().y();
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
        const double qtconcept_item_x = qtnode->GetDisplayStrategy()->pos().x();
        assert(node_x == qtnode_x && qtnode_x == qtconcept_item_x
         && "X coordinat must be in sync");
        const double node_y = node->GetY();
        const double qtnode_y = qtnode->pos().y();
        const double qtconcept_item_y = qtnode->GetDisplayStrategy()->pos().y();
        assert(node_y == qtnode_y && qtnode_y == qtconcept_item_y
         && "Y coordinat must be in sync");
      }
      {
        const double new_x = -1234.5678;
        const double new_y = -8765.4321;
        //Change via Qt concept item
        qtnode->GetDisplayStrategy()->SetPos(new_x,new_y);

        const double node_x = node->GetX();
        const double qtnode_x = qtnode->pos().x();
        const double qtconcept_item_x = qtnode->GetDisplayStrategy()->pos().x();
        assert(
             std::abs(new_x - node_x) < epsilon
          && std::abs(new_x - qtnode_x) < epsilon
          && std::abs(new_x - qtconcept_item_x) < epsilon
          && "X coordinat must be in sync");
        const double node_y = node->GetY();
        const double qtnode_y = qtnode->pos().y();
        const double qtconcept_item_y = qtnode->GetDisplayStrategy()->pos().y();
        assert(
             std::abs(new_y - node_y) < epsilon
          && std::abs(new_y - qtnode_y) < epsilon
          && std::abs(new_y - qtconcept_item_y) < epsilon
          && "Y coordinat must be in sync");
      }
    }
  }
  TRACE("Finished ribi::cmap::QtNode::Test successfully");
}
#endif
