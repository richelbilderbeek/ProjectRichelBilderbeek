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
  const double height = 24.48;
  const double width = 32.64;
  this->SetRoundedRect(QRectF(-width/2.0,-height/2.0,width,height),m_radius_x,m_radius_y);

}

ribi::QtRoundedRectItem::~QtRoundedRectItem() noexcept
{
  //OK
}


const QPen& ribi::QtRoundedRectItem::GetContourPen() const noexcept
{
  return m_contour_pen;
}

const QPen& ribi::QtRoundedRectItem::GetFocusPen() const noexcept
{
  return m_focus_pen;
}

double ribi::QtRoundedRectItem::GetHeight() const noexcept
{
  return GetRect().height();
}

double ribi::QtRoundedRectItem::GetHeightIncludingPen() const noexcept
{
  return GetRectIncludingPen().height();
}

QPointF ribi::QtRoundedRectItem::GetPos() const noexcept
{
  return QGraphicsRectItem::pos();
}

double ribi::QtRoundedRectItem::GetRadiusX() const noexcept
{
  return m_radius_x;
}

double ribi::QtRoundedRectItem::GetRadiusY() const noexcept
{
  return m_radius_y;
}

QRectF ribi::QtRoundedRectItem::GetRect() const noexcept
{
  const double pen_width
    = std::max(m_contour_pen.widthF(),m_focus_pen.widthF())
  ;
  //QGraphicsRectItem::rect() is the entire rect
  return GetRectIncludingPen().adjusted(
     pen_width, pen_width,-pen_width,-pen_width);
}

QRectF ribi::QtRoundedRectItem::GetRectIncludingPen() const noexcept
{
  const QRectF r = QGraphicsRectItem::rect();
  return r;
}

std::string ribi::QtRoundedRectItem::GetVersion() noexcept
{
  return "1.6";
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
  };
}

double ribi::QtRoundedRectItem::GetWidth() const noexcept
{
  return GetRect().width();
}

double ribi::QtRoundedRectItem::GetWidthIncludingPen() const noexcept
{
  return GetRectIncludingPen().width();
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
  const auto rect_before = GetRectIncludingPen();
  #endif // NDEBUG

  painter->setBrush(brush());
  //The item can be selected by clicking on it, or can have focus by moving towards it
  const double width = std::max(m_contour_pen.widthF(),m_focus_pen.widthF());
  if (this->isSelected() || this->hasFocus())
  {
    painter->setPen(m_focus_pen);
    const double width_diff = width - m_focus_pen.widthF();
    painter->drawRoundedRect(
      GetRectIncludingPen().adjusted( //Adjust to stay within rect
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
      this->GetRectIncludingPen().adjusted( //Adjust to stay within rect
        ( 1.0 * width) - width_diff, //+ 1.0,
        ( 1.0 * width) - width_diff, //+ 1.0,
        (-1.0 * width) + width_diff, //- 1.0,
        (-1.0 * width) + width_diff  //- 1.0
      ),
      m_radius_x,m_radius_y
    );
  }

  #ifndef NDEBUG
  const auto rect_after = GetRectIncludingPen();
  assert(rect_before == rect_after);
  #endif
}

void ribi::QtRoundedRectItem::SetContourPen(const QPen& pen) noexcept
{
  #ifndef NDEBUG
  const double inner_height_before = GetHeight();
  const double inner_width_before = GetWidth();
  #endif
  //if (m_contour_pen.widthF() != pen.widthF())
  if (m_contour_pen != pen)
  {
    const double height = GetHeight();
    const double width = GetWidth();
    m_contour_pen = pen;
    this->SetHeight(height);
    this->SetWidth(width);

    this->update();
    m_signal_contour_pen_changed(this);
  }
  #ifndef NDEBUG
  else
  {
    const double inner_height_after = GetHeight();
    const double inner_width_after = GetWidth();
    assert(std::abs(inner_height_before - inner_height_after) < 0.001);
    assert(std::abs(inner_width_before  - inner_width_after ) < 0.001);
  }
  #endif
  assert(std::abs(pen.widthF() - GetContourPen().widthF()) < 0.01);
}

void ribi::QtRoundedRectItem::SetFocusPen(const QPen& pen) noexcept
{
  #ifndef NDEBUG
  const double inner_height_before = GetHeight();
  const double inner_width_before = GetWidth();
  #endif
  if (m_focus_pen != pen)
  {
    const double height = GetHeight();
    const double width = GetWidth();
    m_focus_pen = pen;
    this->SetHeight(height);
    this->SetWidth(width);

    this->update();
    m_signal_focus_pen_changed(this);
  }
  #ifndef NDEBUG
  else
  {
    const double inner_height_after = GetHeight();
    const double inner_width_after = GetWidth();
    assert(std::abs(inner_height_before - inner_height_after) < 0.001);
    assert(std::abs(inner_width_before  - inner_width_after ) < 0.001);
  }
  #endif

  assert(std::abs(pen.widthF() - GetFocusPen().widthF()) < 0.01);
}

void ribi::QtRoundedRectItem::SetHeight(const double height) noexcept
{
  SetHeightIncludingPen(
    height + (2.0 * std::max(m_contour_pen.widthF(),m_focus_pen.widthF()))
  );
  assert(std::abs(height - GetHeight()) < 2.0);
}

void ribi::QtRoundedRectItem::SetHeightIncludingPen(const double height) noexcept
{
  const auto current = this->GetRectIncludingPen();
  const double current_height = current.height();
  if (current_height != height)
  {

    SetRoundedRectIncludingPen(
      QRectF(
        current.left(),
        current.top(),
        current.width(),
        height
      ),
      this->GetRadiusX(),
      this->GetRadiusY()
    );
    //this->update();
    //m_signal_rect_changed(this);
  }
  assert(std::abs(height - GetHeightIncludingPen()) < 2.0);
}

void ribi::QtRoundedRectItem::SetPos(const double x,const double y) noexcept
{
  const double current_x = this->GetPos().x();
  const double current_y = this->GetPos().y();
  if (current_x != x || current_y != y)
  {
    QGraphicsRectItem::setPos(x,y);
    this->update();
    m_signal_pos_changed(this);
  }
  #ifndef NDEBUG
  if(std::abs(y - GetPos().y()) >= 0.01)
  {
    TRACE("ERROR");
    TRACE(y);
    TRACE(GetPos().y());
    TRACE("BREAK");
  }
  #endif

  assert(std::abs(x - GetPos().x()) < 0.01);
  assert(std::abs(y - GetPos().y()) < 0.01);
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


void ribi::QtRoundedRectItem::SetRoundedRect(
  const QRectF new_rect,
  const double radius_x,
  const double radius_y
) noexcept
{
  const auto pen_width = std::max(m_contour_pen.widthF(),m_focus_pen.widthF());
  SetRoundedRectIncludingPen(
    new_rect.adjusted(-pen_width,-pen_width,pen_width,pen_width),
    radius_x,
    radius_y
  );
  #ifndef NDEBUG
  const double e = 2.0;
  if (std::abs(new_rect.height() - GetRect().height()) >= e)
  {
    TRACE("ERROR");
    TRACE(new_rect.height());
    TRACE(GetRect().height());
    TRACE(m_contour_pen.widthF());
    TRACE(m_focus_pen.widthF());
    TRACE(pen_width);
    TRACE("BREAK");
  }
  #endif
  assert(std::abs(new_rect.left() - GetRect().left()) < e);
  assert(std::abs(new_rect.top() - GetRect().top()) < e);
  assert(std::abs(new_rect.width() - GetRect().width()) < e);
  assert(std::abs(new_rect.height() - GetRect().height()) < e);
  assert(radius_x == GetRadiusX());
  assert(radius_y == GetRadiusY());
}

void ribi::QtRoundedRectItem::SetRoundedRectIncludingPen(
  const QRectF new_rect,
  const double radius_x,
  const double radius_y
) noexcept
{
  if (GetRectIncludingPen() != new_rect)
  {
    QGraphicsRectItem::setRect(new_rect);
    this->update();
    m_signal_pos_changed(this);
    m_signal_rect_changed(this);
  }
  this->SetRadiusX(radius_x);
  this->SetRadiusY(radius_y);


  #ifndef NDEBUG
  const auto current = GetRectIncludingPen();
  const double e = 2.0;
  if (
       (std::abs(new_rect.width() - current.width()) >= e)
    || (std::abs(new_rect.height() - current.height()) >= e)
    || (std::abs(new_rect.top() - current.top()) >= e)
    || (std::abs(new_rect.left() - current.left()) >= e)
  )
  {
    TRACE("ERROR");
    TRACE(new_rect.left());
    TRACE(current.left());
    TRACE(new_rect.top());
    TRACE(current.top());
    TRACE(new_rect.width());
    TRACE(current.width());
    TRACE(new_rect.height());
    TRACE(current.height());
    TRACE("BREAK");
  }
  #endif

  assert(std::abs(new_rect.width() - current.width()) < e);
  assert(std::abs(new_rect.height() - current.height()) < e);
  assert(std::abs(new_rect.top() - current.top()) < e);
  assert(std::abs(new_rect.left() - current.left()) < e);

  //assert(new_rect == GetRectIncludingPen());
  assert(radius_x == GetRadiusX());
  assert(radius_y == GetRadiusY());
}


void ribi::QtRoundedRectItem::SetWidth(const double width) noexcept
{
  SetWidthIncludingPen(
    width + (2.0 * std::max(m_contour_pen.widthF(),m_focus_pen.widthF()))
  );
  assert(std::abs(width - GetWidth()) < 2.0);
}

void ribi::QtRoundedRectItem::SetWidthIncludingPen(const double width) noexcept
{
  const auto current = this->GetRectIncludingPen();
  const double current_width = current.width();
  if (current_width != width)
  {
    SetRoundedRectIncludingPen(
      QRectF(
        current.left(),
        current.top(),
        width,
        current.height()
      ),
      this->GetRadiusX(),
      this->GetRadiusY()
    );
    //Signals and update at SetRoundedRectIncludingPen
    //m_signal_rect_changed(this);
    //this->update();
  }
  #ifndef NDEBUG
  const double e = 2.0;
  if(std::abs(width - GetWidthIncludingPen()) >= e)
  {
    TRACE("ERROR");
    TRACE(width);
    TRACE(GetWidthIncludingPen());
    TRACE("BREAK");
  }
  #endif
  assert(std::abs(width - GetWidthIncludingPen()) < e);
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
  QtRoundedRectItem i;
  i.SetPos(345.67,456.78);
  i.SetHeightIncludingPen(123.45);
  i.SetWidthIncludingPen(234.56);
  i.SetHeight(123.45);
  i.SetWidth(234.56);
}
#endif

bool ribi::operator==(const QtRoundedRectItem& lhs, const QtRoundedRectItem& rhs) noexcept
{
  return
       lhs.GetContourPen() == rhs.GetContourPen()
    && lhs.GetFocusPen() == lhs.GetFocusPen()
    && lhs.GetRadiusX() == lhs.GetRadiusX()
    && lhs.GetRadiusY() == lhs.GetRadiusY()
    && lhs.GetRect() == lhs.GetRect()
  ;
}

bool ribi::operator!=(const QtRoundedRectItem& lhs, const QtRoundedRectItem& rhs) noexcept
{
  return !(lhs == rhs);
}
