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
#pragma GCC diagnostic pop

ribi::QtRoundedRectItem::QtRoundedRectItem(QGraphicsItem *parent)
 : QGraphicsRectItem(parent),
   m_signal_contour_pen_changed{},
   m_signal_focus_pen_changed{},
   m_signal_pos_changed{},
   m_signal_radius_x_changed{},
   m_signal_radius_y_changed{},
   m_signal_rect_changed{},
   m_contour_pen(QPen(QColor(0,0,0))),
   m_focus_pen(QPen(QColor(0,0,0),1,Qt::DashLine)),
   m_radius_x(4.0),
   m_radius_y(4.0)
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->SetRoundedRect(QRectF(-16.0,-16.0,32.0,32.0),m_radius_x,m_radius_y);

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
  const int pen_width
    = std::max(m_contour_pen.widthF(),m_focus_pen.widthF())
  ;
  //QGraphicsRectItem::rect() is the entire rect
  return QGraphicsRectItem::rect().adjusted(
     pen_width, pen_width,-pen_width,pen_width);
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

void ribi::QtRoundedRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) noexcept
{
  QGraphicsRectItem::mouseMoveEvent(event);
  this->update();
  m_signal_pos_changed(this);
}

void ribi::QtRoundedRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) noexcept
{
  painter->setBrush(brush());
  //The item can be selected by clicking on it, or can have focus by moving towards it
  if (this->isSelected() || this->hasFocus())
  {
    painter->setPen(m_focus_pen);
    const double width = m_focus_pen.width();
    painter->drawRoundedRect(
      GetRect().adjusted( //Adjust to stay within rect
        (0.5 * width) + 1.0,
        (0.5 * width) + 1.0,
        -width - 1.0,
        -width - 1.0
      ),
      m_radius_x,
      m_radius_y
    );
  }
  else
  {
    painter->setPen(m_contour_pen);
    const double width = m_contour_pen.width();
    painter->drawRoundedRect(

      this->GetRect().adjusted( //Adjust to stay within rect
        (0.5 * width) + 1.0,
        (0.5 * width) + 1.0,
        -width - 1.0,
        -width - 1.0
      ),
      m_radius_x,m_radius_y
    );
  }
}

void ribi::QtRoundedRectItem::SetContourPen(const QPen& pen) noexcept
{
  if (m_contour_pen.widthF() != pen.widthF())
  {
    m_contour_pen = pen;
    this->update();
    m_signal_contour_pen_changed(this);
  }
}

void ribi::QtRoundedRectItem::SetFocusPen(const QPen& pen) noexcept
{
  if (m_focus_pen.widthF() != pen.widthF())
  {
    m_focus_pen = pen;
    this->update();
    m_signal_focus_pen_changed(this);
  }
}

void ribi::QtRoundedRectItem::SetHeight(const double height) noexcept
{
  const double current_height = this->GetRect().height();
  if (current_height != height)
  {
    QGraphicsRectItem::setRect(
      this->GetRect().left(),
      this->GetRect().top(),
      this->GetRect().width(),
      height
    );
    this->update();
    m_signal_rect_changed(this);
  }
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
}

void ribi::QtRoundedRectItem::SetRadiusX(const double radius_x) noexcept
{
  if (m_radius_x != radius_x)
  {
    m_radius_x = radius_x;
    this->update();
    m_signal_radius_x_changed(this);
  }
}

void ribi::QtRoundedRectItem::SetRadiusY(const double radius_y) noexcept
{
  if (m_radius_y != radius_y)
  {
    m_radius_y = radius_y;
    this->update();
    m_signal_radius_y_changed(this);
  }
}


void ribi::QtRoundedRectItem::SetRoundedRect(
  const QRectF new_rect,
  const double radius_x,
  const double radius_y
) noexcept
{
  if (this->GetRect() != new_rect)
  {
    QGraphicsRectItem::setRect(new_rect);
    this->update();
    m_signal_pos_changed(this);
    m_signal_rect_changed(this);
  }
  this->SetRadiusX(radius_x);
  this->SetRadiusY(radius_y);
}

void ribi::QtRoundedRectItem::SetWidth(const double width) noexcept
{
  const double current_width = this->GetRect().width();
  if (current_width != width)
  {
    QGraphicsRectItem::setRect(
      this->GetRect().left(),
      this->GetRect().top(),
      width,
      this->GetRect().height()
    );
    m_signal_rect_changed(this);
    this->update();
  }
}

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
