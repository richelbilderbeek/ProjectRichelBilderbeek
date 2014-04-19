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
  typedef boost::geometry::model::d2::point_xy<int> Coordinat2D;
  Coordinat2D p(0,0);

  const Coordinat2D p1(1,1);
  const Coordinat2D p2(4,8);

  boost::geometry::assign_point(p,p1);

  assert(boost::geometry::equals(p,p1));

  boost::geometry::add_point(p,p2);
  boost::geometry::subtract_point(p,p2);

  assert(boost::geometry::equals(p,p1));
}
