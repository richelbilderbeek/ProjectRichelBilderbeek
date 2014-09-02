
#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QCursor>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include "qtitem.h"
#pragma GCC diagnostic pop

QtItem::QtItem(QGraphicsItem *parent)
  : QGraphicsObject(parent),
    m_clicked_signal{},
    m_n_flashes{0},
    m_pixmap{new QPixmap(":/images/PicR.png")},
    m_timer{new QTimer(this)}
{
  assert(!m_pixmap->isNull()
    && "Assume pixmap is loaded successfully");

  this->setFlags(
      QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable
  );


  //Without this line, hoverMoveEvent will not be called
  this->setAcceptHoverEvents(true);

  ///Set the interval between the flickers
  m_timer->setInterval(100); //100 ms

  QObject::connect(m_timer,SIGNAL(timeout()),
    this,SLOT(FlashEvent()));
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

void QtItem::Flash()
{
  m_n_flashes = 0;
  m_timer->start();
}

void QtItem::FlashEvent()
{
  this->update();
  ++m_n_flashes;
  if (m_n_flashes == 10) { m_timer->stop(); }
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

  if (m_n_flashes % 2)
  {
    //Inverted pixmap
    QImage image = m_pixmap->toImage();
    image.invertPixels();
    QPixmap pixmap = QPixmap::fromImage(image);
    painter->drawPixmap(targetRect,pixmap,m_pixmap->rect());
  }
  else
  {
    //Regular pixmap
    painter->drawPixmap(targetRect,*m_pixmap,m_pixmap->rect());
  }

  //Draw a red line around the pixmap when it is selected
  if (this->isSelected())
  {
    painter->setPen(QPen(QColor(255,0,0),1));
    painter->drawRect(this->boundingRect().adjusted(1.0,1.0,-1.0,-1.0));
  }
}
