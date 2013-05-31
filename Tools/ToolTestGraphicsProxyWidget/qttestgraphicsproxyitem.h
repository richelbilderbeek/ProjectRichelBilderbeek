#ifndef QTBOUNCINGBALL_H
#define QTBOUNCINGBALL_H

#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
struct QGraphicsScene;

struct QtTestGraphicsProxyItem : public QGraphicsProxyWidget
{

  QtTestGraphicsProxyItem(QGraphicsItem *parent, Qt::WindowFlags wFlags);

  /*
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
  */
};

#endif // QTBOUNCINGBALL_H
