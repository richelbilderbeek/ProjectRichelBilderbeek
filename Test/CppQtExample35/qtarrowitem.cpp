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
  const double tail_x,
  const double tail_y,
  const bool tail,
  const double mid_x,
  const double mid_y,
  const bool head,
  const double head_x,
  const double head_y,
  QGraphicsItem *parent)
  : QGraphicsItem(parent),
    m_head(head),
    m_head_x(head_x),
    m_head_y(head_y),
    m_mid_x(mid_x),
    m_mid_y(mid_y),
    m_tail(tail),
    m_tail_x(tail_x),
    m_tail_y(tail_y)
{
  this->setFlag(QGraphicsItem::ItemIsMovable);
  this->setFlag(QGraphicsItem::ItemIsSelectable);
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
    if ((event->pos() - QPointF(m_tail_x,m_tail_y)).manhattanLength() < 10.0)
    {
      m_tail = !m_tail;
      this->update();
    }
    else if ((event->pos() - QPointF(m_head_x,m_head_y)).manhattanLength() < 10.0)
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
  painter->drawLine(
    m_tail_x,m_tail_y,
    m_mid_x ,m_mid_y);
  painter->drawLine(
    m_mid_x,m_mid_y,
    m_head_x,m_head_y);

  const double sz = 10.0; //pixels
  if (m_tail)
  {
    const double dx = m_mid_x - m_tail_x;
    const double dy = m_mid_y - m_tail_y;
    double angle = GetAngle(dx,dy);
    if (dy >= 0.0) angle = (1.0 * boost::math::constants::pi<double>()) + angle;
    const QPointF p0(m_tail_x,m_tail_y);
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
    const double dx = m_head_x - m_mid_x;
    const double dy = m_head_y - m_mid_y;
    double angle = GetAngle(dx,dy);
    if (dy >= 0.0) angle = (1.0 * boost::math::constants::pi<double>()) + angle;
    const QPointF p0(m_head_x,m_head_y);
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
  path.moveTo(m_tail_x,m_tail_y);
  path.lineTo(m_mid_x,m_mid_y);
  path.lineTo(m_head_x,m_head_y);
  stroker.setWidth(m_click_easy_width);
  return stroker.createStroke(path);
}

