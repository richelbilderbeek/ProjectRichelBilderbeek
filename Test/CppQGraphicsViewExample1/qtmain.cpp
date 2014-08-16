#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QGraphicsScene s;
  QGraphicsSimpleTextItem t;
  t.setText("My QGraphicsSimpleTextItem");
  t.setFlags(
      QGraphicsItem::ItemIsSelectable
    | QGraphicsItem::ItemIsMovable);

  s.addItem(&t);
  QGraphicsView v(&s);
  v.setGeometry(100,100,400,100);
  v.show();
  return a.exec();
}
