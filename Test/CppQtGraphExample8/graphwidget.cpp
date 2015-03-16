// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#include "graphwidget.h"
#include <cmath>

#include <boost/lambda/lambda.hpp>

#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "edge.h"
#include "node.h"
#include "popup.h"

GraphWidget::GraphWidget(QWidget *parent)
: QGraphicsView(parent),
  m_timer_id{0},
  m_popup{new PopUp} //Will be owned by scene
{
  QGraphicsScene * const scene = new QGraphicsScene(this);
  scene->addItem(m_popup); //Transfer ownership
  m_popup->setVisible(false);
  m_popup->m_signal_clicked.connect(
    boost::bind(&GraphWidget::OnPopUpClicked,this, boost::lambda::_1)
  );

  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  setScene(scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(3.0,3.0);

  std::vector<Node*> nodes;
  for (int y=-1; y!=2; ++y)
  {
    for (int x=-1; x!=2; ++x)
    {
      const auto node = CreateNode();
      node->setPos(static_cast<double>(x) * 50.0, static_cast<double>(y) * 50.0);
      nodes.push_back(node);
    }

  }
  /*
  scene->addItem(new Edge(nodes[0],nodes[1],this));
  scene->addItem(new Edge(nodes[0],nodes[3],this));
  scene->addItem(new Edge(nodes[1],nodes[2],this));
  scene->addItem(new Edge(nodes[1],nodes[4],this));
  scene->addItem(new Edge(nodes[2],nodes[5],this));
  scene->addItem(new Edge(nodes[3],nodes[4],this));
  scene->addItem(new Edge(nodes[3],nodes[6],this));
  scene->addItem(new Edge(nodes[4],nodes[5],this));
  scene->addItem(new Edge(nodes[4],nodes[7],this));
  scene->addItem(new Edge(nodes[5],nodes[8],this));
  scene->addItem(new Edge(nodes[6],nodes[7],this));
  scene->addItem(new Edge(nodes[7],nodes[8],this));
  */

  CreateEdge(nodes[0],nodes[1]);
  CreateEdge(nodes[0],nodes[3]);
  CreateEdge(nodes[1],nodes[2]);
  CreateEdge(nodes[1],nodes[4]);
  CreateEdge(nodes[2],nodes[5]);
  CreateEdge(nodes[3],nodes[4]);
  CreateEdge(nodes[3],nodes[6]);
  CreateEdge(nodes[4],nodes[5]);
  CreateEdge(nodes[4],nodes[7]);
  CreateEdge(nodes[5],nodes[8]);
  CreateEdge(nodes[6],nodes[7]);
  CreateEdge(nodes[7],nodes[8]);

  {
    //Put the dialog, at size 80%, in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

Edge* GraphWidget::CreateEdge(
  Node * const from_node,
  Node * const to_node
) noexcept
{
  assert(from_node);
  assert(to_node);
  Node * const center_node = CreateNode();
  center_node->setPos(
    (from_node->pos() + to_node->pos()) / 2.0
  );
  center_node->SetRay(center_node->GetRay() / 2.0);
  center_node->SetHasShadow(false);

  Edge * const new_edge{new Edge(from_node,center_node,to_node)};
  new_edge->setZValue(-2.0);
  /*
  new_node->m_signal_focus_in.connect(
    boost::bind(&GraphWidget::OnNodeFocusInEvent,this, boost::lambda::_1)
  );
  new_node->m_signal_focus_out.connect(
    boost::bind(&GraphWidget::OnNodeFocusOutEvent,this, boost::lambda::_1)
  );
  new_node->m_signal_position_changed.connect(
    boost::bind(&GraphWidget::OnNodePositionChangedEvent,this, boost::lambda::_1)
  );
  */
  this->scene()->addItem(new_edge);
  return new_edge;
}

Node* GraphWidget::CreateNode() noexcept
{
  Node * const new_node{new Node(this)};
  new_node->m_signal_focus_in.connect(
    boost::bind(&GraphWidget::OnNodeFocusInEvent,this, boost::lambda::_1)
  );
  new_node->m_signal_focus_out.connect(
    boost::bind(&GraphWidget::OnNodeFocusOutEvent,this, boost::lambda::_1)
  );
  new_node->m_signal_position_changed.connect(
    boost::bind(&GraphWidget::OnNodePositionChangedEvent,this, boost::lambda::_1)
  );
  this->scene()->addItem(new_node);
  return new_node;
}

void GraphWidget::itemMoved() noexcept
{
  if (!m_timer_id)
  {
    m_timer_id = startTimer(1000 / 25);
  }
}

void GraphWidget::keyPressEvent(QKeyEvent *event) noexcept
{
  std::vector<Node*> nodes;
  foreach(QGraphicsItem * const item, scene()->selectedItems())
  {
    Node * const node{dynamic_cast<Node*>(item)};
    if (node) nodes.push_back(node);
  }

  switch (event->key())
  {
    case Qt::Key_Up:
    {
      foreach(Node * const node, nodes) { node->moveBy(0.0,-20.0); }
    }
    break;
    case Qt::Key_Down:
    {
      foreach(Node * const node, nodes) { node->moveBy(0.0,20.0); }
    }
    break;
    case Qt::Key_Left:
    {
      foreach(Node * const node, nodes) { node->moveBy(-20.0,0.0); }
    }
    break;
    case Qt::Key_Right:
    {
      foreach(Node * const node, nodes) { node->moveBy(20,0); }
    }
    break;
    case Qt::Key_Plus:
      zoomIn();
    break;
    case Qt::Key_Minus:
      zoomOut();
    break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
      shuffle();
    break;
    default:
      QGraphicsView::keyPressEvent(event);
  }
}

void GraphWidget::OnNodeFocusInEvent(Node* const node) noexcept
{
  assert(node);
  m_popup->StartFadeIn();
  m_popup->SetNode(node);
  m_popup->setPos(node->pos() + QPointF(25.0,-25.0));
}

void GraphWidget::OnNodeFocusOutEvent(Node* const node) noexcept
{
  assert(node);
  m_popup->StartFadeOut();
  //m_popup->setVisible(false);
}

void GraphWidget::OnNodePositionChangedEvent(Node* const node) noexcept
{
  assert(node);
  if (node->isSelected() || node->hasFocus())
  {
    m_popup->setPos(node->pos() + QPointF(25.0,-25.0));
  }
}

void GraphWidget::OnPopUpClicked(PopUp* const popup) noexcept
{
  const auto node = popup->GetNode();
  if (node)
  {
    node->SetRay(node->GetRay() * 2.0);

    //It might be that the node has increased in size
    //that much, that it collides with another object.
    //itemMoved takes care of handling this collision
    this->itemMoved();
  }
}

void GraphWidget::scaleView(const double scaleFactor) noexcept
{
  const double factor{
    transform().scale(scaleFactor, scaleFactor)
      .mapRect(QRectF(0.0, 0.0, 1.0, 1.0)).width()
  };
  if (factor < 0.07 || factor > 100.0) return;

  scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle() noexcept
{
  foreach (QGraphicsItem * const item, scene()->items())
  {
    if (qgraphicsitem_cast<Node *>(item))
    {
      item->setPos(
        static_cast<double>(-150 + (qrand() % 300)),
        static_cast<double>(-150 + (qrand() % 300))
      );
    }
  }
}

void GraphWidget::timerEvent(QTimerEvent *) noexcept
{
  QList<Node *> nodes;
  foreach (QGraphicsItem *item, scene()->items())
  {
    if (Node * const node = qgraphicsitem_cast<Node *>(item))
    {
      nodes << node;
    }
  }
  foreach (Node * const node, nodes)
  {
    node->calculateForces();
  }

  bool itemsMoved = false;
  foreach (Node * const node, nodes)
  {
    if (node->advance()) itemsMoved = true;
  }

  if (!itemsMoved)
  {
    killTimer(m_timer_id);
    m_timer_id = 0;
  }
}

void GraphWidget::wheelEvent(QWheelEvent *event) noexcept
{
  scaleView(std::pow(2.0, -event->delta() / 240.0));
}

void GraphWidget::zoomIn() noexcept
{
  scaleView(1.2);
}

void GraphWidget::zoomOut() noexcept
{
  scaleView(1.0/1.2);
}
