#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <QApplication>
#include <QBitmap>
#include <QFile>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#pragma GCC diagnostic pop

struct ChangingBackground : public QGraphicsPixmapItem
{
  explicit ChangingBackground(const int width, const int height)
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
  explicit TransparentSprite(
    const std::string& filename,
    const QColor& transparency_color = QColor(0,255,0)) //Lime green
    : dx( ((std::rand() >> 4) % 3) - 1), //Random direction
      dy( ((std::rand() >> 4) % 3) - 1), //Random direction
      maxx(0),
      maxy(0)
  {
    QPixmap pixmap(filename.c_str());
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
  int maxx;
  int maxy;
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
  const int n_sprites = 25;
  for (int i=0; i!=n_sprites; ++i)
  {
    assert(QFile::exists(":/images/Bloem.png"));
    boost::shared_ptr<TransparentSprite> sprite(new TransparentSprite(":/images/Bloem.png"));
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
  timer->start(20);

  return a.exec();
}
