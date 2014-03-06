#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <tuple>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/point.hpp>
#pragma GCC diagnostic pop

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>
  operator-(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& a,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& b
  )
{
  return boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>(
    boost::geometry::get<0>(a) - boost::geometry::get<0>(b),
    boost::geometry::get<1>(a) - boost::geometry::get<1>(b),
    boost::geometry::get<2>(a) - boost::geometry::get<2>(b)
  );
}

///Determine the plane that goes through these three points
std::tuple<double,double,double,double> CalcPlane(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
)
{
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> v1 { p3 - p1 };
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> v2 { p2 - p1 };
}

int main()
{
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> a( 1.0, 2.0,3.0);
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> b( 4.0, 6.0,9.0);
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> c(12.0,11.0,9.0);
  const std::tuple<double,double,double,double> t { CalcPlane(a,b,c) };
  std::cout
    << std::get<0>(t) << '\n'
    << std::get<1>(t) << '\n'
    << std::get<2>(t) << '\n'
    << std::get<3>(t) << '\n'
  ;
}
