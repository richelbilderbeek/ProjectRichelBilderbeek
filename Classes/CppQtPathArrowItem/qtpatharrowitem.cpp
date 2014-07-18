//---------------------------------------------------------------------------
/*
QtPathArrowItem, an arrow QGraphicsItem with one or more midpoints
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
//From http://www.richelbilderbeek.nl/CppQtPathArrowItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtpatharrowitem.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>

#include "geometry.h"
#pragma GCC diagnostic pop

const double ribi::QtPathArrowItem::m_click_easy_width = 10.0;

ribi::QtPathArrowItem::QtPathArrowItem(
  const QPointF& tail_pos,
  const bool tail,
  const std::vector<QPointF>& mid_pos,
  const bool head,
  const QPointF& head_pos,
  QGraphicsItem *parent)
  : QGraphicsItem(parent),       //New since Qt5
    m_signal_item_requests_scene_update{},
    m_focus_pen(QPen(Qt::DashLine)),
    m_head(head),
    m_head_pos(head_pos),
    m_mid_pos(mid_pos),
    m_pen(QPen(QColor(0,0,0))),
    m_tail(tail),
    m_tail_pos(tail_pos)
{
  assert(m_mid_pos.size() >= 1
    && "There must be at least one midpos");
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

  //Allow mouse tracking
  this->setAcceptHoverEvents(true);
}

QRectF ribi::QtPathArrowItem::boundingRect() const
{
  return shape().boundingRect();
}

//double ribi::QtPathArrowItem::GetAngle(const double dx, const double dy)
//{
// return Geometry().GetAngle(dx,dy);
  //const double pi = boost::math::constants::pi<double>();
  //return pi - (std::atan(dx/dy));
//}

std::string ribi::QtPathArrowItem::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtPathArrowItem::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2012-12-01: version 1.0: initial version");
  return v;
}

void ribi::QtPathArrowItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}

void ribi::QtPathArrowItem::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_F1:
    case Qt::Key_1:
    case Qt::Key_T:
    case Qt::Key_Minus:
      m_tail = !m_tail;
      this->update();
      break;
    case Qt::Key_F2:
    case Qt::Key_2:
    case Qt::Key_H:
    case Qt::Key_Plus:
      m_head = !m_head;
      this->update();
      break;
    default:
      break;
  }
  QGraphicsItem::keyPressEvent(event);
  m_signal_item_requests_scene_update(this);

}

void ribi::QtPathArrowItem::mouseMoveEvent(QGraphicsSceneMouseEvent*)
{
  m_signal_item_requests_scene_update(this);
  //QGraphicsLineItem::mouseMoveEvent(event);
}

void ribi::QtPathArrowItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->modifiers() & Qt::ShiftModifier)
  {
    if ((event->pos() - m_tail_pos).manhattanLength() < 10.0)
    {
      m_tail = !m_tail;
      this->update();
    }
    else if ((event->pos() - m_head_pos).manhattanLength() < 10.0)
    {
      m_head = !m_head;
      this->update();
    }
  }
  QGraphicsItem::mousePressEvent(event);
}

void ribi::QtPathArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->setRenderHint(QPainter::Antialiasing);
  if (this->isSelected() || this->hasFocus())
  {
    painter->setPen(m_focus_pen);
  }
  else
  {
    painter->setPen(m_pen);
  }
  {
    //Draw the lines
    painter->drawLine(m_tail_pos,m_mid_pos[0]);
    const std::size_t max = m_mid_pos.size() - 1; //-1, because the line goes to the next index
    for (std::size_t i = 0; i!= max; ++i)
    {
      painter->drawLine(m_mid_pos[i],m_mid_pos[i+1]);
    }
    painter->drawLine(m_mid_pos[ m_mid_pos.size() - 1 ],m_head_pos);
  }


  const double sz = 10.0; //pixels
  if (m_tail)
  {
    const double pi{boost::math::constants::pi<double>()};
    const double dx{m_mid_pos[0].x() - m_tail_pos.x()};
    const double dy{m_mid_pos[0].y() - m_tail_pos.y()};
    double angle{Geometry().GetAngleClockScreen(dx,dy)};
    if (dy >= 0.0) angle = (1.0 * pi) + angle;
    //const QPointF m_tail_pos(m_tail_x,m_tail_y);
    const QPointF p1{
      m_tail_pos + QPointF(
         std::sin(angle + pi + (pi * 0.1)) * sz,
        -std::cos(angle + pi + (pi * 0.1)) * sz)
    };
    const QPointF p2{
      m_tail_pos + QPointF(
         std::sin(angle + pi - (pi * 0.1)) * sz,
        -std::cos(angle + pi - (pi * 0.1)) * sz)
    };
    painter->drawPolygon(QPolygonF() << m_tail_pos << p1 << p2);
  }
  if (m_head)
  {
    const double pi = boost::math::constants::pi<double>();
    const double dx = m_head_pos.x() - m_mid_pos[m_mid_pos.size() - 1].x();
    const double dy = m_head_pos.y() - m_mid_pos[m_mid_pos.size() - 1].y();
    double angle{Geometry().GetAngleClockScreen(dx,dy)};
    if (dy >= 0.0) angle = (1.0 * pi) + angle;
    const QPointF p1
      = m_head_pos + QPointF(
         std::sin(angle +  0.0 + (pi * 0.1)) * sz,
        -std::cos(angle +  0.0 + (pi * 0.1)) * sz);
    const QPointF p2
      = m_head_pos + QPointF(
         std::sin(angle +  0.0 - (pi * 0.1)) * sz,
        -std::cos(angle +  0.0 - (pi * 0.1)) * sz);

    painter->drawPolygon(QPolygonF() << m_head_pos << p1 << p2);
  }
}

void ribi::QtPathArrowItem::SetArrowPath(
  const QPointF& tail_pos,
  const std::vector<QPointF>& mid_pos,
  const QPointF& head_pos)
{
  m_tail_pos = tail_pos;
  m_mid_pos = mid_pos;
  m_head_pos = head_pos;
  assert(m_mid_pos.size() >= 1 && "There must be at least one midpos");
  this->update();
}

QPainterPath ribi::QtPathArrowItem::shape() const
{
  //Thanks to norobro for posting this code at
  //http://www.qtcentre.org/threads/49201-Increase-margin-for-detecting-tooltip-events-of-QGraphicsLineItem
  QPainterPath path;
  QPainterPathStroker stroker;

  path.moveTo(m_tail_pos);
  const std::size_t sz = m_mid_pos.size();
  for (std::size_t i = 0; i!= sz; ++i)
  {
    path.lineTo(m_mid_pos[i]);
  }
  path.lineTo(m_head_pos);

  stroker.setWidth(m_click_easy_width);
  return stroker.createStroke(path);
}

