#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <QCursor>
#include <QPainter>
#include "qtitem.h"
#pragma GCC diagnostic pop

QtItem::QtItem(QGraphicsItem *parent)
  : QGraphicsPixmapItem(parent)
{
  assert(this->pixmap().isNull()
    && "Assume no pixmap loaded yet");

  //Load the pixmap from resources
  this->setPixmap(QPixmap(":/images/PicR.png"));

  assert(!this->pixmap().isNull()
    && "Assume pixmap is loaded successfully");

  //Let the item have (0.0,0.0) as its center,
  //so it will remain in place when rotating
  this->setOffset(-pixmap().rect().center());

  this->setFlags(
      QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

}

void QtItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  //Let QGraphicsPixmapItem handle most of the painting
  QGraphicsPixmapItem::paint(painter,option,widget);

  //Draw a thick red line around the pixmap when it is selected
  if (this->isSelected())
  {
    painter->setPen(QPen(QColor(255,0,0),3));
    painter->drawRoundedRect(this->boundingRect().adjusted(3.0,3.0,-3.0,-3.0),6.0,6.0);
  }
}
