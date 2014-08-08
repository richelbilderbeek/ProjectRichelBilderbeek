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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtroundedrectitem.h"

#include <cassert>
#include <QPainter>

#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtRoundedRectItem::QtRoundedRectItem(QGraphicsItem *parent)
 : QGraphicsRectItem(parent),
   m_signal_contour_pen_changed{},
   m_signal_focus_pen_changed{},
   m_signal_height_changed{},
   m_signal_pos_changed{},
   m_signal_radius_x_changed{},
   m_signal_radius_y_changed{},
   m_signal_width_changed{},
   m_contour_pen(QPen(QColor(0,0,0),0.0)),
   m_focus_pen(QPen(QColor(0,0,0),0.0,Qt::DashLine)),
   m_radius_x(4.0),
   m_radius_y(4.0)
{
  #ifndef NDEBUG
  Test();
  #endif

  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->SetContourPen(QPen(QColor(0,0,0),2.0));
  this->SetFocusPen(QPen(QColor(0,0,0),3.0,Qt::DashLine));
  const double height = 32.0;
  const double width = 64.0;
  this->SetInnerWidth(width);
  this->SetInnerHeight(height);
}

ribi::QtRoundedRectItem::~QtRoundedRectItem() noexcept
{
  //OK
}

double ribi::QtRoundedRectItem::GetInnerHeight() const noexcept
{
  const double pen_width = GetCurrentPen().widthF();
  return GetOuterHeight() -pen_width;
}

/*
QRectF ribi::QtRoundedRectItem::GetInnerRect() const noexcept
{
  const double pen_width
    = GetCurrentPen().widthF()
  ;
  //QGraphicsRectItem::rect() is the entire rect
  return GetOuterRect().adjusted(
     pen_width, pen_width,-pen_width,-pen_width);
}
*/

double ribi::QtRoundedRectItem::GetInnerWidth() const noexcept
{
  const double pen_width = GetCurrentPen().widthF();
  return GetOuterWidth() -pen_width;
}

/*
QRectF ribi::QtRoundedRectItem::GetOuterRect() const noexcept
{
  const QRectF r = QGraphicsRectItem::rect();
  return r;
}
*/

std::string ribi::QtRoundedRectItem::GetVersion() noexcept
{
  return "1.8";
}

std::vector<std::string> ribi::QtRoundedRectItem::GetVersionHistory() noexcept
{
  return {
    "2012-12-13: version 1.0: initial version",
    "2012-12-19: version 1.1: added use of pen, brush and focus-indicating pen",
    "2012-12-22: version 1.2: correctly uses the focus and regular pen, added contour pen",
    "2014-06-14: version 1.3: removed superfluous signal m_signal_item_has_updated",
    "2014-06-14: version 1.4: fixed issue #219",
    "2014-06-16: version 1.5: disallow setRect and setPos (use SetRoundedRect and SetPos instead), cooperation with QtRoundedRectItemDialog",
    "2014-06-22: version 1.6: allow setting the inner and outer rectangle",
    "2014-08-07: version 1.7: renamed IncludingPen member functions to Outer",
    "2014-08-08: version 1.8: removed using with rectangles from interface, as it led to incorrectness and confusion"
  };
}


void ribi::QtRoundedRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) noexcept
{
  QGraphicsRectItem::mouseMoveEvent(event);
  this->update();
  m_signal_pos_changed(this);
}

void ribi::QtRoundedRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) noexcept
{
  #ifndef NDEBUG
  const auto width_before = GetOuterWidth();
  const auto height_before = GetOuterWidth();
  #endif // NDEBUG

  painter->setBrush(brush());
  //The item can be selected by clicking on it, or can have focus by moving towards it
  const double width{GetOuterWidth()};
  //const double width{GetCurrentPen().widthF()};
  if (this->isSelected() || this->hasFocus())
  {
    painter->setPen(m_focus_pen);
    const double width_diff = width - m_focus_pen.widthF();
    painter->drawRoundedRect(
      QRectF(
        -0.5 * GetOuterWidth(),
        -0.5 * GetOuterHeight(),
         0.5 * GetOuterWidth(),
         0.5 * GetOuterHeight()
      ).adjusted( //Adjust to stay within rect
        ( 1.0 * width) - width_diff, //+ 1.0,
        ( 1.0 * width) - width_diff, //+ 1.0,
        (-1.0 * width) + width_diff, //- 1.0,
        (-1.0 * width) + width_diff  //- 1.0
      ),
      m_radius_x,
      m_radius_y
    );
  }
  else
  {
    painter->setPen(m_contour_pen);
    const double width_diff = width - m_contour_pen.widthF();
    painter->drawRoundedRect(
      QRectF(
        -0.5 * GetOuterWidth(),
        -0.5 * GetOuterHeight(),
         0.5 * GetOuterWidth(),
         0.5 * GetOuterHeight()
      //this->GetOuterRect()
      ).adjusted( //Adjust to stay within rect
        ( 1.0 * width) - width_diff, //+ 1.0,
        ( 1.0 * width) - width_diff, //+ 1.0,
        (-1.0 * width) + width_diff, //- 1.0,
        (-1.0 * width) + width_diff  //- 1.0
      ),
      m_radius_x,m_radius_y
    );
  }

  #ifndef NDEBUG
  const auto width_after = GetOuterWidth();
  const auto height_after = GetOuterHeight();
  assert(width_before == width_after);
  assert(height_before == height_after);
  #endif
}

void ribi::QtRoundedRectItem::SetContourPen(const QPen& pen) noexcept
{
  #ifndef NDEBUG
  const double inner_height_before = GetInnerHeight();
  const double inner_width_before = GetInnerWidth();
  #endif
  //if (m_contour_pen.widthF() != pen.widthF())
  if (m_contour_pen != pen)
  {
    const double height = GetInnerHeight();
    const double width = GetInnerWidth();
    m_contour_pen = pen;
    this->SetInnerHeight(height);
    this->SetInnerWidth(width);

    this->update();
    m_signal_contour_pen_changed(this);
  }
  #ifndef NDEBUG
  else
  {
    const double inner_height_after = GetInnerHeight();
    const double inner_width_after = GetInnerWidth();
    assert(std::abs(inner_height_before - inner_height_after) < 0.001);
    assert(std::abs(inner_width_before  - inner_width_after ) < 0.001);
  }
  #endif
  assert(std::abs(pen.widthF() - GetContourPen().widthF()) < 0.01);
}

void ribi::QtRoundedRectItem::SetFocusPen(const QPen& pen) noexcept
{
  #ifndef NDEBUG
  const double inner_height_before = GetInnerHeight();
  const double inner_width_before = GetInnerWidth();
  #endif
  if (m_focus_pen != pen)
  {
    const double height = GetInnerHeight();
    const double width = GetInnerWidth();
    m_focus_pen = pen;
    this->SetInnerHeight(height);
    this->SetInnerWidth(width);

    this->update();
    m_signal_focus_pen_changed(this);
  }
  #ifndef NDEBUG
  else
  {
    const double inner_height_after = GetInnerHeight();
    const double inner_width_after = GetInnerWidth();
    assert(std::abs(inner_height_before - inner_height_after) < 0.001);
    assert(std::abs(inner_width_before  - inner_width_after ) < 0.001);
  }
  #endif

  assert(std::abs(pen.widthF() - GetFocusPen().widthF()) < 0.01);
}

void ribi::QtRoundedRectItem::SetInnerHeight(const double height) noexcept
{
  SetOuterHeight(
    height + (2.0 * GetCurrentPen().widthF())
  );
  //assert(std::abs(height - GetInnerHeight()) < 2.0);
}

void ribi::QtRoundedRectItem::SetInnerPos(
  const double x,const double y
) noexcept
{
  //const double w{GetCurrentPen().widthF()};
  SetOuterPos(x,y);
}

/*
void ribi::QtRoundedRectItem::SetInnerRect(
  const QRectF& new_rect
) noexcept
{
  SetInnerWidth(new_rect.height());
  SetInnerHeight(new_rect.height());
  SetInnerPos(new_rect.topLeft());
}

void ribi::QtRoundedRectItem::SetInnerRoundedRect(
  const QRectF new_rect,
  const double radius_x,
  const double radius_y
) noexcept
{
  const auto pen_width = GetCurrentPen().widthF();
  SetOuterRoundedRect(
    new_rect.adjusted(-pen_width,-pen_width,pen_width,pen_width),
    radius_x,
    radius_y
  );
}
*/

void ribi::QtRoundedRectItem::SetInnerWidth(const double width) noexcept
{
  SetOuterWidth(
    width + (2.0 * GetCurrentPen().widthF())
  );
  //assert(std::abs(width - GetInnerWidth()) < 2.0);
}


void ribi::QtRoundedRectItem::SetOuterHeight(const double height) noexcept
{
  if (height != GetOuterHeight())
  {
    const auto w = GetOuterWidth();
    const auto h = height;
    const auto p = GetCurrentPen().widthF();
    QGraphicsRectItem::setRect(
      QRectF(
        (-0.5 * w) - p,
        (-0.5 * h) - p,
        ( 0.5 * w) + p,
        ( 0.5 * h) + p
      )
    );
    this->update();
    m_signal_height_changed(this);
  }
  //assert(std::abs(height - GetOuterHeight()) < 2.0);
}

/*
void ribi::QtRoundedRectItem::SetOuterRect(
  const QRectF& new_rect
) noexcept
{
  SetOuterWidth(new_rect.height());
  SetOuterHeight(new_rect.height());
  SetOuterPos(new_rect.topLeft());
}

void ribi::QtRoundedRectItem::SetOuterRoundedRect(
  const QRectF& new_rect,
  const double radius_x,
  const double radius_y
) noexcept
{
  SetOuterRect(new_rect);
  this->SetRadiusX(radius_x);
  this->SetRadiusY(radius_y);

}
*/


void ribi::QtRoundedRectItem::SetOuterWidth(const double width) noexcept
{
  if (width != GetOuterWidth())
  {
    const auto w = width;
    const auto h = GetOuterHeight();
    const auto p = GetCurrentPen().widthF();
    QGraphicsRectItem::setRect(
      QRectF(
        (-0.5 * w) - p,
        (-0.5 * h) - p,
        ( 0.5 * w) + p,
        ( 0.5 * h) + p
      )
    );
    this->update();
    m_signal_width_changed(this);
  }
  //assert(std::abs(width - GetOuterWidth()) < 2.0);
}

/*
void ribi::QtRoundedRectItem::SetOuterWidth(const double width) noexcept
{
  const auto current = this->GetOuterRect();
  const double current_width = current.width();
  if (current_width != width)
  {
    QGraphicsRectItem::setRect(
      QRectF(
        current.left(),
        current.top(),
        width,
        current.height()
      )
    );
    //Signals and update at SetRoundedRectIncludingPen
    m_signal_rect_changed(this);
    this->update();
  }
}
*/

void ribi::QtRoundedRectItem::SetOuterX(const double x) noexcept
{
  const double current_x = this->GetOuterX();
  if (current_x != x)
  {
    const auto current_pos = this->GetOuterPos();
    QGraphicsRectItem::setPos(
      x,
      current_pos.y()
    );

    this->update();
    m_signal_pos_changed(this);
  }
}

void ribi::QtRoundedRectItem::SetOuterY(const double y) noexcept
{
  const double current_y = this->GetOuterY();
  if (current_y != y)
  {
    const auto current_pos = this->GetOuterPos();
    QGraphicsRectItem::setPos(
      current_pos.x(),
      y
    );
    this->update();
    m_signal_pos_changed(this);
  }
}

void ribi::QtRoundedRectItem::SetRadiusX(const double radius_x) noexcept
{
  if (m_radius_x != radius_x)
  {
    m_radius_x = radius_x;
    this->update();
    m_signal_radius_x_changed(this);
  }
  assert(radius_x == GetRadiusX());
}

void ribi::QtRoundedRectItem::SetRadiusY(const double radius_y) noexcept
{
  if (m_radius_y != radius_y)
  {
    m_radius_y = radius_y;
    this->update();
    m_signal_radius_y_changed(this);
  }
  assert(radius_y == GetRadiusY());
}

bool ribi::operator==(const QtRoundedRectItem& lhs, const QtRoundedRectItem& rhs) noexcept
{
  return
       lhs.GetContourPen() == rhs.GetContourPen()
    && lhs.GetFocusPen() == lhs.GetFocusPen()
    && lhs.GetRadiusX() == lhs.GetRadiusX()
    && lhs.GetRadiusY() == lhs.GetRadiusY()
    && lhs.GetInnerWidth() == lhs.GetInnerWidth()
    && lhs.GetInnerHeight() == lhs.GetInnerHeight()
    //&& lhs.GetInnerRect() == lhs.GetInnerRect()
  ;
}

bool ribi::operator!=(const QtRoundedRectItem& lhs, const QtRoundedRectItem& rhs) noexcept
{
  return !(lhs == rhs);
}
