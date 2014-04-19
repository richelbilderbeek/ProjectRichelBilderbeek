#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#pragma GCC diagnostic pop

//Compare a triangle when drawn as a
//QGraphicsPolygonItem or a plain QGraphicsItem

struct TrianglePolygonItem : public QGraphicsPolygonItem
{
  TrianglePolygonItem()
  {
    this->setPolygon(CreatePolygon());
  }

  static const QPolygonF CreatePolygon() noexcept
  {
    //A triangle
    const double ax(  0.0); const double ay(-50.0);
    const double bx( 50.0); const double by( 50.0);
    const double cx(-50.0); const double cy( 50.0);
    const QPolygonF p(
      QVector<QPointF>(
        {
          QPointF(ax,ay),
          QPointF(bx,by),
          QPointF(cx,cy)
        }
      )
    );
    return p;
  }
};

struct TriangleGraphicsItem : public QGraphicsItem
{
  TriangleGraphicsItem() : m_brush{}
  {

  }
  QRectF boundingRect() const
  {
    return CreatePolygon().boundingRect();
  }
  void paint(
    QPainter *painter,
    const QStyleOptionGraphicsItem * /*option*/,
    QWidget * /*widget*/
  )
  {
    painter->setBrush(m_brush);
    painter->drawPolygon(CreatePolygon());
  }
  static const QPolygonF CreatePolygon() noexcept
  {
    //A triangle
    const double ax(  0.0); const double ay(-50.0);
    const double bx( 50.0); const double by( 50.0);
    const double cx(-50.0); const double cy( 50.0);
    const QPolygonF p(
      QVector<QPointF>(
        {
          QPointF(ax,ay),
          QPointF(bx,by),
          QPointF(cx,cy)
        }
      )
    );
    return p;
  }
  void SetMyBrush(const QBrush &brush)
  {
    m_brush = brush;
  }
  private:
  QBrush m_brush;
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QGraphicsView w;

  assert(!w.scene());
  w.setScene(new QGraphicsScene);
  assert(w.scene());

  {
    TrianglePolygonItem * const item = new TrianglePolygonItem;
    item->setPos(-150.0,-150.0);
    w.scene()->addItem(item);
  }
  {
    TrianglePolygonItem * const item = new TrianglePolygonItem;
    item->setBrush(QBrush(QColor(0,0,0)));
    item->setPos(150.0,-150.0);
    w.scene()->addItem(item);
  }
  {
    TriangleGraphicsItem * const item = new TriangleGraphicsItem;
    item->setPos(-150.0, 150.0);
    w.scene()->addItem(item);
  }
  {
    TriangleGraphicsItem * const item = new TriangleGraphicsItem;
    item->SetMyBrush(QBrush(QColor(0,0,0)));
    item->setPos(150.0, 150.0);
    w.scene()->addItem(item);
  }
  w.show();

  return a.exec();
}
