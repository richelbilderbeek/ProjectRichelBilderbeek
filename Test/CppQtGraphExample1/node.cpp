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
  if (!scene() || scene()->mouseGrabberItem() == this) {
    m_new_pos = pos();
    return;
  }

  // Sum up all forces pushing this item away
  qreal xvel = 0;
  qreal yvel = 0;
  foreach (QGraphicsItem *item, scene()->items()) {
    Node *node = qgraphicsitem_cast<Node *>(item);

    if (!node) continue;

    QPointF vec = mapToItem(node, 0, 0);
    qreal dx = vec.x();
    qreal dy = vec.y();
    double l = 2.0 * (dx * dx + dy * dy);
    if (l > 0) {
      xvel += (dx * 150.0) / l;
      yvel += (dy * 150.0) / l;
    }
  }

  // Now subtract all forces pulling items together
  double weight = (m_edges.size() + 1) * 10;
  foreach (Edge *edge, m_edges) {
    QPointF vec;
    if (edge->sourceNode() == this)
    vec = mapToItem(edge->destNode(), 0, 0);
    else
    vec = mapToItem(edge->sourceNode(), 0, 0);
    xvel -= vec.x() / weight;
    yvel -= vec.y() / weight;
  }

  if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
  {
    xvel = yvel = 0;
  }

  QRectF sceneRect = scene()->sceneRect();
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
  #if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
  // Add some extra space around the circle for easier touching with finger
  qreal adjust = 30;
  return QRectF( -10 - adjust, -10 - adjust,
  20 + adjust * 2, 20 + adjust * 2);
  #else
  qreal adjust = 2;
  return QRectF( -10 - adjust, -10 - adjust,
  23 + adjust, 23 + adjust);
  #endif
}

QPainterPath Node::shape() const
{
  QPainterPath path;
  #if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
  // Add some extra space around the circle for easier touching with finger
  path.addEllipse( -40, -40, 80, 80);
  #else
  path.addEllipse(-10, -10, 20, 20);
  #endif
  return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::darkGray);
  painter->drawEllipse(-7, -7, 20, 20);

  QRadialGradient gradient(-3, -3, 10);
  if (option->state & QStyle::State_Sunken) {
    gradient.setCenter(3, 3);
    gradient.setFocalPoint(3, 3);
    gradient.setColorAt(1, QColor(Qt::yellow).light(120));
    gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
  } else {
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
  foreach (Edge *edge, m_edges)
  edge->adjust();
  m_graph->itemMoved();
  break;
  default:
  break;
  };

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
