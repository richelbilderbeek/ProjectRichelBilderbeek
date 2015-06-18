#ifndef QTBOUNCINGBALL_H
#define QTBOUNCINGBALL_H

#include <QGraphicsItem>

struct QGraphicsScene;

struct QtBouncingBall : public QGraphicsItem
{
  QtBouncingBall(QGraphicsItem *parent, QGraphicsScene *scene);
  QtBouncingBall(const QtBouncingBall&) = delete;
  QtBouncingBall& operator=(const QtBouncingBall&) = delete;

  ///Make the balls move
  void advance(int phase);

  ///Thanks compiler for reminding me to add this method!
  QRectF boundingRect() const;

  ///The real collision shape
  QPainterPath shape() const;

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

#endif // QTBOUNCINGBALL_H
