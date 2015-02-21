//---------------------------------------------------------------------------
/*
QtArrowItem, an arrow QGraphicsItem
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtArrowItem.htm
//---------------------------------------------------------------------------
#ifndef QTARROWITEM_H
#define QTARROWITEM_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#include <QGraphicsLineItem>
#include <QPen>
#pragma GCC diagnostic pop

namespace ribi {

///An arrow QGraphicsItem
//From http://www.richelbilderbeek.nl/CppQtArrowItem.htm
struct QtArrowItem : public QGraphicsLineItem
{
  typedef QtArrowItem This;

  QtArrowItem(
    const double x1,
    const double y1,
    const bool tail,
    const double x2,
    const double y2,
    const bool head,
    QGraphicsItem* parent = 0);

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Is there an arrow at the 'to' point (x2,y2)?
  bool HasHead() const noexcept { return m_head; }

  ///Is there an arrow at the 'from' point (x1,y1)?
  bool HasTail() const noexcept { return m_tail; }

  ///Respond to key presses
  void keyPressEvent(QKeyEvent *event);

  ///Set the distance in pixels the user is allowed to be distance from the
  ///arrow head/tail to change it
  void SetArrowHeadClickingDistance(const double manhattan_distance) noexcept;

  ///Set the pen used to show focus
  void SetFocusPen(const QPen& pen) noexcept { m_focus_pen = pen; }

  ///Set if the arrow has a point at the head
  void SetHasHead(const bool has_head) noexcept { m_head = has_head; }

  ///Set if the arrow has a point at the tail
  void SetHasTail(const bool has_tail) noexcept { m_tail = has_tail; }

  ///Set the position of the head
  void SetHeadPos(const double x, const double y) noexcept;

  ///Set the regular pen used to draw the arrow
  void SetPen(const QPen& pen) noexcept { m_pen = pen; }

  ///Set the position of the tail
  void SetTailPos(const double x, const double y) noexcept;

  ///Signal emitted when this item has changed and the scene needs to be updated
  boost::signals2::signal<void (This*)> m_signal_item_requests_scene_update;

protected:
  virtual ~QtArrowItem() noexcept {}

  QRectF boundingRect() const;
  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *);
  QPainterPath shape() const;

private:

  ///Set the distance in pixels the user is allowed to be distance from the
  ///arrow head/tail to change it
  double m_arrow_head_clicking_distance;

  ///The extra width given to the line for easier clicking
  static const double m_click_easy_width;

  ///The arrow used for indicating focus
  QPen m_focus_pen;

  ///Show arrow at head
  bool m_head;

  ///The regular pen
  QPen m_pen;

  ///Show arrow at tail
  bool m_tail;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTARROWITEM_H
