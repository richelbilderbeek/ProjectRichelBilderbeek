#ifndef QTITEM_H
#define QTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsObject>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

//Forward declaration
struct QPixmap;

///A QGraphicsObject that
/// - loads its pixmap from resources
/// - is clickable
/// - is movable
/// - changes the cursor
class QtItem : public QGraphicsObject
{
  Q_OBJECT

  public:

  QtItem(QGraphicsItem *parent = 0);

  ///Signal emitted when clicked
  boost::signals2::signal<void (QtItem*)> m_clicked_signal;

  protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

  QRectF boundingRect() const;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  private:
  ///The pixmap
  boost::scoped_ptr<QPixmap> m_pixmap;
};

#endif // QTITEM_H
