#ifndef QTGRAVITYWIDGETITEM_H
#define QTGRAVITYWIDGETITEM_H

#include <QGraphicsItem>

struct QtGravityWidgetItem : public QGraphicsItem
{
  QtGravityWidgetItem(QGraphicsItem * parent, QGraphicsScene * scene);

  ///Must be defined, thanks compiler for telling me!
  QRectF boundingRect() const;

  ///Must be defined, thanks compiler for telling me!
  void paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *);

  ///Can be defined optionally, this will contain the falling motion
  void advance(int);

  private:
  ///The vertical speed
  double m_dy;

  ///The rectangle this QtGravityWidgetItem is in
  const QRectF m_rect;

  ///Read-only pointer to the QGraphicsScene this QtGravityWidgetItem is part of
  QGraphicsScene * const m_scene;

};
#endif // QTGRAVITYWIDGETITEM_H
