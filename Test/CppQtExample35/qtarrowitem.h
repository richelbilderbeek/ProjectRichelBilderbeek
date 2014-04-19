#ifndef QTARROWITEM_H
#define QTARROWITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsLineItem>
#pragma GCC diagnostic pop

struct QtArrowItem : public QGraphicsItem
{
  QtArrowItem(
    const double tail_x,
    const double tail_y,
    const bool tail,
    const double mid_x,
    const double mid_y,
    const bool head,
    const double head_x,
    const double head_y,
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

  double m_head_x;
  double m_head_y;

  double m_mid_x;
  double m_mid_y;

  ///Show arrow at tail
  bool m_tail;

  double m_tail_x;
  double m_tail_y;

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  static double GetAngle(const double dx, const double dy);

};

#endif // QTARROWITEM_H
