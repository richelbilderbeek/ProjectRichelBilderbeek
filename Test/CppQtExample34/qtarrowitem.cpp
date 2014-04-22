#include <cassert>
#include <cmath>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>

#include "qtarrowitem.h"
#pragma GCC diagnostic pop

const double QtArrowItem::m_click_easy_width = 10.0;

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
  assert(this->line().p1() == QPointF(x1,y1));
  assert(this->line().p2() == QPointF(x2,y2));
}

double QtArrowItem::GetAngle(const double dx, const double dy)
{
  return boost::math::constants::pi<double>() - (std::atan(dx/dy));
}

QRectF QtArrowItem::boundingRect() const
{
  return shape().boundingRect();
}

void QtArrowItem::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_F1:
    case Qt::Key_1:
    case Qt::Key_T:
    case Qt::Key_Minus:
      m_tail = !m_tail;
      this->update();
      break;
    case Qt::Key_F2:
    case Qt::Key_2:
    case Qt::Key_H:
    case Qt::Key_Plus:
      m_head = !m_head;
      this->update();
      break;
    default:
      break;
  }
}

void QtArrowItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->modifiers() & Qt::ShiftModifier)
  {
    if ((event->pos() - this->line().p1()).manhattanLength() < 10.0)
    {
      m_tail = !m_tail;
      this->update();
    }
    else if ((event->pos() - this->line().p2()).manhattanLength() < 10.0)
    {
      m_head = !m_head;
      this->update();
    }
  }
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
  if (m_tail)
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
  if (m_head)
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

QPainterPath QtArrowItem::shape() const
{
  //Thanks to norobro for posting this code at
  //http://www.qtcentre.org/threads/49201-Increase-margin-for-detecting-tooltip-events-of-QGraphicsLineItem
  QPainterPath path;
  QPainterPathStroker stroker;
  path.moveTo(line().p1());
  path.lineTo(line().p2());
  stroker.setWidth(m_click_easy_width);
  return stroker.createStroke(path);
}

