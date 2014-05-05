#ifndef QTITEM_H
#define QTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsPixmapItem>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

///A QGraphicsPixmapItem that loads its pixmap from resources
///and is clickable
struct QtItem : public QGraphicsPixmapItem
{
  QtItem(QGraphicsItem *parent = 0);

  ///Signal emitted when clicked
  boost::signals2::signal<void (QtItem*)> m_clicked_signal;


  protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // QTITEM_H
