#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#pragma GCC diagnostic pop

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
        i.setPixel(
          QPoint(x,y), //Position
          QColor( //Color
            (x+z+0)%256,
            (y+z+0)%256,
            (x+y+z)%256)
          .rgb());
      }
    }
    this->setPixmap(this->pixmap().fromImage(i));
    ++z;
  }
  private:
  int z;
};


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  //Create a scene to add the background sprite to
  boost::shared_ptr<QGraphicsScene> scene(new QGraphicsScene);

  //Create a background sprite to add to the scene
  boost::shared_ptr<ChangingBackground> background(
    new ChangingBackground(256,256));
  scene->addItem(background.get());

  //Create a view to display the scene
  boost::shared_ptr<QGraphicsView> view(new QGraphicsView);
  view->setScene(scene.get());

  //Create a timer to call 'advance' on the scene and its sprite
  boost::shared_ptr<QTimer> timer(new QTimer(scene.get()));
  timer->connect(timer.get(), SIGNAL(timeout()), scene.get(), SLOT(advance()));
  timer->start(20);

  //Display the view
  view->show();

  //Move the view to the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  view->move( screen.center() - view->rect().center() );

  return a.exec();
}
