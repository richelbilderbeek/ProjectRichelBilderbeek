#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
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

  this->setFlags(QGraphicsItem::ItemIsMovable);
}
