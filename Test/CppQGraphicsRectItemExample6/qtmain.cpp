#include <cassert>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QGraphicsScene scene;
  QGraphicsView view(&scene);
  view.setGeometry(100,100,400,100);

  QGraphicsRectItem item;
  item.setFlags(
      QGraphicsItem::ItemIsSelectable
    | QGraphicsItem::ItemIsFocusable
  );

  item.setRect(-20,-10,40,20);

  scene.addItem(&item);

  assert(item.flags() && QGraphicsItem::ItemIsSelectable);
  assert(item.flags() && QGraphicsItem::ItemIsFocusable);
  assert(item.scene());
  assert(item.isVisible());

  assert(!item.hasFocus()); //No focus yet

  item.setFocus();          //Set focus

  view.show();              //Show it

  //Force paint of item
  {
    QImage image(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    scene.render(&painter);
    image.save("tmp.png");
  }

  assert(item.hasFocus());  //Why does this fail?

  return a.exec();
}
