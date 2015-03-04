// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "edge.h"
#include "node.h"
#include "graphwidget.h"

Node::Node(GraphWidget *graphWidget)
  :
    m_edges{},
    m_new_pos{},
    m_graph(graphWidget)
{
  setFlag(ItemIsMovable);
  setFlag(ItemSendsGeometryChanges);
  setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
}

void Node::addEdge(Edge *edge)
{
  m_edges << edge;
  edge->adjust();
}

QList<Edge *> Node::edges() const
{
  return m_edges;
}

void Node::calculateForces()
{
  if (!scene() || scene()->mouseGrabberItem() == this)
  {
    m_new_pos = pos();
    return;
  }

  // Sum up all forces pushing this item away
  double xvel = 0.0;
  double yvel = 0.0;
  foreach (QGraphicsItem *item, scene()->items())
  {
    Node * const node = qgraphicsitem_cast<Node *>(item);

    if (!node) continue;

    const QPointF vec{mapToItem(node, 0.0, 0.0)};
    const double dx{vec.x()};
    const double dy{vec.y()};
    const double l{2.0 * (dx * dx + dy * dy)};
    if (l > 0.0)
    {
      xvel += (dx * 150.0) / l;
      yvel += (dy * 150.0) / l;
    }
  }

  // Now subtract all forces pulling items together
  const double weight = static_cast<double>(m_edges.size() + 1) * 10.0;
  foreach (Edge *edge, m_edges)
  {
    const QPointF vec
      = edge->sourceNode() == this
      ? mapToItem(edge->destNode(), 0, 0)
      : mapToItem(edge->sourceNode(), 0, 0)
    ;
    xvel -= vec.x() / weight;
    yvel -= vec.y() / weight;
  }

  if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
  {
    xvel = yvel = 0.0;
  }

  const QRectF sceneRect = scene()->sceneRect();
  m_new_pos = pos() + QPointF(xvel, yvel);
  m_new_pos.setX(qMin(qMax(m_new_pos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
  m_new_pos.setY(qMin(qMax(m_new_pos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}

bool Node::advance()
{
  if (m_new_pos == pos()) return false;

  setPos(m_new_pos);
  return true;
}

QRectF Node::boundingRect() const
{
  const double adjust{2.0};
  return QRectF(
    -10.0 - adjust,
    -10.0 - adjust,
     23.0 + adjust,
     23.0 + adjust
   );
}

QPainterPath Node::shape() const
{
  QPainterPath path;
  path.addEllipse(-10.0, -10.0, 20.0, 20.0);
  return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::darkGray);
  painter->drawEllipse(-7, -7, 20, 20);

  QRadialGradient gradient(-3, -3, 10);
  if (option->state & QStyle::State_Sunken)
  {
    gradient.setCenter(3, 3);
    gradient.setFocalPoint(3, 3);
    gradient.setColorAt(1, QColor(Qt::yellow).light(120));
    gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
  }
  else
  {
    gradient.setColorAt(0, Qt::yellow);
    gradient.setColorAt(1, Qt::darkYellow);
  }
  painter->setBrush(gradient);

  painter->setPen(QPen(Qt::black, 0));
  painter->drawEllipse(-10, -10, 20, 20);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
  switch (change) {
    case ItemPositionHasChanged:
    {
      foreach (Edge *edge, m_edges)
      edge->adjust();
      m_graph->itemMoved();
    }
    break;
    default:
    break;
  }

  return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  update();
  QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}
