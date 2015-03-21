//---------------------------------------------------------------------------
/*
QtQuadBezierArrowItem, an quadratic Bezier arrow QGraphicsItem
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
///The QGraphicsItems supplied will not be deleted by QtQuadBezierArrowItem
struct QtQuadBezierArrowItem : public QGraphicsItem
{
  QtQuadBezierArrowItem(
    QGraphicsItem* const from,
    const bool tail,
    QGraphicsItem* const mid,
    const bool head,
    QGraphicsItem* const to,
    QGraphicsItem* parent = 0
  ) noexcept;

  virtual ~QtQuadBezierArrowItem() noexcept {}

  ///The rectangle that containg the item, used for rough calculations like
  ///collision detection
  QRectF boundingRect() const override final;

  ///Get the QPen used to indicate that the arrow has focus
  const QPen& GetFocusPen() const noexcept { return m_focus_pen; }

  ///Get the item where the arrow originates from
  ///(would the arrow and tail heads not be reversible)
  ///Use the specific GetFrom* member functions to modify this item
  const QGraphicsItem* GetFromItem() const noexcept { return m_from; }
  double GetFromX() const noexcept { return m_from->x(); }
  double GetFromY() const noexcept { return m_from->y(); }

  ///Obtain the head point of the arrow, on the edge of the rectangle m_from
  QPointF GetHead() const noexcept;

  ///Get the item where the arrow pass through in the middle
  ///Use the specific GetMid* member functions to modify this item
  const QGraphicsItem* GetMidItem() const noexcept { return m_mid; }
  double GetMidX() const noexcept { return m_mid->x(); }
  double GetMidY() const noexcept { return m_mid->y(); }

  ///Get the QPen used to draw a regular, non-focused, arrow
  const QPen& GetPen() const noexcept { return m_pen; }

  ///Obtain the tail point of the arrow, on the edge of the rectangle m_from
  QPointF GetTail() const noexcept;

  ///Get the item where the arrow points to
  ///(would the arrow and tail heads not be reversible)
  ///Use the specific GetTo* member functions to modify this item
  const QGraphicsItem* GetToItem() const noexcept { return m_to; }
  double GetToX() const noexcept { return m_to->x(); }
  double GetToY() const noexcept { return m_to->y(); }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Is there an arrow at the 'to' point (x2,y2)?
  bool HasHead() const noexcept { return m_head; }

  ///Is there an arrow at the 'from' point (x1,y1)?
  bool HasTail() const noexcept { return m_tail; }

  ///Respond to key press
  void keyPressEvent(QKeyEvent *event) noexcept override final;

  ///Respond to mouse press
  void mousePressEvent(QGraphicsSceneMouseEvent *event) noexcept override final;

  ///Paint a QtQuadBezierArrowItem
  void paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *) noexcept override final;

  ///Set if the arrow has a point at the head
  void SetHasHead(const bool has_head) noexcept;

  ///Set if the arrow has a point at the tail
  void SetHasTail(const bool has_tail) noexcept;

  ///Set the pen used to show focus
  void SetFocusPen(const QPen& pen) noexcept;

  ///Set the position of the from item
  void SetFromPos(const QPointF& pos) noexcept;
  void SetFromPos(const double x, const double y) noexcept { SetFromPos(QPointF(x,y)); }
  void SetFromX(const double& x) noexcept { SetFromPos(x,GetFromY()); }
  void SetFromY(const double& y) noexcept { SetFromPos(GetFromX(),y); }

  ///Set the position of the middle item
  void SetMidPos(const QPointF& pos) noexcept;
  void SetMidPos(const double x, const double y) noexcept { SetMidPos(QPointF(x,y)); }
  void SetMidX(const double& x) noexcept { SetMidPos(x,GetMidY()); }
  void SetMidY(const double& y) noexcept { SetMidPos(GetMidX(),y); }

  ///Set the regular pen used to draw the arrow
  void SetPen(const QPen& pen) noexcept;

  void SetShowBoundingRect(const bool show_bounding_rect) noexcept;

  ///Set the position of the from item
  void SetToPos(const QPointF& pos) noexcept;
  void SetToPos(const double x, const double y) noexcept { SetToPos(QPointF(x,y)); }
  void SetToX(const double& x) noexcept { SetToPos(x,GetToY()); }
  void SetToY(const double& y) noexcept { SetToPos(GetToX(),y); }

  ///More precise shape compared to boundingRect
  ///In this example, it is redefined to ease selecting those thin lines
  QPainterPath shape() const noexcept override final;

  ///Emitted when the item has called
  boost::signals2::signal<void(const QtQuadBezierArrowItem*)> m_signal_item_updated;

  protected:
  ///Change the cursor when the user moves the mouse cursor in the bounding rectangle
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event) noexcept override final;

  private:
  ///The extra width given to the line for easier clicking
  static const double m_click_easy_width;

  ///The arrow used for indicating focus
  QPen m_focus_pen;

  ///The item where the arrow originates from
  QGraphicsItem* const m_from;

  ///Show arrow at head
  bool m_head;

  ///The item where the arrow pass through in the middle
  QGraphicsItem* const m_mid;

  ///The regular pen
  QPen m_pen;

  ///Show the bounding rectangle, used in debugging
  bool m_show_bounding_rect;

  ///Show arrow at tail
  bool m_tail;

  ///The item where the arrow points to
  ///(would the arrow and tail heads not be reversible)
  QGraphicsItem* const m_to;

  ///Obtain point 'beyond'
  QPointF GetBeyond() const noexcept;

  ///Obtain point 'center'
  /*

  F
   \
    \
  C  M  B
    /
   /
  T

  F = From
  T = To
  M = Mid
  C = Center
  B = Beyond

  */
  QPointF GetCenter() const noexcept;

  QPointF pos() const = delete;
  void setPos(const QPointF&) = delete;
  void setX(const double&) = delete;
  void setY(const double&) = delete;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const QtQuadBezierArrowItem& arrow) noexcept;
};

std::ostream& operator<<(std::ostream& os, const QtQuadBezierArrowItem& arrow) noexcept;
bool operator==(const QtQuadBezierArrowItem& lhs, const QtQuadBezierArrowItem& rhs) noexcept;

} //~namespace ribi

#endif // QTQUADBEZIERARROWITEM_H
