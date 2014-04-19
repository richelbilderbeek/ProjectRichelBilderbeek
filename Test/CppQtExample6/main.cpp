#include <cmath>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>

#include <QApplication>
#include <QBitmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#pragma GCC diagnostic pop

BOOST_STATIC_ASSERT(sizeof(qreal)==sizeof(double)
  && "Assume use of double is equivalent of qreal");

struct ChangingBackground : public QGraphicsPixmapItem
{
  ChangingBackground(const int width, const int height)
    : z(0)
  {
    QPixmap m(width,height);
    this->setPixmap(m);
  }
  void advance(int)
  {
    QImage i = this->pixmap().toImage();
    const int width = i.width();
    const int height = i.height();
    for (int y=0;y!=height;++y)
    {
      for (int x=0;x!=width;++x)
      {
        QPoint pos(x,y);
        QColor c((x+z)%256,(y+z)%256,(x+y+z)%256);
        i.setPixel(pos,c.rgb());
      }
    }
    this->setPixmap(this->pixmap().fromImage(i));
    ++z;
  }
  private:
  int z;
};

struct TransparentSprite : public QGraphicsPixmapItem
{
  TransparentSprite(
    const int width, const int height,
    const int r = 255,
    const int g = 255,
    const int b = 255)
    : dx( ((std::rand() >> 4) % 3) - 1), //Random direction
      dy( ((std::rand() >> 4) % 3) - 1), //Random direction
      maxx(0),
      maxy(0)
  {
    QImage i(width,height,QImage::Format_ARGB32);
    const QColor transparency_color = QColor(0,0,0,255);
    const double r_real = static_cast<double>(r);
    const double g_real = static_cast<double>(g);
    const double b_real = static_cast<double>(b);
    const double midx = static_cast<double>(width ) / 2.0;
    const double midy = static_cast<double>(height) / 2.0;
    const double ray = std::min(midx,midy);
    for (int y=0;y!=height;++y)
    {
      const double y_real = static_cast<double>(y);
      const double dy = midy - y_real;
      const double dy2 = dy * dy;
      for (int x=0;x!=width;++x)
      {
        const double x_real = static_cast<double>(x);
        const double dx = midx - x_real;
        const double dx2 = dx * dx;
        const double dist = std::sqrt(dx2 + dy2);
        if (dist < ray)
        {
          const QColor c(
            (1.0 - (dist / ray)) * r_real,
            (1.0 - (dist / ray)) * g_real,
            (1.0 - (dist / ray)) * b_real);
          i.setPixel(x,y,c.rgb());
        }
        else
        {
          i.setPixel(x,y,transparency_color.rgb());

        }
      }
    }
    this->setPixmap(this->pixmap().fromImage(i));

    QPixmap pixmap = this->pixmap();
    const QBitmap mask = pixmap.createMaskFromColor(transparency_color);
    pixmap.setMask(mask);
    this->setPixmap(pixmap);

  }
  void advance(int)
  {
    int new_x = this->x();
    int new_y = this->y();
    new_x+=dx;
    new_y+=dy;
    if (new_x<0 || new_x>maxx) dx= -dx;
    if (new_y<0 || new_y>maxy) dy= -dy;
    this->setX(new_x);
    this->setY(new_y);
  }
  void setRect(const int width, const int height)
  {
    maxx = width - this->pixmap().width();
    maxy = height - this->pixmap().height();

  }
  private:
  int dx;
  int dy;
  double maxx;
  double maxy;

};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QGraphicsScene s;
  QGraphicsView v(&s);

  ChangingBackground background(512,512);
  s.addItem(&background);

  std::vector<boost::shared_ptr<TransparentSprite> > sprites;
  //Add multiple sprites
  const int n_sprites = 50;
  for (int i=0; i!=n_sprites; ++i)
  {
    boost::shared_ptr<TransparentSprite> sprite(
      new TransparentSprite(
        64,
        64,
        128 + (std::rand() % 128),
        128 + (std::rand() % 128),
        128 + (std::rand() % 128)));
    const int maxx = background.pixmap().width() - sprite->pixmap().width();
    const int maxy = background.pixmap().height() - sprite->pixmap().height();
    sprite->setX(std::rand() % maxx);
    sprite->setY(std::rand() % maxy);
    sprite->setRect(background.pixmap().width(),background.pixmap().height());
    s.addItem(sprite.get());
    sprites.push_back(sprite);
  }

  v.show();

  boost::shared_ptr<QTimer> timer(new QTimer(&s));
  timer->connect(timer.get(), SIGNAL(timeout()), &s, SLOT(advance()));
  timer->start(50);

  return a.exec();
}
