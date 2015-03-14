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
    m_signal_focus_in{},
    m_signal_focus_out{},
    m_signal_position_changed{},
    m_edges{},
    m_graph(graphWidget),
    m_new_pos{},
    m_ray{10.0},
    m_show_bounding_rect{false}
{
  setFlag(ItemIsMovable);
  setFlag(ItemIsFocusable);
  setFlag(ItemIsSelectable);
  setFlag(ItemSendsGeometryChanges);
  setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
}

void Node::addEdge(Edge *edge) noexcept
{
  m_edges << edge;
  edge->adjust();
}

bool Node::advance() noexcept
{
  if (m_new_pos == pos()) return false;

  setPos(m_new_pos);
  return true;
}

QRectF Node::boundingRect() const noexcept
{
  const double adjust{2.0};
  return QRectF(
    -m_ray - adjust,
    -m_ray - adjust,
     (2.0 * m_ray) + 3.0 + adjust,
     (2.0 * m_ray) + 3.0 + adjust
   );
}

void Node::calculateForces() noexcept
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

QList<Edge *> Node::edges() const noexcept
{
  return m_edges;
}

void Node::focusInEvent(QFocusEvent *) noexcept
{
  m_signal_focus_in(this);
}

void Node::focusOutEvent(QFocusEvent *) noexcept
{
  m_signal_focus_out(this);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) noexcept
{
  switch (change) {
    case ItemPositionHasChanged:
    {
      foreach (Edge *edge, m_edges)
      edge->adjust();
      m_graph->itemMoved();
      m_signal_position_changed(this);
    }
    break;
    default:
    break;
  }

  return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) noexcept
{
  update();
  QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) noexcept
{
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) noexcept
{
  //Draw the shadow
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::darkGray);
  painter->drawEllipse(-m_ray + 3.0,-m_ray + 3.0, 2.0 * m_ray, 2.0 * m_ray);

  QRadialGradient gradient(-3, -3, 10);

  const bool is_selected{option->state & QStyle::State_Sunken
    || this->isSelected() };
  if (is_selected)
  {
    gradient.setCenter(3, 3);
    gradient.setFocalPoint(3, 3);
    gradient.setColorAt(1, QColor(Qt::lightGray).light(120));
    gradient.setColorAt(0, QColor(Qt::darkGray).light(120));
  }
  else
  {
    gradient.setColorAt(0, Qt::lightGray);
    gradient.setColorAt(1, Qt::darkGray);
  }
  painter->setBrush(gradient);

  painter->setPen(
    QPen(
      Qt::black,
      1.0, //pen width
      is_selected ? Qt::DashLine : Qt::SolidLine
    )
  );
  painter->drawEllipse(-m_ray, -m_ray, 2.0 * m_ray, 2.0 * m_ray);

  //Draw the bounding rectangle
  if (m_show_bounding_rect)
  {
    painter->setBrush(QBrush(QColor(255,0,0,32)));
    painter->setPen(QPen(QColor(255,0,0,64)));
    painter->drawRect(this->boundingRect());
  }
}

void Node::SetRay(const double ray)
{
  m_ray = ray;
  this->update();
}

QPainterPath Node::shape() const noexcept
{
  QPainterPath path;
  path.addEllipse(-m_ray, -m_ray, 2.0*m_ray, 2.0*m_ray);
  return path;
}


