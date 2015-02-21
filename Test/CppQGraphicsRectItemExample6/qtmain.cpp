#include <cassert>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsRectItem>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QGraphicsScene scene;

  QGraphicsRectItem item;
  item.setFlags(
      QGraphicsItem::ItemIsSelectable
    | QGraphicsItem::ItemIsFocusable
  );

  item.setRect(-20,-10,40,20);

  scene.addItem(&item);

  assert(item.flags() && QGraphicsItem::ItemIsSelectable);
  assert(item.flags() && QGraphicsItem::ItemIsFocusable);

  assert(!item.hasFocus()); //No focus yet
  item.setFocus();          //Set focus
  assert(item.hasFocus());  //Why does this fail?

  QGraphicsView view(&scene);
  view.setGeometry(100,100,400,100);
  view.show();

  return a.exec();
}
