#include <cassert>
#include <cmath>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsScene>
#include <QPainter>
#include "qtgravitywidgetitem.h"
#pragma GCC diagnostic pop

QtGravityWidgetItem::QtGravityWidgetItem(
  QGraphicsItem * parent,
  QGraphicsScene * scene)
  : QGraphicsItem(parent),
    m_dy(0.0),
    m_rect(-16.0,-16.0,32.0,32.0),
    m_scene(scene)
{
  assert(m_scene);
  m_scene->addItem(this);
}

void QtGravityWidgetItem::advance(int)
{
  const double acceleration = 0.1;

  //If the new y coordinat (after acceleration) causes the bottom of the QtGravityWidgetItem
  //to be beyond the edge of the QGraphicsScene, turn the vertical speed upwards
  if (y() + m_dy + acceleration + (m_rect.height() * 0.5) > m_scene->height()) m_dy = -std::abs(m_dy + acceleration);

  //Accelerate the QtGravityWidgetItem
  m_dy+=acceleration;

  //Move the QtGravityWidgetItem
  setY(y() + m_dy);

  //Move the QtGravityWidgetItem up when the QGraphicsScene is resized so much
  //that the QtGravityWidgetItem gets out of sight
  if (y() + (m_rect.height() * 0.5) > m_scene->height())
  {
    //Move the QtGravityWidgetItem to the bottom of the QGraphicsScene
    setY(m_scene->height() - (m_rect.height() * 0.5));

    //Set the vertical speed to zero, otherwise there is need to check if the QtGravityWidgetItem
    //leaves the top of the QGraphicsScene
    m_dy = 0.0;
  }
}

QRectF QtGravityWidgetItem::boundingRect() const
{
  return m_rect;
}

void QtGravityWidgetItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->drawEllipse(m_rect);
}
