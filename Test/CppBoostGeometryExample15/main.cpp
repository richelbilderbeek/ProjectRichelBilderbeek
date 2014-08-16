#include <cassert>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
//#include <boost/geometry/algorithms/correct.hpp>
//#include <boost/geometry/algorithms/equals.hpp>
//#include <boost/geometry/algorithms/intersection.hpp>
//#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
//#include <boost/geometry/geometries/polygon.hpp>
//#include <boost/geometry/io/wkt/read.hpp>
//#include <boost/geometry/io/wkt/write.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#pragma GCC diagnostic pop
/*

+   *---*        +               +
|   |   |        |               |
+   |   |        + *---*         +   +-*
|   | A |        | | B |         |     |
+   |   |    +   + *---*     =   +   +-*
|   |   |        |               |
+   +---+        +               +
|                |               |
+-+-+-+-+-+      +-+-+-+-+-+     +-+-+-+-+-+

*/
int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::linestring<Coordinat2D> Linestring;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;
  typedef std::vector<Linestring> Linestrings;

  //Create polygon A
  Polygon a;
  boost::geometry::read_wkt(
    "POLYGON((4.0 4.0,4.0 1.0,2.0 1.0,2.0 4.0))",
    a
  );
  boost::geometry::correct(a);

  //Create linestring B
  Linestring b;
  boost::geometry::read_wkt(
    "LINESTRING(1.0 3.0,3.0 3.0,3.0 2.0,1.0 2.0)",
    b
  );
  boost::geometry::correct(b);

  //Create intersection
  Linestrings intersections;
  boost::geometry::intersection(a,b,intersections);
  assert(intersections.size() == 1);

  //Extract the only intersection
  const auto found = intersections[0];

  Linestring expected;
  boost::geometry::read_wkt(
    "LINESTRING(2.0 3.0,3.0 3.0,3.0 2.0,2.0 2.0)",
    expected
  );

  std::cout
    << "Found:" << '\n'
    << "As WKT: " << boost::geometry::wkt<decltype(found)>(found) << '\n'
    << "#points: " << found.size() << '\n'
  ;

  for (const auto point: found)
  {
    std::cout << '(' << boost::geometry::get<0>(point)
      << ',' << boost::geometry::get<1>(point) << ')'
      << '\n'
    ;
  }

  std::cout
    << "Expected:" << '\n'
    << "As WKT: " << boost::geometry::wkt<decltype(expected)>(expected) << '\n'
    << "#points: " << expected.size() << '\n';
  for (const auto point: expected)
  {
    std::cout << '(' << boost::geometry::get<0>(point)
      << ',' << boost::geometry::get<1>(point) << ')'
      << '\n'
    ;
  }

  assert(found.size() == expected.size());
  assert(boost::geometry::equals(found,expected));
}

/* Screen output:

Found:
As WKT: LINESTRING(2 3,3 3,3 2,2 2)
#points: 4
(2,3)
(3,3)
(3,2)
(2,2)
Expected:
As WKT: LINESTRING(2 3,3 3,3 2,2 2)
#points: 4
(2,3)
(3,3)
(3,2)
(2,2)
Press <RETURN> to close this window...

*/
