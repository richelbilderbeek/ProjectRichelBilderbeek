#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <memory>

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#pragma GCC diagnostic pop


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QGraphicsSimpleTextItem * const item_a{
    new QGraphicsSimpleTextItem("A")
  };
  assert(item_a->pos().x() == 0.0);
  assert(item_a->pos().y() == 0.0);

  QGraphicsSimpleTextItem * const item_b{
    new QGraphicsSimpleTextItem("B")
  };
  assert(item_b->pos().x() == 0.0);
  assert(item_b->pos().y() == 0.0);

  QGraphicsScene s;
  s.addItem(item_a);
  s.addItem(item_b);

  QGraphicsView w;
  w.setGeometry(100,100,400,100);
  w.setScene(&s);

  //Move item A
  {
    QGraphicsSceneMouseEvent * const event{new QGraphicsSceneMouseEvent};
    event->setButtonDownPos(Qt::LeftButton,QPointF(0.0,0.0));
    event->setPos(QPointF(100.0,100.0));
    qApp->sendEvent(&item_a,event); //Compile error: QGraphicsSimpleTextItem is not a derived class of QObject
  }

  w.show();
  a.exec();
}
