#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#pragma GCC diagnostic pop

struct MyItem : public QGraphicsPolygonItem
{
  MyItem()
  {
    this->setPolygon(CreatePolygon());
  }

  //A complex shape
  static const QPolygonF CreatePolygon() noexcept
  {
    const double meter = 200.0;
    const double milli = 0.001;

    //Draw frame with opening
    const double ax( 0.1 * meter); const double ay(-0.4 * meter);
    const double bx( 0.1 * meter); const double by(-0.2 * meter);
    const double cx( 0.3 * meter); const double cy(-0.2 * meter);
    const double dx( 0.3 * meter); const double dy( 0.29 * meter);
    const double ex(-0.1 * meter); const double ey( 0.29 * meter);
    const double fx(-0.1 * meter); const double fy( 1.29 * meter);
    const double gx(-0.2 * meter); const double gy( 1.29 * meter);
    const double hx(-0.2 * meter); const double hy(-0.4 * meter);
    const QPolygonF p_outside(
      QVector<QPointF>(
        {
          QPointF(ax,ay),
          QPointF(bx,by),
          QPointF(cx,cy),
          QPointF(dx,dy),
          QPointF(ex,ey),
          QPointF(fx,fy),
          QPointF(gx,gy),
          QPointF(hx,hy)
        }
      )
    );
    //Draw rect in frame
    const double rx((-47.4-25.0) * milli * meter);
    const double ry(( 56.4-25.0) * milli * meter);
    const double rw((160.0+50.0) * milli * meter);
    const double rh((130.0+50.0) * milli * meter);
    const QRectF r(rx,ry,rw,rh);
    const QPolygonF p_inside(
      QVector<QPointF>(
        {
          QPointF( rx      ,ry),
          QPointF((rx + rw),ry),
          QPointF((rx + rw),(ry+rh)),
          QPointF( rx      ,(ry+rh))
        }
      )
    );
    const QPolygonF p( p_outside.subtracted(p_inside));
    return p;
  }
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QGraphicsView w;

  assert(!w.scene());
  w.setScene(new QGraphicsScene);
  assert(w.scene());

  {
    MyItem * const item = new MyItem;
    w.scene()->addItem(item);
  }
  {
    MyItem * const item = new MyItem;
    item->setBrush(QBrush(QColor(0,0,0)));
    item->setPos(300.0,0);
    w.scene()->addItem(item);
  }
  w.show();

  return a.exec();
}
