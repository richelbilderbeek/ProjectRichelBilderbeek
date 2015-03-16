// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html
#include "edge.h"


#include <QPainter>
#include <QStyleOption>
#include "node.h"

#include <boost/math/constants/constants.hpp>

Edge::Edge(
  Node * const source_node,
  Node * const center_node,
  Node * const dest_node
)
  :
    m_arrow_size{10.0},
    m_center_node{center_node},
    m_dest_node{dest_node},
    m_dest_point{0.0,0.0},
    m_show_bounding_rect{true},
    m_source_node{source_node},
    m_source_point{0.0,0.0}
{
  this->setFlags(
      ItemIsFocusable
    | ItemIsSelectable
  );
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

void Edge::adjust() noexcept
{
  if (!m_source_node || !m_dest_node) return;

  const QLineF line(mapFromItem(m_source_node, 0, 0), mapFromItem(m_dest_node, 0, 0));
  const double length{line.length()};

  //Keep the center node in the center
  m_center_node->setPos(
    (m_source_node->pos() + m_dest_node->pos()) / 2.0
  );

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

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget *)
{
  if (!m_source_node || !m_dest_node) return;

  const double pi{boost::math::constants::pi<double>()};
  const double tau{boost::math::constants::two_pi<double>()};


  const QLineF line(m_source_point, m_dest_point);

  if (qFuzzyCompare(line.length(), 0.0)) return;

  // Draw the line itself
  const bool is_selected{option->state & QStyle::State_Sunken || isSelected()};
  painter->setPen(
    QPen(
      Qt::black,
      1.0,
      is_selected ? Qt::DashLine : Qt::SolidLine,
      Qt::RoundCap,
      Qt::RoundJoin
    )
  );
  painter->drawLine(line);

  painter->setPen(
    QPen(
      Qt::black,
      1.0,
      Qt::SolidLine, //The point must be drawn with solidLine
      Qt::RoundCap,
      Qt::RoundJoin
    )
  );

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

  //Draw the bounding rectangle
  if (m_show_bounding_rect)
  {
    painter->setBrush(QBrush(QColor(0,0,255,32)));
    painter->setPen(QPen(QColor(0,0,255,64)));
    painter->drawRect(this->boundingRect());
  }
}
