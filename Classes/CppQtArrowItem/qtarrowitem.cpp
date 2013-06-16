//---------------------------------------------------------------------------
/*
QtArrowItem, an arrow QGraphicsItem
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
//From http://www.richelbilderbeek.nl/CppQtArrowItem.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtarrowitem.h"

#include <cassert>
#include <cmath>

#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>

#include "trace.h"

const double QtArrowItem::m_click_easy_width = 10.0;

QtArrowItem::QtArrowItem(
  const double x1,
  const double y1,
  const bool tail,
  const double x2,
  const double y2,
  const bool head,
  QGraphicsItem* parent,
  QGraphicsScene* scene)
  : QGraphicsLineItem(x1,y1,x2,y2,parent),       //New since Qt5
//: QGraphicsLineItem(x1,y1,x2,y2,parent,scene), //Deprecated in Qt5
    m_arrow_head_clicking_distance(20.0),
    m_focus_pen(QPen(Qt::DashLine)),
    m_head(head),
    m_pen(QPen(QColor(0,0,0))),
    m_tail(tail)
{
  assert(!scene);
  //scene->addItem(this);
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

  //Allow mouse tracking
  this->setAcceptHoverEvents(true);

  assert(this->line().p1() == QPointF(x1,y1));
  assert(this->line().p2() == QPointF(x2,y2));
}

QRectF QtArrowItem::boundingRect() const
{
  return shape().boundingRect();
}

double QtArrowItem::GetAngle(const double dx, const double dy)
{
  return M_PI - (std::atan(dx/dy));
}

const std::string QtArrowItem::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> QtArrowItem::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-11-18: version 1.0: initial version");
  v.push_back("2012-11-20: version 1.1: mouse cursor changes its shape when moving over this item");
  v.push_back("2012-12-19: version 1.2: allow changing pens");
  return v;
}

void QtArrowItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}

void QtArrowItem::keyPressEvent(QKeyEvent *event)
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
  QGraphicsLineItem::keyPressEvent(event);
  m_signal_item_requests_scene_update(this);
}

void QtArrowItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  m_signal_item_requests_scene_update(this);
  QGraphicsLineItem::mouseMoveEvent(event);
}

void QtArrowItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->modifiers() & Qt::ShiftModifier)
  {
    if ((event->pos() - this->line().p1()).manhattanLength() < m_arrow_head_clicking_distance)
    {
      m_tail = !m_tail;
      this->update();
    }
    else if ((event->pos() - this->line().p2()).manhattanLength() < m_arrow_head_clicking_distance)
    {
      m_head = !m_head;
      this->update();
    }
  }
}

void QtArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *)
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
  painter->drawLine(this->line());

  //The angle from tail to head
  double angle = GetAngle(line().dx(),line().dy());
  if (line().dy() >= 0.0) angle = (1.0 * M_PI) + angle;
  const double sz = 10.0; //pixels
  if (m_tail)
  {
    const QPointF p0 = this->line().p1();
    const QPointF p1
      = p0 + QPointF(
         std::sin(angle + M_PI + (M_PI * 0.1)) * sz,
        -std::cos(angle + M_PI + (M_PI * 0.1)) * sz);
    const QPointF p2
      = p0 + QPointF(
         std::sin(angle + M_PI - (M_PI * 0.1)) * sz,
        -std::cos(angle + M_PI - (M_PI * 0.1)) * sz);
    painter->drawPolygon(QPolygonF() << p0 << p1 << p2);
  }
  if (m_head)
  {
    const QPointF p0 = this->line().p2();

    const QPointF p1
      = p0 + QPointF(
         std::sin(angle +  0.0 + (M_PI * 0.1)) * sz,
        -std::cos(angle +  0.0 + (M_PI * 0.1)) * sz);
    const QPointF p2
      = p0 + QPointF(
         std::sin(angle +  0.0 - (M_PI * 0.1)) * sz,
        -std::cos(angle +  0.0 - (M_PI * 0.1)) * sz);

    painter->drawPolygon(QPolygonF() << p0 << p1 << p2);
  }
}

void QtArrowItem::SetArrowHeadClickingDistance(const double manhattan_distance)
{
  m_arrow_head_clicking_distance = manhattan_distance;
}

void QtArrowItem::SetHeadPos(const double x, const double y)
{
  if (line().x2() != x || line().y2() != y)
  {
    QLineF line = this->line();
    line.setP2(QPointF(x,y));
    this->setLine(line);
    this->update();
  }
}

void QtArrowItem::SetTailPos(const double x, const double y)
{
  if (line().x1() != x || line().y1() != y)
  {
    QLineF line = this->line();
    line.setP1(QPointF(x,y));
    this->setLine(line);
    this->update();
  }
}

QPainterPath QtArrowItem::shape() const
{
  //Thanks to norobro for posting this code at
  //http://www.qtcentre.org/threads/49201-Increase-margin-for-detecting-tooltip-events-of-QGraphicsLineItem
  QPainterPath path;
  QPainterPathStroker stroker;
  path.moveTo(line().p1());
  path.lineTo(line().p2());
  stroker.setWidth(m_click_easy_width);
  return stroker.createStroke(path);
}
