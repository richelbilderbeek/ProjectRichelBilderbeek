#ifndef QTROUNDEDRECTITEM_H
#define QTROUNDEDRECTITEM_H

#include <boost/signals2.hpp>
#include <QGraphicsRectItem>
#include <QPen>

///Rounded rectangle item
struct QtRoundedRectItem : public QGraphicsRectItem
{
  QtRoundedRectItem(QGraphicsItem *parent = 0);

  virtual ~QtRoundedRectItem() {}

  ///Get the pen by which the contour is drawn
  const QPen& GetContourPen() const { return m_contour_pen; }

  ///Get the pen by which focus is indicated
  const QPen& GetFocusPen() const { return m_focus_pen; }

  ///Get the rounded rect corner x radius
  double GetRadiusX() const { return m_radius_x; }

  ///Get the rounded rect corner y radius
  double GetRadiusY() const { return m_radius_y; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Set the pen by which the contours are normally drawn
  ///Default value: QPen(Qt::DashLine)
  void SetContourPen(const QPen& pen);

  ///Set the pen by which focus is indicated
  ///Default value: QPen(Qt::DashLine)
  void SetFocusPen(const QPen& pen);

  ///Set the rounded rect corner x radius
  void SetRadiusX(const double radius_x);

  ///Set the rounded rect corner y radius
  void SetRadiusY(const double radius_y);

  ///Set the rounded rect
  void SetRoundedRect(const QRectF rect, const double radius_x, const double radius_y);

  ///Signal emitted when this item has updated itself
  mutable boost::signals2::signal<void (const QtRoundedRectItem*)> m_signal_item_has_updated;

  ///Signal emitted when this item has moved
  mutable boost::signals2::signal<void ()> m_signal_request_scene_update;

protected:

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  private:
  ///The pen by which the contour is drawn
  QPen m_contour_pen;

  ///The pen by which focus is indicated
  QPen m_focus_pen;

  ///The rounded rect corner x radius
  double m_radius_x;

  ///The rounded rect corner y radius
  double m_radius_y;
};

#endif // QTROUNDEDRECTITEM_H
