#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include "grabber.h"
#pragma GCC diagnostic pop



int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QGraphicsScene s;
  QGraphicsSimpleTextItem t;
  t.setText("To be grabbed...");
  t.setFlags(
      QGraphicsItem::ItemIsSelectable
    | QGraphicsItem::ItemIsMovable);

  s.addItem(&t);
  QGraphicsView v(&s);
  v.setGeometry(100,100,400,100);
  v.show();

  Grabber g(
    v.winId(),
    "CppQGraphicsViewExample2Screengrab.png"
  );
  QTimer::singleShot(1000,&g,SLOT(Grab()));

  return a.exec();
}
