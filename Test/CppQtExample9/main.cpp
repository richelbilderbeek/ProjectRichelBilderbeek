#include <cassert>
#include <cmath>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/timer.hpp>
#include <QApplication>
#include <QBitmap>
#include <QDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QVBoxLayout>
#pragma GCC diagnostic pop

BOOST_STATIC_ASSERT(sizeof(qreal)==sizeof(double)
  && "Assume use of double is equivalent of qreal");

struct Background : public QGraphicsPixmapItem
{
  explicit Background(const int width = 256, const int height = 256)
  {
    QImage i(width,height,QImage::Format_ARGB32);
    for (int y=0;y!=height;++y)
    {
      for (int x=0;x!=width;++x)
      {
        const int gray = (x + y) % 256;
        i.setPixel(QPoint(x,y),QColor(gray,gray,gray).rgb());
      }
    }
    this->setPixmap(this->pixmap().fromImage(i));
  }
};

struct Sprite : public QGraphicsPixmapItem
{
  explicit Sprite(const int width = 32, const int height = 32)
    : dx(1.0), dy(1.0), maxx(0.0), maxy(0.0)
  {
    QImage i(width,height,QImage::Format_ARGB32);
    for (int y=0;y!=height;++y)
    {
      for (int x=0;x!=width;++x)
      {
        const int gray = ((8 * x) + (8 * y)) % 256;
        i.setPixel(QPoint(x,y),QColor(gray,gray,gray).rgb());
      }
    }
    this->setPixmap(this->pixmap().fromImage(i));
  }
  void advance(int)
  {
    double new_x = this->x();
    double new_y = this->y();
    new_x+=dx;
    new_y+=dy;
    if (new_x<0.0 || new_x>maxx) dx= -dx;
    if (new_y<0.0 || new_y>maxy) dy= -dy;
    this->setX(new_x);
    this->setY(new_y);
  }
  void setRect(const int width, const int height)
  {
    maxx = static_cast<double>(width  - this->pixmap().width() );
    maxy = static_cast<double>(height - this->pixmap().height());
  }
  private:
  double dx;
  double dy;
  double maxx;
  double maxy;
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  //Start with creating a scene
  boost::shared_ptr<QGraphicsScene> scene(new QGraphicsScene);

  //Add background to scene
  boost::shared_ptr<Background> background(new Background);
  scene->addItem(background.get());

  //Add sprites to scene
  std::vector<boost::shared_ptr<Sprite> > sprites;
  //Add multiple sprites
  {
    const int n_sprites = 20;
    const double midx = background->pixmap().width() / 2.0;
    const double midy = background->pixmap().height() / 2.0;
    const double ray = std::min(midx,midy) * 0.8;
    const double d_angle = boost::math::constants::two_pi<double>() / static_cast<double>(n_sprites);
    double angle = 0.0;
    for (int i=0; i!=n_sprites; ++i)
    {
      boost::shared_ptr<Sprite> sprite(new Sprite);
      const double x = midx + (std::sin(angle) * ray) - (sprite->pixmap().width() / 2);
      const double y = midy - (std::cos(angle) * ray) - (sprite->pixmap().height() / 2);
      sprite->setX(x);
      sprite->setY(y);
      sprite->setRect(background->pixmap().width(),background->pixmap().height());
      scene->addItem(sprite.get());
      sprites.push_back(sprite);
      angle+=d_angle;
    }
  }

  //Connect a view to display the scene
  boost::shared_ptr<QGraphicsView> view(new QGraphicsView);
  view->setScene(scene.get());

  //Create a layout to put the scene in
  boost::shared_ptr<QVBoxLayout> layout(new QVBoxLayout);
  layout->addWidget(view.get());

  //Create a dialog to display to laid-out-scene
  boost::shared_ptr<QDialog> dialog(new QDialog);
  dialog->setLayout(layout.get());
  dialog->setGeometry(view->rect());

  //Create a timer to call 'advance' on all sprites'
  boost::shared_ptr<QTimer> timer(new QTimer(scene.get()));
  timer->connect(timer.get(), SIGNAL(timeout()), scene.get(), SLOT(advance()));
  timer->start(20);

  //Show the graphicsscene with its sprites
  dialog->show();

  return a.exec();
}
