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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#include <QGraphicsRectItem>
#include <QPen>
#pragma GCC diagnostic pop

namespace ribi {

///Rounded rectangle item
struct QtRoundedRectItem : public QGraphicsRectItem
{
  QtRoundedRectItem(QGraphicsItem *parent = 0);

  virtual ~QtRoundedRectItem() noexcept {}

  ///Get the pen by which the contour is drawn
  const QPen& GetContourPen() const { return m_contour_pen; }

  ///Get the pen by which focus is indicated
  const QPen& GetFocusPen() const { return m_focus_pen; }

  ///Get the rounded rect corner x radius
  double GetRadiusX() const { return m_radius_x; }

  ///Get the rounded rect corner y radius
  double GetRadiusY() const { return m_radius_y; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

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

} //~namespace ribi

#endif // QTROUNDEDRECTITEM_H
