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
class QtRoundedRectItem : public QGraphicsRectItem
{
  //Q_OBJECT //Cannot make this a QObject???

  public:
  explicit QtRoundedRectItem(QGraphicsItem *parent = 0);

  virtual ~QtRoundedRectItem() noexcept;

  ///Get the pen by which the contour is drawn
  const QPen& GetContourPen() const noexcept;

  ///Get the pen by which focus is indicated
  const QPen& GetFocusPen() const noexcept;

  ///Get the height of the area within the rounded rectangle
  /*
    ___
   / _ \  GetHeight/GetWidth = 1
   ||_||  GetHeightIncludingPen/GetWidthIncludingPen = 3
   \___/

  */
  double GetHeight() const noexcept;
  ///Get the height of the area including the rounded rectangle itself
  double GetHeightIncludingPen() const noexcept;

  QPointF GetPos() const noexcept;

  ///Get the rounded rect corner x radius
  double GetRadiusX() const noexcept;

  ///Get the rounded rect corner y radius
  double GetRadiusY() const noexcept;

  ///Get the rectangle of the inner area
  QRectF GetRect() const noexcept;
  QRectF GetRectIncludingPen() const noexcept;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Get the width of the area within the rounded rectangle
  /*
    ___
   / _ \  GetHeight/GetWidth = 1
   ||_||  GetHeightIncludingPen/GetWidthIncludingPen = 3
   \___/

  */
  double GetWidth() const noexcept;
  ///Get the width of the area including the rounded rectangle itself
  double GetWidthIncludingPen() const noexcept;

  double GetX() const noexcept { return GetPos().x(); }
  double GetY() const noexcept { return GetPos().y(); }

  ///Set the pen by which the contours are normally drawn
  ///Default value: QPen(Qt::DashLine)
  void SetContourPen(const QPen& pen) noexcept;

  ///Set the pen by which focus is indicated
  ///Default value: QPen(Qt::DashLine)
  void SetFocusPen(const QPen& pen) noexcept;

  void SetHeight(const double width) noexcept;
  void SetHeightIncludingPen(const double width) noexcept;

  void SetPos(const double x,const double y) noexcept;

  ///Set the rounded rect corner x radius
  void SetRadiusX(const double radius_x) noexcept;

  ///Set the rounded rect corner y radius
  void SetRadiusY(const double radius_y) noexcept;

  ///Set the rounded rect of the inner area
  void SetRoundedRect(const QRectF rect, const double radius_x, const double radius_y) noexcept;
  void SetRoundedRectIncludingPen(const QRectF rect, const double radius_x, const double radius_y) noexcept;

  void SetWidth(const double width) noexcept;
  void SetWidthIncludingPen(const double width) noexcept;

  void SetX(const double x) noexcept { SetPos(x,GetY()); }
  void SetY(const double y) noexcept { SetPos(GetX(),y); }

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
