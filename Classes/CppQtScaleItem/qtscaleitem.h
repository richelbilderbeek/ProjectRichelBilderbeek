#ifndef QTSCALEITEM_H
#define QTSCALEITEM_H

#include <QGraphicsItem>

///This top item defines a scale
struct QtScaleItem : public QGraphicsItem
{
  QtScaleItem(QGraphicsItem *parent = 0);

  QRectF boundingRect() const;

  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  QPainterPath shape() const;


  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


  static void GetRgb(
    const double x,
    double& r,
    double& g,
    double& b);

  ///The maximum scale length in meters
  ///For example, with a length of 1.0 meter, then meters, decimeters, centimeters, etc. are displayed
  static const double m_length;

  ///The type of this class as a std::string
  static const std::string m_type_string;
};

#endif // QTSCALEITEM_H
