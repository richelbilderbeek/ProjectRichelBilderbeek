//---------------------------------------------------------------------------
/*
QtRoundedRectItem, rectangular-shaped QGraphicsItem
Copyright (C) 2012-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtRoundedRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTROUNDEDRECTITEM_H
#define QTROUNDEDRECTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <iosfwd>
#include <boost/signals2.hpp>

#include <QGraphicsRectItem>
#include <QPen>
#pragma GCC diagnostic pop

namespace ribi {

///Rounded rectangle item
/*

     _______
  A /       \        A  ______
   /  _____  \        X/ _____ \
  |  |B    |  |       | |B    | |
  |  |     |  |       | |     | |
  |  |_____|  |       | |_____| |
   \         /         \_______/
    \_______/

A: Outer rectangle, includes thickest pen width
B: Inner rectangle, excluded thickest pen width
X: If the rectangle is displayed with a thinner pen, A remains at the same place
*/
class QtRoundedRectItem : public QGraphicsRectItem
{
  //Q_OBJECT //Cannot make this a QObject???

  public:
  explicit QtRoundedRectItem(QGraphicsItem *parent = 0);

  virtual ~QtRoundedRectItem() noexcept;

  ///Get the pen by which the contour is drawn
  const QPen& GetContourPen() const noexcept { return m_contour_pen; }

  ///Get the pen by which focus is indicated
  const QPen& GetFocusPen() const noexcept { return m_focus_pen; }

  double GetInnerHeight() const noexcept { return GetInnerRect().height(); }
  QPointF GetInnerPos() const noexcept { return GetInnerRect().topLeft(); }
  QRectF GetInnerRect() const noexcept;
  double GetInnerWidth() const noexcept { return GetInnerRect().width(); }
  double GetInnerX() const noexcept { return GetInnerPos().x(); }
  double GetInnerY() const noexcept { return GetInnerPos().y(); }

  double GetOuterHeight() const noexcept { return GetOuterRect().height(); }
  QPointF GetOuterPos() const noexcept { return GetOuterRect().topLeft(); }
  QRectF GetOuterRect() const noexcept;
  double GetOuterWidth() const noexcept { return GetOuterRect().width(); }
  double GetOuterX() const noexcept { return GetOuterPos().x(); }
  double GetOuterY() const noexcept { return GetOuterPos().y(); }

  ///Get the rounded rect corner x radius
  double GetRadiusX() const noexcept{ return m_radius_x; }

  ///Get the rounded rect corner y radius
  double GetRadiusY() const noexcept{ return m_radius_y; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  void SetContourPen(const QPen& pen) noexcept; ///Set the pen by which the contours are normally drawn, default value: QPen(Qt::DashLine)
  void SetFocusPen(const QPen& pen) noexcept; ///Set the pen by which focus is indicated, default value: QPen(Qt::DashLine)

  void SetInnerHeight(const double width) noexcept;
  void SetInnerPos(const double x,const double y) noexcept;
  void SetInnerPos(const QPointF& pos) noexcept { SetInnerPos(pos.x(),pos.y()); }
  void SetInnerRect(const QRectF& rect) noexcept;
  void SetInnerRoundedRect(const QRectF rect, const double radius_x, const double radius_y) noexcept;
  void SetInnerWidth(const double width) noexcept;
  void SetInnerX(const double x) noexcept { SetInnerPos(x,GetInnerY()); }
  void SetInnerY(const double y) noexcept { SetInnerPos(GetInnerX(),y); }

  void SetOuterHeight(const double width) noexcept;
  void SetOuterPos(const double x,const double y) noexcept { SetOuterX(x); SetOuterY(y); }
  void SetOuterPos(const QPointF& pos) noexcept { SetOuterPos(pos.x(),pos.y()); }
  void SetOuterRect(const QRectF& rect) noexcept;
  void SetOuterRoundedRect(const QRectF& rect, const double radius_x, const double radius_y) noexcept;
  void SetOuterWidth(const double width) noexcept;
  void SetOuterX(const double x) noexcept;
  void SetOuterY(const double y) noexcept;

  void SetRadiusX(const double radius_x) noexcept;
  void SetRadiusY(const double radius_y) noexcept;

  mutable boost::signals2::signal<void (QtRoundedRectItem*)> m_signal_contour_pen_changed;
  mutable boost::signals2::signal<void (QtRoundedRectItem*)> m_signal_focus_pen_changed;
  mutable boost::signals2::signal<void (QtRoundedRectItem*)> m_signal_pos_changed;
  mutable boost::signals2::signal<void (QtRoundedRectItem*)> m_signal_radius_x_changed;
  mutable boost::signals2::signal<void (QtRoundedRectItem*)> m_signal_radius_y_changed;
  mutable boost::signals2::signal<void (QtRoundedRectItem*)> m_signal_rect_changed;

  ///Signal emitted when this item has changed its position
  //mutable boost::signals2::signal<void (QtRoundedRectItem*)> m_signal_pos_changed;

  ///Signal emitted when this item has moved
  //mutable boost::signals2::signal<void ()> m_signal_request_scene_update;

protected:

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) noexcept override;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) noexcept override;

  private:
  ///The pen by which the contour is drawn
  QPen m_contour_pen;

  ///The pen by which focus is indicated
  QPen m_focus_pen;

  ///The rounded rect corner x radius
  double m_radius_x;

  ///The rounded rect corner y radius
  double m_radius_y;

  ///To make it private, use GetPos instead
  QPointF pos() = delete;
  ///To make it private, use GetRect instead
  QRectF rect() = delete;
  ///To make it private, use SetPos instead
  void setPos(qreal x, qreal y) = delete;
  void setPos(const QPointF&) = delete;
  ///To make it private, use SetRoundedRect instead
  void setRect(const double,const double,const double,const double) = delete;
  void setRect(const QRectF&) = delete;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os,const QtRoundedRectItem& item) noexcept;

bool operator==(const QtRoundedRectItem& lhs, const QtRoundedRectItem& rhs) noexcept;
bool operator!=(const QtRoundedRectItem& lhs, const QtRoundedRectItem& rhs) noexcept;

} //~namespace ribi

#endif // QTROUNDEDRECTITEM_H
