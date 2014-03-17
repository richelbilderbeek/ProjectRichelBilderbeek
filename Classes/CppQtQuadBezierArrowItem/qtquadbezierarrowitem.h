//---------------------------------------------------------------------------
/*
QtQuadBezierArrowItem, an quadratic Bezier arrow QGraphicsItem
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
//From http://www.richelbilderbeek.nl/CppQtQuadBezierArrowItem.htm
//---------------------------------------------------------------------------
#ifndef QTQUADBEZIERARROWITEM_H
#define QTQUADBEZIERARROWITEM_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <QGraphicsPathItem>
#include <QPen>
#pragma GCC diagnostic pop

namespace ribi {

///The QtQuadBezierArrowItem is a QGraphicsItem that
///follows the three QGraphicsItem positions
///If mid is nullptr, the line will be straight
struct QtQuadBezierArrowItem : public QGraphicsItem
{
  QtQuadBezierArrowItem(
    const QGraphicsItem* const from,
    const bool tail,
    const QGraphicsItem* const mid, HIERO
    const bool head,
    const QGraphicsItem* const to,
    QGraphicsItem* parent = 0);

  virtual ~QtQuadBezierArrowItem() noexcept {}

  ///Get the QPen used to indicate that the arrow has focus
  const QPen& GetFocusPen() const noexcept { return m_focus_pen; }

  ///Get the item where the arrow originates from
  ///(would the arrow and tail heads not be reversible)
  const QGraphicsItem* GetFromItem() const noexcept { return m_from; }

  ///Obtain the head point of the arrow, on the edge of the rectangle m_from
  QPointF GetHead() const noexcept;

  ///Get the item where the arrow pass through in the middle
  const QGraphicsItem* GetMidItem() const noexcept { return m_mid; }

  ///Get the QPen used to draw a regular, non-focused, arrow
  const QPen& GetPen() const noexcept { return m_pen; }

  ///Obtain the tail point of the arrow, on the edge of the rectangle m_from
  QPointF GetTail() const noexcept;

  ///Get the item where the arrow points to
  ///(would the arrow and tail heads not be reversible)
  const QGraphicsItem* GetToItem() const noexcept { return m_to; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Is there an arrow at the 'to' point (x2,y2)?
  bool HasHead() const noexcept { return m_head; }

  ///Is there an arrow at the 'from' point (x1,y1)?
  bool HasTail() const noexcept { return m_tail; }

  ///Respond to key press
  void keyPressEvent(QKeyEvent *event);

  ///Respond to mouse press
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  ///The rectangle that containg the item, used for rough calculations like
  ///collision detection
  virtual QRectF boundingRect() const;

  ///Paint a QtQuadBezierArrowItem
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *);

  ///Set if the arrow has a point at the head
  void SetHasHead(const bool has_head) noexcept;

  ///Set if the arrow has a point at the tail
  void SetHasTail(const bool has_tail) noexcept;

  ///Set the pen used to show focus
  void SetFocusPen(const QPen& pen) noexcept { m_focus_pen = pen; }

  ///Set the regular pen used to draw the arrow
  void SetPen(const QPen& pen) noexcept { m_pen = pen; }

  ///More precise shape compared to boundingRect
  ///In this example, it is redefined to ease selecting those thin lines
  QPainterPath shape() const;

  ///Emitted when the item has called
  boost::signals2::signal<void(const QtQuadBezierArrowItem*)> m_signal_item_updated;

  protected:
  ///Change the cursor when the user moves the mouse cursor in the bounding rectangle
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  private:
  ///The extra width given to the line for easier clicking
  static const double m_click_easy_width;

  ///The arrow used for indicating focus
  QPen m_focus_pen;

  ///The item where the arrow originates from
  const QGraphicsItem* const m_from;

  ///Show arrow at head
  bool m_head;

  ///The item where the arrow pass through in the middle
  const QGraphicsItem* const m_mid;

  ///The regular pen
  QPen m_pen;

  ///Show arrow at tail
  bool m_tail;

  ///The item where the arrow points to
  ///(would the arrow and tail heads not be reversible)
  const QGraphicsItem* const m_to;

  ///Obtain point 'beyond'
  QPointF GetBeyond() const noexcept;

  ///Obtain point 'center'
  QPointF GetCenter() const noexcept;

  QPointF pos() const = delete;
};

} //~namespace ribi

#endif // QTQUADBEZIERARROWITEM_H
