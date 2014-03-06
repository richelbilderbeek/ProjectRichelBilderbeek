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

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> CalcCrossProduct(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& a,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& b
) noexcept
{
  using boost::geometry::get;
  return boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>(
    (get<1>(a) * get<2>(b)) - (get<2>(a) * get<1>(b)),
    (get<2>(a) * get<0>(b)) - (get<0>(a) * get<2>(b)),
    (get<0>(a) * get<1>(b)) - (get<1>(a) * get<0>(b))
  );
}


///Determine the plane that goes through these three points
std::tuple<double,double,double,double> CalcPlane(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
)
{
  using boost::geometry::cs::cartesian;
  using boost::geometry::get;
  using boost::geometry::model::point;
  const point<double,3,cartesian> v1 { p3 - p1 };
  const point<double,3,cartesian> v2 { p2 - p1 };

  const point<double,3,cartesian> cross { CalcCrossProduct(v1,v2) };

  const double a { get<0>(cross) };
  const double b { get<1>(cross) };
  const double c { get<2>(cross) };

  const double x { get<0>(p1) };
  const double y { get<1>(p1) };
  const double z { get<2>(p1) };

  const double d { ((a * x) + (b * y) + (c * z)) };
  return std::make_tuple(a,b,c,d);

}

int main()
{
  using boost::geometry::model::point;
  using boost::geometry::cs::cartesian;
  const double p1_x { 1.0 };
  const double p1_y { 2.0 };
  const double p1_z { 3.0 };
  const double p2_x { 4.0 };
  const double p2_y { 6.0 };
  const double p2_z { 9.0 };
  const double p3_x {12.0 };
  const double p3_y {11.0 };
  const double p3_z { 9.0 };
  const point<double,3,cartesian> p1(p1_x,p1_y,p1_z);
  const point<double,3,cartesian> p2(p2_x,p2_y,p2_z);
  const point<double,3,cartesian> p3(p3_x,p3_y,p3_z);
  const std::tuple<double,double,double,double> t { CalcPlane(p1,p2,p3) };
  const double a { std::get<0>(t) };
  const double b { std::get<1>(t) };
  const double c { std::get<2>(t) };
  const double d { std::get<3>(t) };
  const double d_p1_expected { (a * p1_x) + (b * p1_y) + (c * p1_z) };
  const double d_p2_expected { (a * p2_x) + (b * p2_y) + (c * p2_z) };
  const double d_p3_expected { (a * p3_x) + (b * p3_y) + (c * p3_z) };

  std::clog
    << "(a * x) + (b * y) + (c * z) = d" << '\n'
    << "(" << a << " * x) + (" << b << " * y) + (" << c << " * z) = " << d << '\n'
    << "(" << a << " * " << p1_x << ") + (" << b << " * " << p1_y << ") + (" << c << " * " << p1_z << ") = " << d << '\n'
    << "(" << (a * p1_x) << ") + (" << (b * p1_y) << ") + (" << (c * p1_z) << ") = " << d << '\n'
    << "(" << a << " * " << p2_x << ") + (" << b << " * " << p2_y << ") + (" << c << " * " << p2_z << ") = " << d << '\n'
    << "(" << (a * p2_x) << ") + (" << (b * p2_y) << ") + (" << (c * p2_z) << ") = " << d << '\n'
    << "(" << a << " * " << p3_x << ") + (" << b << " * " << p3_y << ") + (" << c << " * " << p3_z << ") = " << d << '\n'
    << "(" << (a * p3_x) << ") + (" << (b * p3_y) << ") + (" << (c * p3_z) << ") = " << d << '\n'
  ;

  assert(std::abs(d - d_p1_expected) < 0.001);
  assert(std::abs(d - d_p2_expected) < 0.001);
  assert(std::abs(d - d_p3_expected) < 0.001);

}

/* Screen output

(a * x) + (b * y) + (c * z) = d
(30 * x) + (-48 * y) + (17 * z) = -15
(30 * 1) + (-48 * 2) + (17 * 3) = -15
(30) + (-96) + (51) = -15
(30 * 4) + (-48 * 6) + (17 * 9) = -15
(120) + (-288) + (153) = -15
(30 * 12) + (-48 * 11) + (17 * 9) = -15
(360) + (-528) + (153) = -15
Press <RETURN> to close this window...

*/
