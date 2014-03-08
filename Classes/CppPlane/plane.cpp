#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "plane.h"

#include <cassert>

#include "geometry.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::Plane::Plane(
  const std::vector<double>& coefficients
) : m_coefficients(coefficients)
{
  assert(m_coefficients.size() == 4);

  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<double> ribi::Plane::CalcPlane(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
) noexcept
{
  const auto v(Geometry().CalcPlane(p1,p2,p3));
  assert(v.size() == 4);
  return v;
}

std::vector<double> ribi::Plane::CalcPlane(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>&
  #ifndef NDEBUG
  p4
  #endif
) noexcept
{
  const auto v(Geometry().CalcPlane(p1,p2,p3));
  assert(v.size() == 4);
  #ifndef NDEBUG
  {
    Plane p(v);
    const double x { boost::geometry::get<0>(p4) };
    const double y { boost::geometry::get<1>(p4) };
    const double z { boost::geometry::get<2>(p4) };
    const double z_expected { p.CalcZ(x,y) };
    assert(std::abs(z - z_expected) < 0.001);
  }
  #endif
  return v;
}

std::vector<boost::geometry::model::d2::point_xy<double>> ribi::Plane::CalcProjection(
  const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points
)
{
  assert(points.size() >= 3);
  Plane p(points[0],points[1],points[2]);
  const double x_origin { 0.0 };
  const double y_origin { 0.0 };
  const double z_origin { p.CalcZ(x_origin,y_origin) };

  std::vector<boost::geometry::model::d2::point_xy<double>> v;
  for (const auto point: points)
  {
    const auto x(boost::geometry::get<0>(point));
    const auto y(boost::geometry::get<1>(point));
    const auto z(boost::geometry::get<2>(point));
    const double dx {
      std::sqrt(
          ((x - x_origin) * (x - x_origin))
        + ((z - z_origin) * (z - z_origin))
      ) * (x - x_origin)
    };
    const double dy {
      std::sqrt(
          ((y - y_origin) * (y - y_origin))
        + ((z - z_origin) * (z - z_origin))
      ) * (y - y_origin)
    };
    boost::geometry::model::d2::point_xy<double> point_xy(dx,dy);
    v.push_back(point_xy);
  }
  return v;
}

double ribi::Plane::CalcZ(const double x, const double y) const
{
  // z = -A/C.x - B/C.y + D/C = (-A.x - B.y + D) / C
  const double a = m_coefficients[0];
  const double b = m_coefficients[1];
  const double c = m_coefficients[2];
  const double d = m_coefficients[3];
  if (c == 0.0) throw std::logic_error("ribi::Plane::CalcZ: cannot calculate Z of a vertical plane");
  return ((-a*x) - (b*y) + d) / c;
}

std::string ribi::Plane::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::Plane::GetVersionHistory() const noexcept
{
  return {
    "2014-03-07: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::Plane::Test() noexcept
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Plane::Test");
  {
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    typedef point<double,3,cartesian> Point;
    const double p1_x { 1.0 };
    const double p1_y { 2.0 };
    const double p1_z { 3.0 };
    const double p2_x { 4.0 };
    const double p2_y { 6.0 };
    const double p2_z { 9.0 };
    const double p3_x {12.0 };
    const double p3_y {11.0 };
    const double p3_z { 9.0 };
    Plane p(
      Point(p1_x,p1_y,p1_z),
      Point(p2_x,p2_y,p2_z),
      Point(p3_x,p3_y,p3_z)
    );
    const auto t(p.GetCoefficients());
    assert(t.size() == 4);
    const double a { t[0] };
    const double b { t[1] };
    const double c { t[2] };
    const double d { t[3] };
    const double a_expected {  30.0 };
    const double b_expected { -48.0 };
    const double c_expected {  17.0 };
    const double d_expected { -15.0 };
    assert(std::abs(a - a_expected) < 0.001);
    assert(std::abs(b - b_expected) < 0.001);
    assert(std::abs(c - c_expected) < 0.001);
    assert(std::abs(d - d_expected) < 0.001);
    const double d_p1_expected { (a * p1_x) + (b * p1_y) + (c * p1_z) };
    const double d_p2_expected { (a * p2_x) + (b * p2_y) + (c * p2_z) };
    const double d_p3_expected { (a * p3_x) + (b * p3_y) + (c * p3_z) };

    const bool verbose = false;
    if (verbose)
    {
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
      /* Screen output

      (a * x) + (b * y) + (c * z) = d
      (30 * x) + (-48 * y) + (17 * z) = -15
      (30 * 1) + (-48 * 2) + (17 * 3) = -15
      (30) + (-96) + (51) = -15
      (30 * 4) + (-48 * 6) + (17 * 9) = -15
      (120) + (-288) + (153) = -15
      (30 * 12) + (-48 * 11) + (17 * 9) = -15
      (360) + (-528) + (153) = -15

      */
    }
    assert(std::abs(d - d_p1_expected) < 0.001);
    assert(std::abs(d - d_p2_expected) < 0.001);
    assert(std::abs(d - d_p3_expected) < 0.001);
  }
  //CalcPlane
  {
    //CalcPlane return the coefficients in the following form:
    // A.x + B.y + C.z = D
    //Converting this to z being a function of x and y:
    // -C.z = A.x + B.y - D
    // z = -A/C.x - B/C.y + D/C
    //In this test, use the formula:
    //  z = (2.0 * x) + (3.0 * y) + (5.0)
    //Coefficients must then become:
    //  -A/C = 2.0
    //  -B/C = 3.0
    //   D/C = 5.0
    //Coefficients are, when setting C to 1.0:
    //  -A = 2.0 => A = -2.0
    //  -B = 3.0 => B = -3.0
    //   C = 1.0
    //   D = 5.0
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    const point<double,3,cartesian> p1(1.0,1.0,10.0);
    const point<double,3,cartesian> p2(1.0,2.0,13.0);
    const point<double,3,cartesian> p3(2.0,1.0,12.0);
    Plane p(p1,p2,p3);
    const auto t(p.GetCoefficients());
    const double a { t[0] };
    const double b { t[1] };
    const double c { t[2] };
    const double d { t[3] };
    const double a_expected { -2.0 };
    const double b_expected { -3.0 };
    const double c_expected {  1.0 };
    const double d_expected {  5.0 };
    assert(std::abs(a - a_expected) < 0.001);
    assert(std::abs(b - b_expected) < 0.001);
    assert(std::abs(c - c_expected) < 0.001);
    assert(std::abs(d - d_expected) < 0.001);
    const double d_p1_expected { (a * 1.0) + (b * 1.0) + (c * 10.0) };
    const double d_p2_expected { (a * 1.0) + (b * 2.0) + (c * 13.0) };
    const double d_p3_expected { (a * 2.0) + (b * 1.0) + (c * 12.0) };
    assert(std::abs(d - d_p1_expected) < 0.001);
    assert(std::abs(d - d_p2_expected) < 0.001);
    assert(std::abs(d - d_p3_expected) < 0.001);
    TRACE(p.ToFunction());
  }
  //CalcZ
  {
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    const point<double,3,cartesian> p1(1.0,2.0,3.0);
    const point<double,3,cartesian> p2(2.0,5.0,8.0);
    const point<double,3,cartesian> p3(3.0,7.0,11.0);
    Plane p(p1,p2,p3);
    TRACE(p.CalcZ(1.0,2.0));
    TRACE(p.CalcZ(2.0,5.0));
    TRACE(p.CalcZ(3.0,7.0));

    assert( std::abs(p.CalcZ(1.0,2.0)- 3.0) < 0.001);
    assert( std::abs(p.CalcZ(2.0,5.0)- 8.0) < 0.001);
    assert( std::abs(p.CalcZ(3.0,7.0)-11.0) < 0.001);
    TRACE(p.ToFunction());
  }
  //ToFunction, 3 points and 4 points
  {
    std::function<double(double,double)> f {
      [](const double x, const double y)
      {
        return (2.0 * x) + (3.0 * y) + 5.0;
      }
    };
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    const double x1 { 2.0 };
    const double y1 { 3.0 };
    const double x2 { 5.0 };
    const double y2 { 7.0 };
    const double x3 { 11.0 };
    const double y3 { 13.0 };
    const double x4 { 17.0 };
    const double y4 { 29.0 };
    const point<double,3,cartesian> p1(x1,y1,f(x1,y1));
    const point<double,3,cartesian> p2(x2,y2,f(x2,y2));
    const point<double,3,cartesian> p3(x3,y3,f(x3,y3));
    const Plane a(p1,p2,p3);
    assert(a.ToFunction() == "z=(2*x) + (3*y) + 5");
    const point<double,3,cartesian> p4(x4,y4,f(x4,y4));
    const Plane b(p1,p2,p3,p4);
    assert(a.ToFunction() == b.ToFunction());
  }
  //GetProjection
  {
    typedef boost::geometry::model::d2::point_xy<double> Point2D;
    typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Point3D;
    using boost::geometry::get;
    /*

    A: (0,0,1)                  A: (0,0)
    B: (1,0,0)                  B: (SQRT(2),0)
    C: (1,1,0)                  C: (SQRT(2),SQRT(2))

    |    /
    |   /                       |
    A-----C                     |  C
    |\/  /      -> becomes ->   | /|
    |/\ /                       |/ |
    +--B---                     A--B-----

    */
    const std::vector<Point2D> v {
      CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      )
    };
    assert(v.size() == 3);
    assert(std::abs(get<0>(v[0]) -           0.0  ) < 0.001);
    assert(std::abs(get<1>(v[0]) -           0.0  ) < 0.001);
    assert(std::abs(get<0>(v[1]) - std::sqrt(2.0) ) < 0.001);
    assert(std::abs(get<1>(v[1]) -           0.0  ) < 0.001);

    assert(std::abs(get<0>(v[2]) - std::sqrt(2.0) ) < 0.001);
    assert(std::abs(get<1>(v[2]) - std::sqrt(2.0) ) < 0.001);

  }

  TRACE("Finished ribi::Plane::Test successfully");
}
#endif

std::string ribi::Plane::ToFunction() const
{
  const double a = m_coefficients[0];
  const double b = m_coefficients[1];
  const double c = m_coefficients[2];
  const double d = m_coefficients[3];
  if (c == 0.0) throw std::logic_error("ribi::Plane::CalcZ: cannot calculate Z of a vertical plane");
  // z = -A/C.x - B/C.y + D/C
  std::stringstream s;
  s
    << "z=(" << (-a/c) << "*x" << ")"
    << " + (" << (-b/c) << "*y" << ")"
    << " + " << (d/c) << "";
  return s.str();
}

