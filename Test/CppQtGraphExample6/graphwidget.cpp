// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#include "graphwidget.h"
#include <cmath>

#include <boost/lambda/lambda.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "edge.h"
#include "node.h"
#include "popup.h"

GraphWidget::GraphWidget(QWidget *parent)
: QGraphicsView(parent),
  m_timer_id{0},
  m_focus_item{new PopUp} //Will be owned by scene
{
  QGraphicsScene * const scene = new QGraphicsScene(this);
  scene->addItem(m_focus_item); //Transfer ownership
  m_focus_item->setRect(-8.0,-8.0,16.0,16.0);
  m_focus_item->setVisible(false);

  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  //Make the scene infinitely large
  //scene->setSceneRect(-200, -200, 400, 400);
  setScene(scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(0.8, 0.8);
  setMinimumSize(400, 400);
  setWindowTitle(tr("Elastic Nodes"));

  std::vector<Node*> nodes;
  for (int y=-1; y!=2; ++y)
  {
    for (int x=-1; x!=2; ++x)
    {
      const auto node = createNode();
      node->setPos(static_cast<double>(x) * 50.0, static_cast<double>(y) * 50.0);
      nodes.push_back(node);
    }

  }
  //m_active_node = nodes[4];
  scene->addItem(new Edge(nodes[0],nodes[1]));
  scene->addItem(new Edge(nodes[0],nodes[3]));
  scene->addItem(new Edge(nodes[1],nodes[2]));
  scene->addItem(new Edge(nodes[1],nodes[4]));
  scene->addItem(new Edge(nodes[2],nodes[5]));
  scene->addItem(new Edge(nodes[3],nodes[4]));
  scene->addItem(new Edge(nodes[3],nodes[6]));
  scene->addItem(new Edge(nodes[4],nodes[5]));
  scene->addItem(new Edge(nodes[4],nodes[7]));
  scene->addItem(new Edge(nodes[5],nodes[8]));
  scene->addItem(new Edge(nodes[6],nodes[7]));
  scene->addItem(new Edge(nodes[7],nodes[8]));
  //m_active_node->setSelected(true);
}

Node* GraphWidget::createNode() noexcept
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
  m_focus_item->setVisible(true);
  m_focus_item->setPos(node->pos() + QPointF(25.0,-25.0));
}

void GraphWidget::OnNodeFocusOutEvent(Node* const node) noexcept
{
  assert(node);
  m_focus_item->setVisible(false);
}

void GraphWidget::OnNodePositionChangedEvent(Node* const node) noexcept
{
  assert(node);
  if (node->isSelected() || node->hasFocus())
  {
    m_focus_item->setPos(node->pos() + QPointF(25.0,-25.0));
  }
}

void GraphWidget::scaleView(qreal scaleFactor) noexcept
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
    if (node->advance())
    itemsMoved = true;
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
