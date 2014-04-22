#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#pragma GCC diagnostic pop

//Goal: determine if a polygon, derived from points, is convex
//Method: if the convex_hull equals that points, it is convex
//
//Bug: convex_hull does make a convex polygon look concave for certain values
//
//Bug report is posted at https://svn.boost.org/trac/boost/ticket/9873
int main()
{
  using namespace boost::geometry;
  typedef model::d2::point_xy<double> Point;
  typedef model::polygon<Point> Polygon;

  //Example A: works as expected
  {
    /* Polygon used:

      -
      |
      -  2---3
      |  |
      -  1---0
      |
      +--|---|---|

    (point values are those simplified from example B)

    */
    const std::vector<Point> points {
        {15.0,631.0},
        { 8.0,628.0},
        { 8.0,679.0},
        {15.0,682.0}
    };

    Polygon polygon;
    append(polygon, points);

    assert(boost::geometry::num_points(polygon) == 4);

    boost::geometry::correct(polygon);

    assert(boost::geometry::num_points(polygon) == 5
      && "OK: boost::geometry::correct adds a point");

    Polygon hull;
    boost::geometry::convex_hull(polygon, hull);

    assert(boost::geometry::num_points(hull) == 5
      && "OK: the hull of a convex polygon has the same number of points as that polygon");
    assert(boost::geometry::equals(polygon,hull));
  }

  //Example B: does not work as expected
  {
    /* Polygon used:

      -
      |
      -  2---3
      |  |
      -  1---0
      |
      +--|---|---|


    */
    const std::vector<Point> points {
        {15.9835,631.923},
        {8.24075,628.579},
        {8.24075,679.58 },
        {15.9835,682.926}
    };

    Polygon polygon;
    append(polygon, points);
    assert(boost::geometry::num_points(polygon) == 4);

    boost::geometry::correct(polygon);

    assert(boost::geometry::num_points(polygon) == 5
      && "OK: boost::geometry::correct adds a point");

    Polygon hull;
    boost::geometry::convex_hull(polygon, hull);

    assert(boost::geometry::num_points(hull) == 6
      && "Should not add an extra point, as the original polygon was convex");

    assert(!boost::geometry::equals(polygon,hull)
      && "Should be equal, but does not");
  }
}
