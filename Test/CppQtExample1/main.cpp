#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <QApplication>
#include <QBitmap>
#include <QGraphicsPathItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#pragma GCC diagnostic pop

struct Background : public QGraphicsPixmapItem
{
  explicit Background(const std::string& filename)
  {
    QPixmap m(filename.c_str());
    this->setPixmap(m);
  }
};

struct TransparentSprite : public QGraphicsPixmapItem
{
  explicit TransparentSprite(
    const std::string& filename,
    const QColor& transparency_color = QColor(0,255,0)) //Lime green
    : dx(1), dy(1), maxx(320), maxy(200)
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
    maxx = width  - this->pixmap().width();
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

  //Original image from http://commons.wikimedia.org/wiki/File:Bubblegum_2.png
  //by Marendo Mueller 10.05.2013, resized to 15%
  Background background(":/images/Bubblegum_2.png");
  s.addItem(&background);

  //Image from http://commons.wikimedia.org/wiki/File:Bloem.png
  //by DD21
  TransparentSprite sprite(":/images/Bloem.png");
  sprite.setRect(background.pixmap().width(),background.pixmap().height());

  s.addItem(&sprite);

  v.show();

  boost::shared_ptr<QTimer> timer(new QTimer(&s));
  timer->connect(timer.get(), SIGNAL(timeout()), &s, SLOT(advance()));
  timer->start(10);

  return a.exec();
}
