#include <cmath>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>
#include <QPainter>
#include "qtarrowitem.h"
#pragma GCC diagnostic pop

QtArrowItem::QtArrowItem(
  const double x1,
  const double y1,
  const bool tail,
  const double x2,
  const double y2,
  const bool head,
  QGraphicsItem *parent)
  : QGraphicsLineItem(x1,y1,x2,y2,parent),
    m_head(head),
    m_tail(tail)
{
  this->setFlag(QGraphicsItem::ItemIsMovable);
  this->setFlag(QGraphicsItem::ItemIsSelectable);
}

double QtArrowItem::GetAngle(const double dx, const double dy)
{
  return boost::math::constants::pi<double>() - (std::atan(dx/dy));
}

QPainterPath QtArrowItem::shape() const
{
  //Thanks to norobro for posting this code at 
  //http://www.qtcentre.org/threads/49201-Increase-margin-for-detecting-tooltip-events-of-QGraphicsLineItem
  QPainterPath path;
  QPainterPathStroker stroker;
  path.moveTo(line().p1());
  path.lineTo(line().p2());
  stroker.setWidth(10);
  return stroker.createStroke(path);
}

QRectF QtArrowItem::boundingRect() const
{
  return shape().boundingRect();
}

void QtArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->setRenderHint(QPainter::Antialiasing);
  if (this->isSelected())
  {
    const QColor color(255,0,0);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
  }
  else
  {
    const QColor color(0,0,0);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(1);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
  }
  painter->drawLine(this->line());

  //The angle from tail to head
  double angle = GetAngle(line().dx(),line().dy());
  if (line().dy() >= 0.0) angle = (1.0 * boost::math::constants::pi<double>()) + angle;
  const double sz = 10.0; //pixels
  {
    const QPointF p0 = this->line().p1();
    const QPointF p1
      = p0 + QPointF(
         std::sin(angle + boost::math::constants::pi<double>() + (boost::math::constants::pi<double>() * 0.1)) * sz,
        -std::cos(angle + boost::math::constants::pi<double>() + (boost::math::constants::pi<double>() * 0.1)) * sz);
    const QPointF p2
      = p0 + QPointF(
         std::sin(angle + boost::math::constants::pi<double>() - (boost::math::constants::pi<double>() * 0.1)) * sz,
        -std::cos(angle + boost::math::constants::pi<double>() - (boost::math::constants::pi<double>() * 0.1)) * sz);
    painter->drawPolygon(QPolygonF() << p0 << p1 << p2);
  }
  {
    const QPointF p0 = this->line().p2();

    const QPointF p1
      = p0 + QPointF(
         std::sin(angle +  0.0 + (boost::math::constants::pi<double>() * 0.1)) * sz,
        -std::cos(angle +  0.0 + (boost::math::constants::pi<double>() * 0.1)) * sz);
    const QPointF p2
      = p0 + QPointF(
         std::sin(angle +  0.0 - (boost::math::constants::pi<double>() * 0.1)) * sz,
        -std::cos(angle +  0.0 - (boost::math::constants::pi<double>() * 0.1)) * sz);

    painter->drawPolygon(QPolygonF() << p0 << p1 << p2);
  }
}
