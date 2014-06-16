//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapnewarrow.h"

#include <string>
#include <boost/lexical_cast.hpp>

#include <QFont>
#include <QPainter>

//#include "qtconceptmapconceptitem.h"
#include "qtconceptmapnode.h"
#include "trace.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#pragma GCC diagnostic pop

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
  const std::vector<Line> lines
    =
    {
      CreateLine(std::vector<Point>( {p0,p1} )),
      CreateLine(std::vector<Point>( {p0,p2} )),
      CreateLine(std::vector<Point>( {p1,p3} )),
      CreateLine(std::vector<Point>( {p2,p3} ))
    };
  std::vector<Point> points;
  std::for_each(lines.begin(),lines.end(),
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

ribi::cmap::QtNewArrow::QtNewArrow(
  QtNode * const from,
  const QPointF& current_to)
  : QtArrowItem(
      from->GetPos().x(),
      from->GetPos().y(),
      false,
      current_to.x(),
      current_to.y(),
      true
    ),
    m_from(from)
{
  assert(m_from);

  //New arrows are above all items
  this->setZValue(2.0);

  //A new arrow must not be moveable
  this->setFlag(QGraphicsItem::ItemIsSelectable,false);
  this->setFlag(QGraphicsItem::ItemIsMovable,false);

  //Reject enterHoverEvents
  this->setAcceptHoverEvents(false);

  assert(!(this->flags() & QGraphicsItem::ItemIsSelectable));
  assert(!(this->flags() & QGraphicsItem::ItemIsMovable ));
}

void ribi::cmap::QtNewArrow::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::linestring<Point> Line;
  typedef boost::geometry::model::box<Point> Rect;
  const Line line = CreateLine(
    std::vector<Point>(
      {
        Point(m_from->GetPos().x(),m_from->GetPos().y()),
        Point(this->line().p2().x(),this->line().p2().y())
      }
    )
  );
  const QRectF qr1 = m_from->boundingRect().translated(m_from->GetPos());

  const Rect r1(
    Point(qr1.topLeft().x()    ,qr1.topLeft().y()    ),
    Point(qr1.bottomRight().x(),qr1.bottomRight().y())
    );

  std::vector<Point> p1 = GetLineRectIntersections(line,r1);
  if (p1.empty())
  {
    //Yes,it happens, when the line does not leave the rectangle
    //this happens when the two node rectanges overlap
    p1.push_back(Point(m_from->GetPos().x(),m_from->GetPos().y()));
  }
  assert(!p1.empty());
  assert(p1.size() == 1);
  const QPointF p2 = this->line().p2();
  this->setLine(QLineF(QPointF(p1[0].x(),p1[0].y()),p2));
  QtArrowItem::paint(painter,option,widget);
}
