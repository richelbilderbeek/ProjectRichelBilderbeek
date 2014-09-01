#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QCursor>
#include <QPainter>
#include <QPixmap>
#include "qtitem.h"
#pragma GCC diagnostic pop

QtItem::QtItem(QGraphicsItem *parent)
  : QGraphicsObject(parent),
    m_clicked_signal{},
    m_pixmap{new QPixmap(":/images/PicR.png")}
{
  assert(!m_pixmap->isNull()
    && "Assume pixmap is loaded successfully");

  this->setFlags(
      QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable
  );


  //Without this line, hoverMoveEvent will not be called
  this->setAcceptHoverEvents(true);
}

QRectF QtItem::boundingRect() const
{
  const QRectF targetRect = m_pixmap->rect().translated(-m_pixmap->rect().center());
  assert(targetRect.center().x() >= -1.0);
  assert(targetRect.center().x() <=  1.0);
  assert(targetRect.center().y() >= -1.0);
  assert(targetRect.center().y() <=  1.0);
  return targetRect;
}

void QtItem::hoverMoveEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}

void QtItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
  //Emit the Boost signal
  m_clicked_signal(this);
}

void QtItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  const QRectF targetRect = m_pixmap->rect().translated(-m_pixmap->rect().center());
  assert(targetRect.center().x() >= -1.0);
  assert(targetRect.center().x() <=  1.0);
  assert(targetRect.center().y() >= -1.0);
  assert(targetRect.center().y() <=  1.0);

  painter->drawPixmap(targetRect,*m_pixmap,m_pixmap->rect());

  //Draw a thick red line around the pixmap when it is selected
  if (this->isSelected())
  {
    painter->setPen(QPen(QColor(255,0,0),2));
    painter->drawRect(this->boundingRect().adjusted(2.0,2.0,-2.0,-2.0));
  }
}
