#ifndef QTITEM_H
#define QTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsObject>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

struct QPixmap;
struct QTimer;

///A QGraphicsObject that
/// - loads its pixmap from resources
/// - is clickable
/// - is movable
/// - changes the cursor
/// - can flash
class QtItem : public QGraphicsObject
{
  Q_OBJECT

  public:

  QtItem(QGraphicsItem *parent = 0);
  QtItem(const QtItem&) = delete;
  QtItem& operator=(const QtItem&) = delete;

  ///Lets this item flash
  void Flash();

  ///Signal emitted when clicked
  boost::signals2::signal<void (QtItem*)> m_clicked_signal;

  protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

  QRectF boundingRect() const;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


  private:
  ///The number of flashes since flashing started
  int m_n_flashes;

  ///The pixmap
  boost::scoped_ptr<QPixmap> m_pixmap;

  ///Use QTimer because of its signals
  //Deleted by its parent (which is this item itself)
  QTimer * const m_timer;

  private slots:
  ///The event called when the item must flicker
  void FlashEvent();
};

#endif // QTITEM_H
