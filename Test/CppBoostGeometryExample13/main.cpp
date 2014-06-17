#include <cassert>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/io/wkt/read.hpp>
#pragma GCC diagnostic pop

//Convert a polygon to linestring and back
int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::linestring<Point> Linestring;
  typedef boost::geometry::model::polygon<Point> Polygon;

  //Create polygon
  Polygon polygon;
  boost::geometry::read_wkt(
    "POLYGON((1.0 1.0, 1.0 3.0, 3.0 3.0, 3.0 1.0))",
    polygon
  );

  //Convert polygon to linestring
  Linestring linestring;
  boost::geometry::append(linestring, polygon.outer());

  //Convert linestring to new polygon
  Polygon new_polygon;
  boost::geometry::append(new_polygon, linestring);

  //Check that the resulting polygon equals the original

  //Instead of using this syntax:
  //  assert(polygon == new_polygon);
  //operator== needs to be defined, which is done by a lambda function
  assert(
    std::equal(
      polygon.outer().begin(),polygon.outer().end(),
      new_polygon.outer().begin(),
      [](const Point& a, const Point& b)
      {
        return boost::geometry::equals(a,b);
      }
    )
  );
}
