#include "planex.h"

#include "planez.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "plane.h"

#include <cassert>

#include "geometry.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::PlaneX::PlaneX(
  const std::vector<double>& coefficients
) : m_plane_z(Rotate(coefficients))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(GetCoefficients().size() == 4);

}

std::vector<boost::geometry::model::d2::point_xy<double>> ribi::PlaneX::CalcProjection(
  const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points
)
{
  auto v(points);
  for(auto& i: v) { i = Rotate(i); }
  try
  {
    return PlaneZ::CalcProjection(v);
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("PlaneX::CalcProjection: cannot calculate projection");
  }
}

double ribi::PlaneX::CalcX(const double y, const double z) const
{
  try
  {
    return m_plane_z.CalcZ(y,z);
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("ribi::PlaneX::CalcX: cannot calculate X of a horizontal plane");
  }
}

ribi::PlaneZ ribi::PlaneX::Create(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
) noexcept
{
  return PlaneZ(Rotate(p1), Rotate(p2), Rotate(p3));
}

ribi::PlaneZ ribi::PlaneX::Create(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p4
) noexcept
{
  return PlaneZ(Rotate(p1), Rotate(p2), Rotate(p3), Rotate(p4));
}

const std::vector<double> ribi::PlaneX::GetCoefficients() const noexcept
{
  const auto v(m_plane_z.GetCoefficients());
  assert(v.size() == 4);
  return { v[2],v[0],v[1],v[3] };
}

std::string ribi::PlaneX::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::PlaneX::GetVersionHistory() const noexcept
{
  return {
    "2014-03-10: version 1.0: initial version, split off from PlaneZ"
  };
}

std::vector<double> ribi::PlaneX::Rotate(const std::vector<double>& coefficients) noexcept
{
  assert(coefficients.size() == 4);
  return
  {
    coefficients[2],
    coefficients[0],
    coefficients[1],
    coefficients[3]
  };
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::PlaneX::Rotate(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& point
) noexcept
{
  return {
    boost::geometry::get<1>(point),
    boost::geometry::get<2>(point),
    boost::geometry::get<0>(point)
  };
}

#ifndef NDEBUG
void ribi::PlaneX::Test() noexcept
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PlaneX::Test");
  /*
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
    PlaneX p(
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
    }
    assert(std::abs(d - d_p1_expected) < 0.001);
    assert(std::abs(d - d_p2_expected) < 0.001);
    assert(std::abs(d - d_p3_expected) < 0.001);
  }
  */
  //CalcPlaneX
  /*
  {
    //CalcPlaneX return the coefficients in the following form:
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
    PlaneX p(p1,p2,p3);
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
  */
  //CalcX, diagonal plane
  {
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    const point<double,3,cartesian> p1(1.0,2.0,3.0);
    const point<double,3,cartesian> p2(2.0,5.0,8.0);
    const point<double,3,cartesian> p3(3.0,7.0,11.0);
    PlaneX p(p1,p2,p3);
    assert( std::abs(p.CalcX(2.0, 3.0)- 1.0) < 0.001);
    assert( std::abs(p.CalcX(5.0, 8.0)- 2.0) < 0.001);
    assert( std::abs(p.CalcX(7.0,11.0)-3.0) < 0.001);
  }
  //CalcX, vertical plane X = 2.0
  /*

    |####/
    |###/
    |##/
    |#/
    |/
 ---+--------
   /|
  / |
 /  |

  */
  {
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    const point<double,3,cartesian> p1(2.0, 3.0, 5.0);
    const point<double,3,cartesian> p2(2.0, 7.0,11.0);
    const point<double,3,cartesian> p3(2.0,13.0,17.0);
    PlaneX p(p1,p2,p3);
    assert( std::abs(p.CalcX(1.0,2.0)-2.0) < 0.001);
    assert( std::abs(p.CalcX(3.0,5.0)-2.0) < 0.001);
    assert( std::abs(p.CalcX(7.0,9.0)-2.0) < 0.001);
  }
  //ToFunction, 3 points and 4 points
  {
    std::function<double(double,double)> f {
      [](const double y, const double z)
      {
        return (2.0 * y) + (3.0 * z) + 5.0;
      }
    };
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    const double y1 { 2.0 };
    const double z1 { 3.0 };
    const double y2 { 5.0 };
    const double z2 { 7.0 };
    const double y3 { 11.0 };
    const double z3 { 13.0 };
    const double y4 { 17.0 };
    const double z4 { 29.0 };
    const point<double,3,cartesian> p1(f(y1,z1),y1,z1);
    const point<double,3,cartesian> p2(f(y2,z2),y2,z2);
    const point<double,3,cartesian> p3(f(y3,z3),y3,z3);
    const PlaneX a(p1,p2,p3);
    assert(a.ToFunction() == "x=(2*y) + (3*z) + 5");
    const point<double,3,cartesian> p4(f(y4,z4),y4,z4);
    const PlaneX b(p1,p2,p3,p4);
    assert(a.ToFunction() == b.ToFunction());
  }
  //GetProjection
  {
    typedef boost::geometry::model::d2::point_xy<double> Point2D;
    typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Point3D;
    using boost::geometry::get;
    /*

    A: (0,0,1)                  A: ( 0,SQRT(2))
    B: (1,0,0)                  B: ( 0,0)
    C: (1,1,0)                  C: ( 1,0)

    |    /
    |   /                          |
    A-----C                        A
    |\/  /      -> becomes ->      |\
    |/\ /                          | \
  --+--B---                    ----B--C--
   /|                              |
  / |                              |
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
    assert(std::abs(get<1>(v[0]) - std::sqrt(2.0) ) < 0.001);
    assert(std::abs(get<0>(v[1]) -           0.0  ) < 0.001);
    assert(std::abs(get<1>(v[1]) -           0.0  ) < 0.001);

    assert(std::abs(get<0>(v[2]) -           1.0  ) < 0.001);
    assert(std::abs(get<1>(v[2]) -           0.0  ) < 0.001);

  }
  //GetProjection, for X = 2 plane
  {
    typedef boost::geometry::model::d2::point_xy<double> Point2D;
    typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Point3D;
    using boost::geometry::get;
    /*

    A: (2,0,0)                  A: (0,0)
    B: (2,1,0)                  B: (1,0)
    C: (2,0,1)                  C: (0,1)

    |######/                 |
    C#####/                  C
    |\###/                   |\
    |#\#/                    | \
    |##B       -> becomes -> |  \
    |#/                      |   \
    |/                       |    \
 ---A--------             ---A-----B---
   /|                        |
  / |                        |
 /  |                        |

    */
    const std::vector<Point2D> v {
      CalcProjection(
        {
          Point3D(2.0,0.0,0.0),
          Point3D(2.0,1.0,0.0),
          Point3D(2.0,0.0,1.0)
        }
      )
    };
    assert(v.size() == 3);
    assert(std::abs(get<0>(v[0]) - 0.0) < 0.001);
    assert(std::abs(get<1>(v[0]) - 0.0) < 0.001);
    assert(std::abs(get<0>(v[1]) - 1.0) < 0.001);
    assert(std::abs(get<1>(v[1]) - 0.0) < 0.001);
    assert(std::abs(get<0>(v[2]) - 0.0) < 0.001);
    assert(std::abs(get<1>(v[2]) - 1.0) < 0.001);

  }
  TRACE("Finished ribi::PlaneX::Test successfully");
}
#endif

std::string ribi::PlaneX::ToFunction() const
{
  try
  {
    std::string s = m_plane_z.ToFunction();
    // 'z=(2*x) + (3*y) + 5'
    //          =>
    // 'x=(2*y) + (3*z) + 5'
    assert(!s.empty());
    s = boost::algorithm::replace_all_copy(s,"*y","*z");
    s = boost::algorithm::replace_all_copy(s,"*x","*y");
    s = boost::algorithm::replace_all_copy(s,"z=","x=");
    return s;
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("ribi::PlaneX::ToFunction: cannot calculate X of a horizontal plane");
  }
}

