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
#pragma GCC diagnostic pop

int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

  Polygon polygon;
  boost::geometry::read_wkt(
    "POLYGON((0.5 2.0 , 1.0 1.0 , 1.0 0.0 , 0.0 0.0 , 0.0 1.0))",
    polygon
  );

  const std::vector<Coordinat2D> points_expected {
    {0.5, 2.0}, //0
    {1.0, 1.0}, //1
    {1.0, 0.0}, //2
    {0.0, 0.0}, //3
    {0.0, 1.0}  //4
  };

  const std::vector<Coordinat2D> points = polygon.outer();

  assert(
    std::equal(
      points.begin(),points.end(),
      points_expected.begin(),
      [](const Coordinat2D& a,const Coordinat2D& b)
      {
        return boost::geometry::equals(a,b);
      }
    )
    && "Points should be as expected"
  );
}
