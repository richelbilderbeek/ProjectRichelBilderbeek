#ifndef QTBOUNCINGRECT_H
#define QTBOUNCINGRECT_H

#include <QGraphicsItem>

struct QGraphicsScene;

struct QtBouncingRect : public QGraphicsItem
{
  QtBouncingRect(QGraphicsItem *parent, QGraphicsScene *scene);

  ///Make the balls move
  void advance(int phase);

  ///Thanks compiler for reminding me to add this method!
  QRectF boundingRect() const;

  ///Thanks compiler for reminding me to add this method!
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


  private:
  ///Use simplified physics in this example
  ///Horizontal speed (delta x)
  double m_dx;

  ///Use simplified physics in this example
  ///Vertical speed (delta y)
  double m_dy;

  ///The scene this class is in
  QGraphicsScene * const m_scene;
};

#endif // QTBOUNCINGRECT_H
