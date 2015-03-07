// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <QtGui>

#include <math.h>

GraphWidget::GraphWidget(QWidget *parent)
: QGraphicsView(parent),
  m_timer_id{0},
  m_active_node{new Node(this)}
{
  QGraphicsScene * const scene = new QGraphicsScene(this);
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
  m_active_node = nodes[4];
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

}

Node* GraphWidget::createNode() noexcept
{
  Node * const new_node{new Node(this)};
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
  switch (event->key())
  {
    case Qt::Key_Up:
      m_active_node->moveBy(0, -20);
    break;
    case Qt::Key_Down:
      m_active_node->moveBy(0, 20);
    break;
    case Qt::Key_Left:
      m_active_node->moveBy(-20, 0);
    break;
    case Qt::Key_Right:
      m_active_node->moveBy(20, 0);
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

void GraphWidget::zoomIn() noexcept
{
  scaleView(1.2);
}

void GraphWidget::zoomOut() noexcept
{
  scaleView(1.0/1.2);
}
