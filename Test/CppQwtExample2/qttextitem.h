#ifndef QTTEXTITEM_H
#define QTTEXTITEM_H

#include <boost/signals2.hpp>
#include <QGraphicsSimpleTextItem>

struct QtTextItem : public QGraphicsSimpleTextItem
{
  QtTextItem(const QString& text, QGraphicsItem* parent = 0);

  boost::signals2::signal<void(double)> m_signal_value;

  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QTTEXTITEM_H
