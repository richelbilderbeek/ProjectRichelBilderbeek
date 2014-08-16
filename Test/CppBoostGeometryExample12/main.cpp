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

// 5 +
//   |
// 4 +   *---*
//   |   |   |
// 3 + *-+-* |
//   | | | | |
// 2 + | * | *
//   | |   |
// 1 + *   *
//   |
// 0 +-+-+-+-+-+
//   0 1 2 3 4 5

int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::linestring<Point> Linestring;
  typedef std::vector<Point> Points;

  Linestring linestring_a;
  boost::geometry::read_wkt(
    "LINESTRING(1.0 1.0, 1.0 3.0, 3.0 3.0, 3.0 1.0)",
    linestring_a
  );

  Linestring linestring_b;
  boost::geometry::read_wkt(
    "LINESTRING(2.0 2.0, 2.0 4.0, 4.0 4.0, 4.0 2.0)",
    linestring_b
  );

  assert(boost::geometry::intersects(linestring_a,linestring_b));
  Points results_found;
  boost::geometry::intersection(linestring_a,linestring_b,results_found);

  assert(results_found.size() == 1);

  std::cout
    << "Found:" << '\n'
    << "#points: " << results_found.size() << '\n'
  ;
  for (const auto result: results_found)
  {
    std::cout << boost::geometry::wkt<Point>(result) << '\n';
  }
}

/* Screen output:

Found:
#points: 1
POINT(2 3)
Press <RETURN> to close this window...

*/
