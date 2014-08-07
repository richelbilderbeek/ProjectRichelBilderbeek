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
#include <sstream>

#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtRoundedRectItem::QtRoundedRectItem(QGraphicsItem *parent)
 : QGraphicsRectItem(parent),
   m_signal_contour_pen_changed{},
   m_signal_focus_pen_changed{},
   m_signal_pos_changed{},
   m_signal_radius_x_changed{},
   m_signal_radius_y_changed{},
   m_signal_rect_changed{},
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
  this->SetInnerRoundedRect(QRectF(-width/2.0,-height/2.0,width,height),m_radius_x,m_radius_y);

}

ribi::QtRoundedRectItem::~QtRoundedRectItem() noexcept
{
  //OK
}

QRectF ribi::QtRoundedRectItem::GetInnerRect() const noexcept
{
  const double pen_width
    = std::max(m_contour_pen.widthF(),m_focus_pen.widthF())
  ;
  //QGraphicsRectItem::rect() is the entire rect
  return GetOuterRect().adjusted(
     pen_width, pen_width,-pen_width,-pen_width);
}

QRectF ribi::QtRoundedRectItem::GetOuterRect() const noexcept
{
  const QRectF r = QGraphicsRectItem::rect();
  return r;
}

std::string ribi::QtRoundedRectItem::GetVersion() noexcept
{
  return "1.7";
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
    "2014-06-22: version 1.6: allow setting the inner and outer rectangle"
    "2014-08-07: version 1.7: renamed IncludingPen member functions to Outer"
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
  const auto rect_before = GetOuterRect();
  #endif // NDEBUG

  painter->setBrush(brush());
  //The item can be selected by clicking on it, or can have focus by moving towards it
  const double width = std::max(m_contour_pen.widthF(),m_focus_pen.widthF());
  if (this->isSelected() || this->hasFocus())
  {
    painter->setPen(m_focus_pen);
    const double width_diff = width - m_focus_pen.widthF();
    painter->drawRoundedRect(
      GetOuterRect().adjusted( //Adjust to stay within rect
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
      this->GetOuterRect().adjusted( //Adjust to stay within rect
        ( 1.0 * width) - width_diff, //+ 1.0,
        ( 1.0 * width) - width_diff, //+ 1.0,
        (-1.0 * width) + width_diff, //- 1.0,
        (-1.0 * width) + width_diff  //- 1.0
      ),
      m_radius_x,m_radius_y
    );
  }

  #ifndef NDEBUG
  const auto rect_after = GetOuterRect();
  assert(rect_before == rect_after);
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
    height + (2.0 * std::max(m_contour_pen.widthF(),m_focus_pen.widthF()))
  );
  assert(std::abs(height - GetInnerHeight()) < 2.0);
}

void ribi::QtRoundedRectItem::SetInnerPos(
  const double x,const double y
) noexcept
{
  const double w{std::max(m_contour_pen.widthF(),m_focus_pen.widthF())};
  SetOuterPos(x-w,y-w);
}

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
  const auto pen_width = std::max(m_contour_pen.widthF(),m_focus_pen.widthF());
  SetOuterRoundedRect(
    new_rect.adjusted(-pen_width,-pen_width,pen_width,pen_width),
    radius_x,
    radius_y
  );
}

void ribi::QtRoundedRectItem::SetInnerWidth(const double width) noexcept
{
  SetOuterWidth(
    width + (2.0 * std::max(m_contour_pen.widthF(),m_focus_pen.widthF()))
  );
  assert(std::abs(width - GetInnerWidth()) < 2.0);
}

void ribi::QtRoundedRectItem::SetOuterHeight(const double height) noexcept
{
  const auto current = this->GetOuterRect();
  const double current_height = current.height();
  if (current_height != height)
  {
    QGraphicsRectItem::setRect(
      QRectF(
        current.left(),
        current.top(),
        current.width(),
        height
      )
    );
    this->update();
    m_signal_rect_changed(this);
  }
  assert(std::abs(height - GetOuterHeight()) < 2.0);
}


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

void ribi::QtRoundedRectItem::SetOuterX(const double x) noexcept
{
  const double current_x = this->GetOuterX();
  if (current_x != x)
  {
    const auto current_rect = this->GetOuterRect();
    QGraphicsRectItem::setRect(
      x,
      current_rect.y(),
      current_rect.width(),
      current_rect.height()
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
    const auto current_rect = this->GetOuterRect();
    QGraphicsRectItem::setRect(
      current_rect.x(),
      y,
      current_rect.width(),
      current_rect.height()
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




#ifndef NDEBUG
void ribi::QtRoundedRectItem::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{true};
  if (verbose) { TRACE("Construction"); }
  {
    QtRoundedRectItem();
  }
  QtRoundedRectItem i;
  if (verbose) { TRACE("SetOuterX and GetOuterX must be symmetric"); }
  {
    const auto old_x = i.GetOuterX();
    const auto new_x = old_x + 10.0;
    i.SetOuterX(new_x);
    assert(std::abs(i.GetOuterX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("SetOuterY and GetOuterY must be symmetric"); }
  {
    const auto old_y = i.GetOuterY();
    const auto new_y = old_y + 10.0;
    i.SetOuterY(new_y);
    assert(std::abs(i.GetOuterY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("SetOuterPos and GetOuterPos must be symmetric"); }
  {
    const auto old_pos = i.GetOuterPos();
    const auto new_pos = old_pos + QPointF(10.0,10.0);
    i.SetOuterPos(new_pos);
    assert(std::abs(i.GetOuterPos().x() - new_pos.x()) < 2.0);
    assert(std::abs(i.GetOuterPos().y() - new_pos.y()) < 2.0);
  }
  if (verbose) { TRACE("SetOuterWidth and GetOuterWidth must be symmetric"); }
  {
    const auto old_width = i.GetOuterWidth();
    const auto new_width = old_width + 10.0;
    i.SetOuterWidth(new_width);
    assert(std::abs(i.GetOuterWidth() - new_width) < 2.0);
  }
  if (verbose) { TRACE("SetOuterHeight and GetOuterHeight must be symmetric"); }
  {
    const auto old_height = i.GetOuterHeight();
    const auto new_height = old_height + 10.0;
    i.SetOuterHeight(new_height);
    assert(std::abs(i.GetOuterHeight() - new_height) < 2.0);
  }
  if (verbose) { TRACE("SetOuterRect and GetOuterRect must be symmetric"); }
  {
    const auto old_rect = i.GetOuterRect();
    const auto new_rect = old_rect.adjusted(-10.0,-10.0,10.0,10.0);
    i.SetOuterRect(new_rect);
    assert(std::abs(i.GetOuterRect().width() - new_rect.width()) < 2.0);
    assert(std::abs(i.GetOuterRect().height() - new_rect.height()) < 2.0);
    assert(std::abs(i.GetOuterRect().left() - new_rect.left()) < 2.0);
    assert(std::abs(i.GetOuterRect().top() - new_rect.top()) < 2.0);
  }
  if (verbose) { TRACE("SetOuterRoundedRect and GetOuterRect must be symmetric"); }
  {
    const auto old_radius_x = i.GetRadiusX();
    const auto old_radius_y = i.GetRadiusY();
    const auto old_rect = i.GetOuterRect();
    const auto new_radius_x = old_radius_x + 5.0;
    const auto new_radius_y = old_radius_y + 5.0;
    const auto new_rect = old_rect.adjusted(-10.0,-10.0,10.0,10.0);
    i.SetOuterRoundedRect(new_rect,new_radius_x, new_radius_y);
    assert(std::abs(i.GetOuterRect().width() - new_rect.width()) < 2.0);
    assert(std::abs(i.GetOuterRect().height() - new_rect.height()) < 2.0);
    assert(std::abs(i.GetOuterRect().left() - new_rect.left()) < 2.0);
    assert(std::abs(i.GetOuterRect().top() - new_rect.top()) < 2.0);
    assert(std::abs(i.GetRadiusX() - new_radius_x) < 2.0);
    assert(std::abs(i.GetRadiusY() - new_radius_y) < 2.0);
  }
  if (verbose) { TRACE("SetInnerX and GetInnerX must be symmetric"); }
  {
    const auto old_x = i.GetInnerX();
    const auto new_x = old_x + 10.0;
    i.SetInnerX(new_x);
    assert(std::abs(i.GetInnerX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("SetInnerY and GetInnerY must be symmetric"); }
  {
    const auto old_y = i.GetInnerY();
    const auto new_y = old_y + 10.0;
    i.SetInnerY(new_y);
    assert(std::abs(i.GetInnerY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("SetInnerPos and GetInnerPos must be symmetric"); }
  {
    const auto old_pos = i.GetInnerPos();
    const auto new_pos = old_pos + QPointF(10.0,10.0);
    i.SetInnerPos(new_pos);
    assert(std::abs(i.GetInnerPos().x() - new_pos.x()) < 2.0);
    assert(std::abs(i.GetInnerPos().y() - new_pos.y()) < 2.0);
  }
  if (verbose) { TRACE("SetInnerHeight and GetInnerHeight must be symmetric"); }
  {
    const auto old_height = i.GetInnerHeight();
    const auto new_height = old_height + 10.0;
    i.SetInnerHeight(new_height);
    assert(std::abs(i.GetInnerHeight() - new_height) < 2.0);
  }
  if (verbose) { TRACE("SetInnerWidth and GetInnerWidth must be symmetric"); }
  {
    const auto old_width = i.GetInnerWidth();
    const auto new_width = old_width + 10.0;
    i.SetInnerWidth(new_width);
    assert(std::abs(i.GetInnerWidth() - new_width) < 2.0);
  }
  if (verbose) { TRACE("SetInnerRect and GetInnerRect must be symmetric"); }
  {
    const auto old_rect = i.GetInnerRect();
    const auto new_rect = old_rect.adjusted(-10.0,-10.0,10.0,10.0);
    i.SetInnerRect(new_rect);
    assert(std::abs(i.GetInnerRect().width() - new_rect.width()) < 2.0);
    assert(std::abs(i.GetInnerRect().height() - new_rect.height()) < 2.0);
    assert(std::abs(i.GetInnerRect().left() - new_rect.left()) < 2.0);
    assert(std::abs(i.GetInnerRect().top() - new_rect.top()) < 2.0);
  }
  if (verbose) { TRACE("SetInnerRoundedRect and GetInnerRect must be symmetric"); }
  {
    const auto old_radius_x = i.GetRadiusX();
    const auto old_radius_y = i.GetRadiusY();
    const auto old_rect = i.GetInnerRect();
    const auto new_radius_x = old_radius_x + 5.0;
    const auto new_radius_y = old_radius_y + 5.0;
    const auto new_rect = old_rect.adjusted(-10.0,-10.0,10.0,10.0);
    i.SetInnerRoundedRect(new_rect,new_radius_x, new_radius_y);
    assert(std::abs(i.GetInnerRect().width() - new_rect.width()) < 2.0);
    assert(std::abs(i.GetInnerRect().height() - new_rect.height()) < 2.0);
    assert(std::abs(i.GetInnerRect().left() - new_rect.left()) < 2.0);
    assert(std::abs(i.GetInnerRect().top() - new_rect.top()) < 2.0);
    assert(std::abs(i.GetRadiusX() - new_radius_x) < 2.0);
    assert(std::abs(i.GetRadiusY() - new_radius_y) < 2.0);
  }
}
#endif

bool ribi::operator==(const QtRoundedRectItem& lhs, const QtRoundedRectItem& rhs) noexcept
{
  return
       lhs.GetContourPen() == rhs.GetContourPen()
    && lhs.GetFocusPen() == lhs.GetFocusPen()
    && lhs.GetRadiusX() == lhs.GetRadiusX()
    && lhs.GetRadiusY() == lhs.GetRadiusY()
    && lhs.GetInnerRect() == lhs.GetInnerRect()
  ;
}

bool ribi::operator!=(const QtRoundedRectItem& lhs, const QtRoundedRectItem& rhs) noexcept
{
  return !(lhs == rhs);
}
