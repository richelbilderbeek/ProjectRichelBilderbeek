#include <cassert>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#pragma GCC diagnostic pop

int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::linestring<Point> Linestring;

  //Obtain the points
  const std::vector<Point> points {
    {1.2,3.4},
    {2.3,4.5},
    {3.4,5.6},
    {4.5,6.7}
  };

  //Create a linestring from these points
  Linestring linestring;
  boost::geometry::append(linestring, points);
  assert(boost::geometry::num_points(linestring) == 4);

  //Create the points back again from that linestring
  const std::vector<Point> points_again = linestring;

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
