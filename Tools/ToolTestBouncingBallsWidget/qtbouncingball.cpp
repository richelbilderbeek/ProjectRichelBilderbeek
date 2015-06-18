#include <cassert>
#include <cmath>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include <QPainter>
#include "qtbouncingball.h"

QtBouncingBall::QtBouncingBall(QGraphicsItem *parent, QGraphicsScene *scene)
 : QGraphicsItem(parent),
   m_dx(1.0), m_dy(1.0), m_scene(scene)
{
  m_scene->addItem(this);
  assert(m_scene && "An initialized QGraphicsScene must be supplied");
}

void QtBouncingBall::advance(int /* phase */)
{
  if (x() + m_dx + (boundingRect().width() * 0.5) > m_scene->width()) m_dx = -std::abs(m_dx);
  else if (x() + m_dx - (boundingRect().width() * 0.5) < 0.0) m_dx = std::abs(m_dx);
  if (y() + m_dy + (boundingRect().height() * 0.5) > m_scene->height()) m_dy = -std::abs(m_dy);
  else if (y() + m_dy - (boundingRect().width() * 0.5) < 0.0) m_dy = std::abs(m_dy);
  this->setPos(x() + m_dx, y() + m_dy);

  //Respond to collision with other item
  const QList<QGraphicsItem *> others = collidingItems();
  if (others.isEmpty()) return;
  const QGraphicsItem * const other = others[0];
  if (this->x() < other->x()) m_dx = -std::abs(m_dx);
  else if (this->x() > other->x()) m_dx =  std::abs(m_dx);
  if (this->y() < other->y()) m_dy = -std::abs(m_dy);
  else if (this->y() > other->y()) m_dy =  std::abs(m_dy);
  this->setPos(x() + m_dx, y() + m_dy);
  this->setPos(x() + m_dx, y() + m_dy);

}

QRectF QtBouncingBall::boundingRect() const
{
  return QRectF(-16.0,-16.0,32.0,32.0);
}

void QtBouncingBall::paint(
  QPainter *painter,
  const QStyleOptionGraphicsItem * /* option */,
  QWidget * /* widget */)
{
  painter->drawEllipse(this->boundingRect());
}

QPainterPath QtBouncingBall::shape() const
{
  QPainterPath p;
  p.addEllipse(boundingRect());
  return p;
}
