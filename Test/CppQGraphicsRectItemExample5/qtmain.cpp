#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#pragma GCC diagnostic pop

void Test()
{
  QGraphicsScene scene;

  QGraphicsRectItem item;
  item.setRect(-15,-5,30,10);

  scene.addItem(&item);

  //Create an image of before
  QImage image_before(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
  {
    // Start all pixels transparent
    image_before.fill(Qt::transparent);
    QPainter painter(&image_before);
    scene.render(&painter);
    image_before.save("Before.png");
  }

  item.setRect(-10,-20,20,40);
  //Create an image of after
  QImage image_after(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
  {
    // Start all pixels transparent
    image_after.fill(Qt::transparent);
    QPainter painter(&image_after);
    scene.render(&painter);
    image_after.save("After.png");
  }

  //Assume both images differ
  assert(image_before != image_after);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Test();

  QGraphicsScene s;
  QGraphicsRectItem t;
  t.setRect(-20,-10,40,20);

  s.addItem(&t);
  QGraphicsView v(&s);
  v.setGeometry(100,100,400,100);
  v.show();

  return a.exec();
}
