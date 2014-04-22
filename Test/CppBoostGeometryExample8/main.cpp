#include <cassert>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#pragma GCC diagnostic pop

int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::polygon<Point> Polygon;

  //Obtain the points
  const std::vector<Point> points {
      {15.9835,631.923},
      {8.24075,628.579},
      {8.24075,679.58 },
      {15.9835,682.926}
  };

  //Create a polygon from these points
  Polygon polygon;
  boost::geometry::append(polygon, points);
  assert(boost::geometry::num_points(polygon) == 4);

  //Create the points back again from that polygon
  const std::vector<Point> points_again = polygon.outer();

  //Initial and re-created points must be equal
  assert(
    std::equal(points.begin(),points.end(),points_again.begin(),
      [](const boost::geometry::model::d2::point_xy<double>& a, const boost::geometry::model::d2::point_xy<double>& b)
      {
        return boost::geometry::equals(a,b);
      }
    )
  );
}
