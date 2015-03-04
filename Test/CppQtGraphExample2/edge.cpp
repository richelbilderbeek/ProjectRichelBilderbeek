// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html
#include <QPainter>

#include "edge.h"
#include "node.h"

#include <boost/math/constants/constants.hpp>

Edge::Edge(Node * const sourceNode, Node * const destNode)
  :
    m_source_node{sourceNode},
    m_dest_node{destNode},
    m_source_point{0.0,0.0},
    m_dest_point{0.0,0.0},
    m_arrow_size{10.0}
{
  setAcceptedMouseButtons(0);
  m_source_node->addEdge(this);
  m_dest_node->addEdge(this);
  adjust();
}

Node * Edge::sourceNode() const noexcept
{
  return m_source_node;
}

Node * Edge::destNode() const noexcept
{
  return m_dest_node;
}

void Edge::adjust()
{
  if (!m_source_node || !m_dest_node) return;

  const QLineF line(mapFromItem(m_source_node, 0, 0), mapFromItem(m_dest_node, 0, 0));
  const double length{line.length()};

  prepareGeometryChange();

  if (length > 20.0)
  {
    const QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
    m_source_point = line.p1() + edgeOffset;
    m_dest_point = line.p2() - edgeOffset;
  }
  else
  {
    m_source_point = m_dest_point = line.p1();
  }
}

QRectF Edge::boundingRect() const
{
  if (!m_source_node || !m_dest_node) return QRectF();

  const double penWidth{1.0};
  const double extra{(penWidth + m_arrow_size) / 2.0};

  return QRectF(
    m_source_point,
    QSizeF(m_dest_point.x() - m_source_point.x(),
      m_dest_point.y() - m_source_point.y()
    )
  ).normalized()
   .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  if (!m_source_node || !m_dest_node) return;

  const double pi{boost::math::constants::pi<double>()};
  const double tau{boost::math::constants::two_pi<double>()};


  const QLineF line(m_source_point, m_dest_point);

  if (qFuzzyCompare(line.length(), 0.0)) return;

  // Draw the line itself
  painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->drawLine(line);

  // Draw the arrows
  double angle = std::acos(line.dx() / line.length());
  if (line.dy() >= 0) angle = tau - angle;

  using std::sin;
  using std::cos;
  const QPointF sourceArrowP1{m_source_point + QPointF(sin(angle + pi / 3.0) * m_arrow_size,cos(angle + pi / 3.0) * m_arrow_size)};
  const QPointF sourceArrowP2{m_source_point + QPointF(sin(angle + pi - pi / 3.0) * m_arrow_size,cos(angle + pi - pi / 3.0) * m_arrow_size)};
  const QPointF destArrowP1{m_dest_point + QPointF(sin(angle - pi / 3.0) * m_arrow_size,cos(angle - pi / 3.0) * m_arrow_size)};
  const QPointF destArrowP2{m_dest_point + QPointF(sin(angle - pi + pi / 3.0) * m_arrow_size,cos(angle - pi + pi / 3.0) * m_arrow_size)};

  painter->setBrush(Qt::black);
  painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
  painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
