#include <QColor>
#include <QPixmap>
#include <QGraphicsScene>
#include "qtknokfighterbackground.h"
#include "rainbow.h"

QtKnokfighterBackground::QtKnokfighterBackground(
  const int width, const int height,
  QGraphicsItem *parent)
  : QGraphicsPixmapItem(parent),
    z(0)
{
  this->setPixmap(QPixmap(width,height));
  DrawPixmap();
}

void QtKnokfighterBackground::advance(int)
{
  //++z;
  //DrawPixmap();
}

void QtKnokfighterBackground::DrawPixmap()
{
  QImage i = this->pixmap().toImage();
  const int width = i.width();
  const int height = i.height();
  for (int y=0;y!=height;++y)
  {
    for (int x=0;x!=width;++x)
    {
      double z = static_cast<double>(1 + ((x+y) % 254)) / 255.0;
      z = (z < 0.0 ? 0.0 : (z > 1.0 ? 1.0 : z));
      double r,g,b;
      Rainbow::GetRgb(z,r,g,b);
      i.setPixel( QPoint(x,y),
        QColor(
          static_cast<int>(r * 255.0),
          static_cast<int>(g * 255.0),
          static_cast<int>(b * 255.0)).rgb()
        );
    }
  }
  this->setPixmap(this->pixmap().fromImage(i));

}
