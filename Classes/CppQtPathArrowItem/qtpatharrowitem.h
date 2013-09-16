//---------------------------------------------------------------------------
/*
QtPathArrowItem, an arrow QGraphicsItem with one or more midpoints
Copyright (C) 2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtPathArrowItem.htm
//---------------------------------------------------------------------------
#ifndef QTPATHARROWITEM_H
#define QTPATHARROWITEM_H

#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include <QGraphicsLineItem>
#include <QPen>
#pragma GCC diagnostic pop

namespace ribi {

///An arrow item that has one or more midpoints
struct QtPathArrowItem : public QGraphicsItem
{
  typedef QtPathArrowItem This;

  QtPathArrowItem(
    const QPointF& tail_pos,
    const bool tail,
    const std::vector<QPointF>& mid_pos,
    const bool head,
    const QPointF& head_pos,
    QGraphicsItem *parent = 0);

  virtual ~QtPathArrowItem() noexcept {}

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Is there an arrow at the 'to' point (x2,y2)?
  bool HasHead() const { return m_head; }

  ///Is there an arrow at the 'from' point (x1,y1)?
  bool HasTail() const { return m_tail; }

  ///Respond to key presses
  void keyPressEvent(QKeyEvent *event);

  ///Set the path the arrow has to take
  void SetArrowPath(
    const QPointF& tail_pos,
    const std::vector<QPointF>& mid_pos,
    const QPointF& head_pos);

  ///Set the pen used to show focus
  void SetFocusPen(const QPen& pen) { m_focus_pen = pen; }

  ///Set the regular pen used to draw the arrow
  void SetPen(const QPen& pen) { m_pen = pen; }

  ///Set if the arrow has a point at the head
  void SetHasHead(const bool has_head) { m_head = has_head; }

  ///Set if the arrow has a point at the tail
  void SetHasTail(const bool has_tail) { m_tail = has_tail; }

  ///Signal to request a scene update, because this item has moved/changed
  boost::signals2::signal<void (This*)> m_signal_item_requests_scene_update;

protected:
  QRectF boundingRect() const;
  void hoverEnterEvent(QGraphicsSceneHoverEvent *);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
  QPainterPath shape() const;

private:

  ///The extra width given to the line for easier clicking
  static const double m_click_easy_width;

  ///The arrow used for indicating focus
  QPen m_focus_pen;

  ///Show arrow at head
  bool m_head;

  ///The position of the head
  QPointF m_head_pos;

  ///The positions between tail (lower indices) and tail (higher indices)
  std::vector<QPointF> m_mid_pos;

  ///The regular pen
  QPen m_pen;

  ///Show arrow at tail
  bool m_tail;

  ///The position of the head
  QPointF m_tail_pos;

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  static double GetAngle(const double dx, const double dy);

};

} //~namespace ribi

#endif // QTPATHARROWITEM_H
