#include <cassert>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/io/wkt/read.hpp>
#include <boost/geometry/io/wkt/write.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#pragma GCC diagnostic pop
/*

   +   *---*
   |   |   |
   + *-+-* |
   | | | | |
   + | *-+-*
   | |   |
   + *---*
   |
   +-+-+-+-+-+

*/


int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;
  typedef std::vector<Polygon> Polygons;

  Polygon polygon_a;
  boost::geometry::read_wkt(
    "POLYGON((1.0 1.0 , 1.0 3.0 , 3.0 3.0 , 3.0 1.0))",
    polygon_a
  );
  boost::geometry::correct(polygon_a);

  Polygon polygon_b;
  boost::geometry::read_wkt(
    "POLYGON((2.0 2.0 , 2.0 4.0 , 4.0 4.0 , 4.0 2.0))",
    polygon_b
  );
  boost::geometry::correct(polygon_b);

  Polygons polygons;
  boost::geometry::intersection(polygon_a,polygon_b,polygons);

  assert(polygons.size() == 1);
  const auto polygon_found = polygons[0];

  Polygon polygon_expected;
  boost::geometry::read_wkt(
    "POLYGON((2.0 2.0, 2.0 3.0, 3.0 3.0, 3.0 2.0))",
    polygon_expected
  );
  boost::geometry::correct(polygon_expected);

  std::cout
    << "Found:" << '\n'
    << "As WKT: " << boost::geometry::wkt<Polygon>(polygon_found) << '\n'
    << "#points: " << polygon_found.outer().size() << '\n';

  for (auto point: polygon_found.outer())
  {
    std::cout << '(' << boost::geometry::get<0>(point)
      << ',' << boost::geometry::get<1>(point) << ')'
      << '\n'
    ;
  }

  std::cout
    << "Expected:" << '\n'
    << "As WKT: " << boost::geometry::wkt<Polygon>(polygon_expected) << '\n'
    << "#points: " << polygon_expected.outer().size() << '\n';
  for (auto point: polygon_expected.outer())
  {
    std::cout << '(' << boost::geometry::get<0>(point)
      << ',' << boost::geometry::get<1>(point) << ')'
      << '\n'
    ;
  }

  assert(polygon_found.outer().size() == polygon_expected.outer().size());
  assert(boost::geometry::equals(polygon_found,polygon_expected));
}

/* Screen output:

Found:
As WKT: POLYGON((2 3,3 3,3 2,2 2,2 3))
#points: 5
(2,3)
(3,3)
(3,2)
(2,2)
(2,3)
Expected:
As WKT: POLYGON((2 2,2 3,3 3,3 2,2 2))
#points: 5
(2,2)
(2,3)
(3,3)
(3,2)
(2,2)
Press <RETURN> to close this window...

*/
