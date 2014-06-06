#include <cassert>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/io/wkt/read.hpp>
#include <boost/geometry/io/wkt/write.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#pragma GCC diagnostic pop

//Convert a polygon to linestring and back
//FAILS :-(
int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::linestring<Point> Linestring;
  typedef boost::geometry::model::polygon<Point> Polygon;
  typedef std::vector<Point> Points;

  Polygon polygon;
  boost::geometry::read_wkt(
    "POLYGON((1.0 1.0, 1.0 3.0, 3.0 3.0, 3.0 1.0))",
    polygon
  );

  Linestring linestring;
  //FAILS :-(
  boost::geometry::convert(polygon.outer(), linestring);
}

