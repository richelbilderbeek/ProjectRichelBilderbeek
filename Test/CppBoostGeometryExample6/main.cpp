#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#pragma GCC diagnostic pop

int main()
{
  using namespace boost::geometry;


  /* Polygon used:

    3-
     |
    2-    4 #
     |   / \
    1-  2   3
     |  | * |
    0-  0---1
     |
     +--|---|---|
        0   1   2

  *: point that is tested to be within the polygon
  #: point that is tested to be outside of the polygon

  */

  const std::vector<model::d2::point_xy<double>> points {
    {0.0, 0.0}, {1.0, 0.0}, {0.0, 2.0}, {1.0, 2.0}, {0.5, 2.0}
  };

  model::polygon<model::d2::point_xy<double> > house;
  append(house, points);

  assert( within(model::d2::point_xy<double>(0.5, 0.5), house));
  assert(!within(model::d2::point_xy<double>(1.0, 2.0), house));
}
