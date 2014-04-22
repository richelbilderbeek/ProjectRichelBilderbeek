#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#pragma GCC diagnostic pop

bool IsConvex(boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon)
{
  boost::geometry::correct(polygon);
  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> hull;
  boost::geometry::convex_hull(polygon, hull);
  return boost::geometry::area(hull) == boost::geometry::area(polygon);
}

int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  /* Polygons used:

  0123456789012    0123456789012
 0+------------   0+------------
 1|               1|
 2| A---------B   2| A---------B
 3| E        /    3|  \   D   /
 4|  \      /     4|   \ / \ /
 5|   D----C      5|    E   C
  |                |

     Convex           Concave

  */

  //Convex shape
  {
    const std::vector<Coordinat2D> points {
      { 2.0, 2.0}, //A
      {12.0, 2.0}, //B
      { 9.0, 5.0}, //C
      { 4.0, 5.0}, //D
      { 2.0, 3.0}  //E
    };

    boost::geometry::model::polygon<Coordinat2D> polygon;
    boost::geometry::append(polygon, points);
    assert(IsConvex(polygon));
  }
  //Concave shape
  {
    const std::vector<Coordinat2D> points {
      { 2.0, 2.0}, //A
      {12.0, 2.0}, //B
      { 9.0, 5.0}, //C
      { 7.0, 3.0}, //D
      { 5.0, 5.0}  //E
    };

    boost::geometry::model::polygon<Coordinat2D> polygon;
    boost::geometry::append(polygon, points);
    assert(!IsConvex(polygon));
  }
}
