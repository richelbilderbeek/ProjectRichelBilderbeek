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
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/io/wkt/read.hpp>
#include <boost/geometry/io/wkt/write.hpp>
#include <boost/geometry/io/wkt/stream.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#pragma GCC diagnostic pop

int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

 const std::string wkt = "POLYGON((0.5 2.0,1.0 1.0,1.0 0.0,0.0 0.0,0.0 1.0))";

 std::cout << wkt << '\n';

  Polygon polygon;
  boost::geometry::read_wkt(wkt,polygon);

  {
    const auto w = boost::geometry::wkt<>(polygon);
    std::cout << w << '\n';
  }

  boost::geometry::correct(polygon);

  {
    const auto w = boost::geometry::wkt<>(polygon);
    std::cout << w << '\n';
  }
}

/* Screen output

POLYGON((0.5 2.0,1.0 1.0,1.0 0.0,0.0 0.0,0.0 1.0))
POLYGON((0.5 2,1 1,1 0,0 0,0 1))
POLYGON((0.5 2,1 1,1 0,0 0,0 1,0.5 2))
Press <RETURN> to close this window...

*/
