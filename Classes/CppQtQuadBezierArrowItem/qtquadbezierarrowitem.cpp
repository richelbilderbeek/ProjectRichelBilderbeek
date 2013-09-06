//---------------------------------------------------------------------------
/*
QtQuadBezierArrowItem, an quadratic Bezier arrow QGraphicsItem
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
//From http://www.richelbilderbeek.nl/CppQtQuadBezierArrowItem.htm
//---------------------------------------------------------------------------


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtquadbezierarrowitem.h"

#include <cassert>
#include <cmath>

#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry.hpp>
#include <boost/math/constants/constants.hpp>
#pragma GCC diagnostic pop

#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>

#include "trace.h"

template <class T>
bool operator==(
  const boost::geometry::model::d2::point_xy<T>& a,
  const boost::geometry::model::d2::point_xy<T>& b)
{
  return a.x() == b.x() && a.y() == b.y();
}

template <class T>
bool operator!=(
  const boost::geometry::model::d2::point_xy<T>& a,
  const boost::geometry::model::d2::point_xy<T>& b)
{
  return !(a == b);
}

template <class T>
bool operator==(
  const boost::geometry::model::linestring<boost::geometry::model::d2::point_xy<T> > a,
  const boost::geometry::model::linestring<boost::geometry::model::d2::point_xy<T> > b)
{
  return (a[0] == b[0] && a[1] == b[1])
    ||   (a[0] == b[1] && a[1] == b[0]);
}

template <class T>
bool operator!=(
  const boost::geometry::model::linestring<boost::geometry::model::d2::point_xy<T> > a,
  const boost::geometry::model::linestring<boost::geometry::model::d2::point_xy<T> > b)
{
  return !(a==b);
}

///Obtain the zero or one intersections between two finite lines
//From http://www.richelbilderbeek.nl/CppGetLineLineIntersections.htm
template <class T>
const std::vector<
  boost::geometry::model::d2::point_xy<T>
>
GetLineLineIntersections(
  const boost::geometry::model::linestring<
    boost::geometry::model::d2::point_xy<T>
  > line1,
  const boost::geometry::model::linestring<
    boost::geometry::model::d2::point_xy<T>
  > line2)
{
  typedef boost::geometry::model::d2::point_xy<T> Point;
  //typedef boost::geometry::model::linestring<Point> Line;
  std::vector<Point> points;
  boost::geometry::intersection(line1,line2,points);
  assert(points.empty() || points.size() == 1);
  return points;
}

//Helper function to create a const line without a temporary std::vector
template <class T>
const boost::geometry::model::linestring<boost::geometry::model::d2::point_xy<T>
>
CreateLine(const std::vector<boost::geometry::model::d2::point_xy<T> >& v)
{
  return boost::geometry::model::linestring<
    boost::geometry::model::d2::point_xy<T>
  >(v.begin(),v.end());
}

///Obtain the Pythagorian distance from two delta's
//From www.richelbilderbeek.nl/CppGetDistance.htm
double GetDistance(const double delta_x, const double delta_y)
{
  return std::sqrt( (delta_x * delta_x) + (delta_y * delta_y) );
}

///Obtain the Pythagorian distance from two coordinats
//From www.richelbilderbeek.nl/CppGetDistance.htm
double GetDistance(const double x1, const double y1, const double x2, const double y2)
{
  return GetDistance(x1-x2,y1-y2);
}

///Obtain the zero, one or two intersections between a line and a rectanle
//From http://www.richelbilderbeek.nl/CppGetLineRectIntersections.htm
template <class T>
const std::vector<
  boost::geometry::model::d2::point_xy<T>
>
GetLineRectIntersections(
  const boost::geometry::model::linestring<
    boost::geometry::model::d2::point_xy<T>
  > line,
  const boost::geometry::model::box<
    boost::geometry::model::d2::point_xy<T>
  > rect)
{
  typedef boost::geometry::model::d2::point_xy<T> Point;
  typedef boost::geometry::model::linestring<Point> Line;
  //typedef boost::geometry::model::box<Point> Rect;

  const Point p0 = Point(rect.min_corner().x(), rect.min_corner().y());
  const Point p1 = Point(rect.max_corner().x(), rect.min_corner().y());
  const Point p2 = Point(rect.min_corner().x(), rect.max_corner().y());
  const Point p3 = Point(rect.max_corner().x(), rect.max_corner().y());
  assert(p0 != p1); assert(p0 != p2); assert(p0 != p3);
  assert(p1 != p0); assert(p1 != p2); assert(p1 != p3);
  assert(p2 != p0); assert(p2 != p1); assert(p2 != p3);
  assert(p3 != p0); assert(p3 != p1); assert(p3 != p2);

  const std::vector<Line> rect_sides
    =
    {
      CreateLine(std::vector<Point>( {p0,p1} )),
      CreateLine(std::vector<Point>( {p0,p2} )),
      CreateLine(std::vector<Point>( {p1,p3} )),
      CreateLine(std::vector<Point>( {p2,p3} ))
    };
  std::vector<Point> points;
  std::for_each(rect_sides.begin(),rect_sides.end(),
    [&points,line](const Line& side)
    {
      const std::vector<Point> v = GetLineLineIntersections(line,side);
      std::copy(v.begin(),v.end(),std::back_inserter(points));
    }
  );
  //Remove doublures
  //Put 'typename' before 'std::vector<Point>::iteratortype' to prevent getting the error below:
  //error: need 'typename' before 'std::vector<boost::geometry::model::d2::point_xy<T> >::iterator'
  //  because 'std::vector<boost::geometry::model::d2::point_xy<T> >' is a dependent scope
  typename std::vector<Point>::iterator new_end = std::unique( points.begin(),points.end(),
    [](const Point& lhs, const Point& rhs)
    {
      return lhs.x() == rhs.x() && lhs.y() == rhs.y();
    }
  );
  points.erase(new_end,points.end());

  assert(points.size() <= 2);

  return points;
}

const double QtQuadBezierArrowItem::m_click_easy_width = 10.0;

QtQuadBezierArrowItem::QtQuadBezierArrowItem(
  const QGraphicsItem* const from,
  const bool tail,
  const QGraphicsItem* const mid,
  const bool head,
  const QGraphicsItem* const to,
  QGraphicsItem* parent)
  : QGraphicsItem(parent),       //New since Qt5
    m_focus_pen(QPen(Qt::DashLine)),
    m_from(from),
    m_head(head),
    m_mid(mid),
    m_pen(QPen(QColor(0,0,0))),
    m_tail(tail),
    m_to(to)
{
  assert(from); assert(to); assert(mid);
  assert(from != to); assert(from != mid); assert(mid != to);
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsSelectable);

  assert(!(flags() & QGraphicsItem::ItemIsMovable) );
  assert( (flags() & QGraphicsItem::ItemIsSelectable) );

  //Accept enterHoverEvents
  this->setAcceptHoverEvents(true);

  //Put this arrow item under the rect
  this->setZValue(mid->zValue() - 1.0);
}

QRectF QtQuadBezierArrowItem::boundingRect() const
{
  return shape().boundingRect();
}

double QtQuadBezierArrowItem::GetAngle(const double dx, const double dy)
{
  const double pi = boost::math::constants::pi<double>();
  return pi - (std::atan(dx/dy));
}

const QPointF QtQuadBezierArrowItem::GetBeyond() const
{
  const QPointF center = GetCenter();
  const double dx_mid_center = m_mid->pos().x() - center.x();
  const double dy_mid_center = m_mid->pos().y() - center.y();
  const QPointF beyond(center.x() + dx_mid_center + dx_mid_center, center.y() + dy_mid_center + dy_mid_center);
  return beyond;
}

const QPointF QtQuadBezierArrowItem::GetCenter() const
{
  const QPointF center((m_from->pos() + m_to->pos()) / 2.0);
  return center;
}

const QPointF QtQuadBezierArrowItem::GetHead() const
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::linestring<Point> Line;
  typedef boost::geometry::model::box<Point> Rect;

  const QPointF beyond = GetBeyond();

  const Line line_head = CreateLine(
    std::vector<Point>(
      {
        Point(beyond.x(),beyond.y()),
        Point(m_to->pos().x(),m_to->pos().y()),
      }
    )
  );

  const QRectF qr_to = m_to->boundingRect().translated(m_to->pos());

  const Rect r_to(
    Point(qr_to.topLeft().x()    ,qr_to.topLeft().y()    ),
    Point(qr_to.bottomRight().x(),qr_to.bottomRight().y())
    );


  std::vector<Point> p_head_end = GetLineRectIntersections(line_head,r_to);
  if (p_head_end.size() == 1)
  {
    return QPointF(p_head_end[0].x(),p_head_end[0].y());
  }
  if (p_head_end.empty())
  {
    p_head_end.push_back(Point(m_to->pos().x(),m_to->pos().y()));
    //Yes,it happens, when the line does not leave the rectangle
    //this happens when the two node rectanges overlap
    assert(!p_head_end.empty());
    assert(p_head_end.size() == 1); ///BUG?
    return QPointF(p_head_end[0].x(),p_head_end[0].y());
  }
  else
  {
    assert(p_head_end.size() == 2);
    //Choose point closest to beyond
    const double d1 = GetDistance(beyond.x(),beyond.y(),p_head_end[0].x(),p_head_end[0].x());
    const double d2 = GetDistance(beyond.x(),beyond.y(),p_head_end[1].x(),p_head_end[1].x());
    if (d1 <= d2)
    {
      return QPointF(p_head_end[0].x(),p_head_end[0].y());
    }
    else
    {
      return QPointF(p_head_end[1].x(),p_head_end[1].y());
    }
  }
}

const QPointF QtQuadBezierArrowItem::GetTail() const
{

  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::linestring<Point> Line;
  typedef boost::geometry::model::box<Point> Rect;

  const QPointF beyond = GetBeyond();

  const Line line_tail = CreateLine(
    std::vector<Point>(
      {
        Point(m_from->pos().x(),m_from->pos().y()),
        Point(beyond.x(),beyond.y()),
      }
    )
  );

  const QRectF qr_from = m_from->boundingRect().translated(m_from->pos());

  const Rect r_from(
    Point(qr_from.topLeft().x()    ,qr_from.topLeft().y()    ),
    Point(qr_from.bottomRight().x(),qr_from.bottomRight().y())
    );

  std::vector<Point> p_tail_end = GetLineRectIntersections(line_tail,r_from);
  if (p_tail_end.size() == 1)
  {
    return QPointF(p_tail_end[0].x(),p_tail_end[0].y());
  }
  if (p_tail_end.empty())
  {
    //Yes,it happens, when the line does not leave the rectangle
    //this happens when the two node rectanges overlap
    p_tail_end.push_back(Point(m_from->pos().x(),m_from->pos().y()));
    assert(!p_tail_end.empty());
    assert(p_tail_end.size() == 1);
    return QPointF(p_tail_end[0].x(),p_tail_end[0].y());
  }
  else
  {
    assert(p_tail_end.size() == 2);
    //Choose point closest to beyond
    const double d1 = GetDistance(beyond.x(),beyond.y(),p_tail_end[0].x(),p_tail_end[0].x());
    const double d2 = GetDistance(beyond.x(),beyond.y(),p_tail_end[1].x(),p_tail_end[1].x());
    if (d1 <= d2)
    {
      return QPointF(p_tail_end[0].x(),p_tail_end[0].y());
    }
    else
    {
      return QPointF(p_tail_end[1].x(),p_tail_end[1].y());
    }
  }
}

const std::string QtQuadBezierArrowItem::GetVersion()
{
  return "1.4";
}

const std::vector<std::string> QtQuadBezierArrowItem::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-07: version 1.0: initial version");
  v.push_back("2012-12-13: version 1.1: respond to focus");
  v.push_back("2012-12-29: version 1.2: fixed bug in GetHead and GetTail that occurs when GetLineRectIntersections returns two points");
  v.push_back("2013-01-01: version 1.3: added QGraphicsItem getters");
  v.push_back("2013-07-10: version 1.4: setting arrow heads emits a notification signal");
  return v;
}

void QtQuadBezierArrowItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}

void QtQuadBezierArrowItem::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_F1:
    case Qt::Key_1:
    case Qt::Key_T:
    case Qt::Key_Minus:
      m_tail = !m_tail;
      this->update();
      m_signal_item_updated(this);
      return;
    case Qt::Key_F2:
    case Qt::Key_2:
    case Qt::Key_H:
    case Qt::Key_Plus:
      m_head = !m_head;
      this->update();
      m_signal_item_updated(this);
      return;
    default:
      break;
  }
  QGraphicsItem::keyPressEvent(event);
}

void QtQuadBezierArrowItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->modifiers() & Qt::ShiftModifier)
  {
    if ((event->pos() - this->m_from->pos()).manhattanLength() < 10.0)
    {
      m_tail = !m_tail;
      this->update();
      m_signal_item_updated(this);
    }
    else if ((event->pos() - this->m_to->pos()).manhattanLength() < 10.0)
    {
      m_head = !m_head;
      this->update();
      m_signal_item_updated(this);
    }
  }
  QGraphicsItem::mousePressEvent(event);
}


void QtQuadBezierArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->setRenderHint(QPainter::Antialiasing);
  painter->drawEllipse(this->GetMidItem()->pos(),1,1);

  if (this->isSelected() || this->hasFocus())
  {
    painter->setPen(m_focus_pen);
  }
  else
  {
    painter->setPen(m_pen);
  }
  //Line must go _though_ mid pos, instead of using it as a virtual hinge point
  //Solution:
  // - define point 'center' as the middle between from and to
  // - define point 'beyond' as the mirror point of 'center', using mid_pos as a mirror
  const QPointF beyond = GetBeyond();
  const QPointF p_tail_end = GetTail();
  const QPointF p_head_end = GetHead();

  QPainterPath curve;
  curve.moveTo(p_tail_end);
  curve.quadTo(beyond,p_head_end);
  painter->drawPath(curve);

  {
    const double sz = 10.0; //pixels
    if (m_tail)
    {
      //The angle from midpoint to tail
      //Thanks goes out to Toine van den Bogaart and Theo van den Bogaart for being happy to help with the math
      const double pi = boost::math::constants::pi<double>();
      const double dx = beyond.x() - m_from->pos().x();
      const double dy = beyond.y() - m_from->pos().y();
      double angle = GetAngle(dx,dy);
      if (dy >= 0.0) angle = (1.0 * pi) + angle;
      const QPointF p0(p_tail_end.x(),p_tail_end.y());
      const QPointF p1
        = p0 + QPointF(
           std::sin(angle + pi + (pi * 0.1)) * sz,
          -std::cos(angle + pi + (pi * 0.1)) * sz);
      const QPointF p2
        = p0 + QPointF(
           std::sin(angle + pi - (pi * 0.1)) * sz,
          -std::cos(angle + pi - (pi * 0.1)) * sz);
      painter->drawPolygon(QPolygonF() << p0 << p1 << p2);
    }
    if (m_head)
    {
      //The angle from midpoint to head
      //Thanks goes out to Toine van den Bogaart and Theo van den Bogaart for being happy to help with the math
      const double pi = boost::math::constants::pi<double>();
      const double dx = m_to->pos().x() - beyond.x();
      const double dy = m_to->pos().y() - beyond.y();
      double angle = GetAngle(dx,dy);
      if (dy >= 0.0) angle = (1.0 * pi) + angle;

      const QPointF p0(p_head_end.x(),p_head_end.y());
      const QPointF p1
        = p0 + QPointF(
           std::sin(angle +  0.0 + (pi * 0.1)) * sz,
          -std::cos(angle +  0.0 + (pi * 0.1)) * sz);
      const QPointF p2
        = p0 + QPointF(
           std::sin(angle +  0.0 - (pi * 0.1)) * sz,
          -std::cos(angle +  0.0 - (pi * 0.1)) * sz);

      painter->drawPolygon(QPolygonF() << p0 << p1 << p2);
    }
  }
}

void QtQuadBezierArrowItem::SetHasHead(const bool has_head)
{

  if (m_head != has_head)
  {
    m_head = has_head;
    this->update();
    m_signal_item_updated(this);
  }
}

void QtQuadBezierArrowItem::SetHasTail(const bool has_tail)
{
  if (m_tail != has_tail)
  {
    m_tail = has_tail;
    this->update();
    m_signal_item_updated(this);
  }
}


QPainterPath QtQuadBezierArrowItem::shape() const
{
  const QPointF beyond = GetBeyond();
  const QPointF p_tail_end = GetTail();
  const QPointF p_head_end = GetHead();

  QPainterPath curve;
  curve.moveTo(p_tail_end);
  curve.quadTo(beyond,p_head_end);

  QPainterPathStroker stroker;
  stroker.setWidth(m_click_easy_width);
  return stroker.createStroke(curve);
}
