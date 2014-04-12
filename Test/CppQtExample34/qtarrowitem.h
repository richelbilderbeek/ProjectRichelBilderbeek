#ifndef QTARROWITEM_H
#define QTARROWITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsLineItem>
#pragma GCC diagnostic pop

struct QtArrowItem : public QGraphicsLineItem
{
  QtArrowItem(
    const double x1,
    const double y1,
    const bool tail,
    const double x2,
    const double y2,
    const bool head,
    QGraphicsItem *parent = 0);

  ///Respond to key presses
  void keyPressEvent(QKeyEvent *event);

  protected:
  ///The rectangle that containg the item, used for rough calculations like
  ///collision detection
  QRectF boundingRect() const;


  ///Respond to mouse press
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  ///Paint a QtTextPositionItem
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

  ///More precise shape compared to boundingRect
  ///In this example, it is redefined to ease selecting those thin lines
  QPainterPath shape() const;


  private:
  ///The extra width given to the line for easier clicking
  static const double m_click_easy_width;

  ///Show arrow at head
  bool m_head;

  ///Show arrow at tail
  bool m_tail;

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  static double GetAngle(const double dx, const double dy);

};

#endif // QTARROWITEM_H
