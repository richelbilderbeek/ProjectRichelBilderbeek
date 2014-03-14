#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "geometry.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

#include "plane.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::Geometry::Geometry()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::geometry::model::d2::point_xy<double> ribi::Geometry::CalcCenter(const std::vector<boost::geometry::model::d2::point_xy<double>>& points) const noexcept
{
  typedef boost::geometry::model::d2::point_xy<double> T;
  T sum(0.0,0.0);
  for (const auto& point: points)
  {
    sum.x(sum.x() + point.x());
    sum.y(sum.y() + point.y());
  }
  const double n { static_cast<double>(points.size()) };
  const T center(
    sum.x() / n,
    sum.y() / n
  );
  return center;

}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::Geometry::CalcCenter(const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points) const noexcept
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> T;
  double sum_x = 0.0;
  double sum_y = 0.0;
  double sum_z = 0.0;
  for (const auto& point: points)
  {
    sum_x += boost::geometry::get<0>(point);
    sum_y += boost::geometry::get<1>(point);
    sum_z += boost::geometry::get<2>(point);
  }
  const double n { static_cast<double>(points.size()) };
  const T center(
    sum_x / n,
    sum_y / n,
    sum_z / n
  );
  return center;
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::Geometry::CalcCrossProduct(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& a,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& b
) const noexcept
{
  using boost::geometry::get;
  return boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>(
    (get<1>(a) * get<2>(b)) - (get<2>(a) * get<1>(b)),
    (get<2>(a) * get<0>(b)) - (get<0>(a) * get<2>(b)),
    (get<0>(a) * get<1>(b)) - (get<1>(a) * get<0>(b))
  );
}

double ribi::Geometry::CalcDotProduct(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& a,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& b
) const noexcept
{
  using boost::geometry::get;
  return
      (get<0>(a) * get<0>(b))
    + (get<1>(a) * get<1>(b))
    + (get<2>(a) * get<2>(b))
  ;
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::Geometry::CalcNormal(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& a,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& b,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& c
) const noexcept
{
  const auto u(c - a);
  const auto v(b - a);
  return CalcCrossProduct(u,v);
}

std::vector<double> ribi::Geometry::CalcPlane(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
) const noexcept
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
  return { a,b,c,d };

}

/*
boost::geometry::model::d2::point_xy<double> ribi::Geometry::Coordinat2DToBoostGeometryPointXy(
  const Coordinat2D& c
) const noexcept
{
  return boost::geometry::model::d2::point_xy<double>(
    c.GetX(),c.GetY()
  );
}
*/

/*
std::vector<boost::geometry::model::d2::point_xy<double>> ribi::Geometry::Coordinats2DToBoostGeometryPointsXy(
  const std::vector<Coordinat2D>& v
) const noexcept
{
  std::vector<boost::geometry::model::d2::point_xy<double>> w;
  for (auto c: v) { w.push_back(Coordinat2DToBoostGeometryPointXy(c)); }
  return w;
}
*/

double ribi::Geometry::Fmod(const double x, const double mod) const noexcept
{
  #ifndef NDEBUG
  if (std::isnan(x)
    || std::isnan(mod)
    || mod <= 0.0
  )
  {
    TRACE("ERROR");
    TRACE(std::isnan(x));
    TRACE(std::isnan(mod));
    TRACE(x);
    TRACE("BREAK");
  }
  #endif

  assert(!std::isnan(x) && "Fmod its input value cannot be NaN");
  assert(!std::isnan(mod) && "Fmod its input mod cannot be NaN");
  assert(mod != 0.0 && "Cannot do a modulus of zero");
  assert(mod >= 0.0 && "Cannot do a modulus by a negative value");

  if (x < 0.0)
  {
    const double new_x {
      x + (mod * (1 + static_cast<int>(-x / mod)))
    };
    assert(new_x >= 0.0);
    return Fmod(new_x,mod);
  }
  double result = x - (mod * static_cast<int>(x / mod));

  assert(!std::isnan(result) && "Fmod its result cannot be NaN");
  assert(result >= 0.0 && "Fmod must return a value between zero and mod");
  assert(result < mod  && "Fmod must return a value between zero and mod");
  return result;
}

double ribi::Geometry::GetAngle(const double dx, const double dy) const noexcept
{
  const double pi = boost::math::constants::pi<double>();
  const double tau = boost::math::constants::two_pi<double>();
  const double angle = Fmod(pi - (std::atan2(dx,dy)),tau);
  assert(angle >= 0.0 && "GetAngle must return a value between zero and two pi");
  assert(angle < tau  && "GetAngle must return a value between zero and two pi");
  return angle;
}

double ribi::Geometry::GetAngle(const Coordinat2D& p) const noexcept
{
  return GetAngle(
    boost::geometry::get<0>(p),
    boost::geometry::get<1>(p)
  );
}

double ribi::Geometry::GetDistance(const double dx, const double dy) const noexcept
{
  return std::sqrt( (dx * dx) + (dy * dy) );
}

std::string ribi::Geometry::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Geometry::GetVersionHistory() const noexcept
{
  return {
    "2014-02-25: version 1.0: initial version",
    "2014-03-11: version 1.1: removed use of custom coordinat classes, use Boost.Geometry instead"
  };
}

bool ribi::Geometry::IsClockwise(const double a, const double b) const noexcept
{
  const double pi  = boost::math::constants::pi<double>();
  const double tau = boost::math::constants::two_pi<double>();
  const double c { Fmod(a,tau) };
  const double d { Fmod(b,tau) };
  assert(c >= 0);
  assert(c < tau);
  assert(d >= 0);
  assert(d < tau);
  if (d - c >= 0.0 && d - c < pi) return true;
  if (d + tau - c >= 0.0 && d + tau - c < pi) return true;
  return false;
}

bool ribi::Geometry::IsClockwise(const std::vector<double>& angles) const noexcept
{
  const int sz = static_cast<int>(angles.size());
  assert(sz >= 2 && "Need at least two angles to determine if these are clockwise");
  for (int i=0; i!=sz-1; ++i)
  {
    if (!IsClockwise(angles[i],angles[i+1])) return false;
  }
  return true;
}

/*
bool ribi::Geometry::IsClockwise(const std::vector<Coordinat3D>& points, const Coordinat3D& observer) const noexcept
{
  const int n_points { static_cast<int>(points.size()) };
  assert(n_points == 3 || n_points == 4);
  if (n_points == 3)
  {
    const Coordinat3D a { points[0] };
    const Coordinat3D b { points[1] };
    const Coordinat3D c { points[2] };
    const Coordinat3D normal { CalcNormal(a,b,c) };
    const double direction { CalcDotProduct(normal,a - observer) };
    return direction > 0.0;
  }
  else
  {
    assert(n_points == 4);
    //See if the points in the projection are in the same direction
    const std::vector<boost::geometry::model::d2::point_xy<double>> v(
      Plane().CalcProjection(
        {
          points[0].ToBoostGeometryPoint(),
          points[1].ToBoostGeometryPoint(),
          points[2].ToBoostGeometryPoint(),
          points[3].ToBoostGeometryPoint()
        }
      )
    );
    //If the points are messed up, they cannot be clockwise

    if (!IsClockwiseHorizontal(v) && !IsCounterClockwiseHorizontal(v)) return false;
    //The neatly orderder point have the same winding as the first three
    std::vector<Coordinat3D> a;
    std::copy(points.begin() + 0,points.begin() + 3,std::back_inserter(a));
    return IsClockwise(a,observer);
  }
}
*/

bool ribi::Geometry::IsClockwise(const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points, const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& observer) const noexcept
{
  const int n_points = static_cast<int>(points.size());
  assert(n_points == 3 || n_points == 4);
  if (n_points == 3)
  {
    const auto a(points[0]);
    const auto b(points[1]);
    const auto c(points[2]);
    const auto normal(CalcNormal(a,b,c));
    const auto direction(CalcDotProduct(normal,a - observer));
    return direction > 0.0;
  }
  else
  {
    assert(n_points == 4);
    //See if the points in the projection are in the same direction
    assert(Geometry().IsPlane(points));
    const auto v(
      Plane(points[0],points[1],points[2]).CalcProjection(
        {
          points[0],
          points[1],
          points[2],
          points[3]
        }
      )
    );
    //If the points are messed up, they cannot be clockwise
    if (!IsClockwiseHorizontal(v) && !IsCounterClockwiseHorizontal(v)) return false;
    //The neatly orderder point have the same winding as the first three
    std::remove_const<std::remove_reference<decltype(points)>::type>::type a;
    std::copy(points.begin() + 0,points.begin() + 3,std::back_inserter(a));
    return IsClockwise(a,observer);
  }
}

bool ribi::Geometry::IsClockwiseHorizontal(const std::vector<Coordinat3D>& points) const noexcept
{
  using boost::geometry::get;
  const auto center(CalcCenter(points));
  std::vector<double> angles;
  angles.reserve(points.size());
  std::transform(points.begin(),points.end(),
    std::back_inserter(angles),
    [this,center](const Coordinat3D& coordinat)
    {
      return GetAngle(
        get<0>(coordinat) - get<0>(center),
        get<1>(coordinat) - get<1>(center)
      );
    }
  );
  return IsClockwise(angles);
}

bool ribi::Geometry::IsClockwiseHorizontal(const std::vector<boost::geometry::model::d2::point_xy<double>>& points) const noexcept
{
  //Points are determined from their center
  const auto center(CalcCenter(points));
  std::vector<double> angles;
  angles.reserve(points.size());
  std::transform(points.begin(),points.end(),
    std::back_inserter(angles),
    [this,center](const boost::geometry::model::d2::point_xy<double>& coordinat)
    {
      return GetAngle(
        coordinat.x() - center.x(),
        coordinat.y() - center.y()
      );
    }
  );
  return IsClockwise(angles);
}

bool ribi::Geometry::IsConvex(boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon) const noexcept
{
  boost::geometry::correct(polygon);
  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> hull;
  boost::geometry::convex_hull(polygon, hull);
  return boost::geometry::area(hull) == boost::geometry::area(polygon);
}

/*
bool ribi::Geometry::IsConvex(const std::vector<Coordinat3D>& points) const noexcept
{
  return points.empty();
}
*/

bool ribi::Geometry::IsCounterClockwise(const double a, const double b) const noexcept
{
  return !IsClockwise(a,b);
}

bool ribi::Geometry::IsCounterClockwise(const std::vector<double>& angles) const noexcept
{
  const int sz = static_cast<int>(angles.size());
  assert(sz >= 2 && "Need at least two angles to determine if these are counter-clockwise");
  for (int i=0; i!=sz-1; ++i)
  {
    if (!IsCounterClockwise(angles[i],angles[i+1])) return false;
  }
  return true;
}

bool ribi::Geometry::IsCounterClockwiseHorizontal(const std::vector<Coordinat2D>& points) const noexcept
{
  //Points are determined from their center
  const auto center(CalcCenter(points));
  std::vector<double> angles;
  angles.reserve(points.size());
  std::transform(points.begin(),points.end(),
    std::back_inserter(angles),
    [this,center](const Coordinat2D& coordinat)
    {
      return GetAngle(
        coordinat - center
      );
    }
  );
  return IsCounterClockwise(angles);
}

bool ribi::Geometry::IsCounterClockwiseHorizontal(const std::vector<Coordinat3D>& points3d) const noexcept
{
  std::vector<Coordinat2D> points2d;
  for (auto point3d: points3d)
  {
    points2d.push_back(
      {
        boost::geometry::get<0>(point3d),
        boost::geometry::get<1>(point3d)
      }
    );
  }
  return IsCounterClockwiseHorizontal(points2d);
}

/*
bool ribi::Geometry::IsCounterClockwiseHorizontal(const std::vector<boost::geometry::model::d2::point_xy<double>>& points) const noexcept
{
  //Points are determined from their center
  const auto center(CalcCenter(points));
  std::vector<double> angles;
  angles.reserve(points.size());
  std::transform(points.begin(),points.end(),
    std::back_inserter(angles),
    [this,center](const boost::geometry::model::d2::point_xy<double>& coordinat)
    {
      return GetAngle(
        coordinat.x() - center.x(),
        coordinat.y() - center.y()
      );
    }
  );
  return IsCounterClockwise(angles);
}
*/

std::function<bool(const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs)>
  ribi::Geometry::Equals() const noexcept
{
  return [](const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs)
  {
    using boost::geometry::get;
    return
      get<0>(lhs) == get<0>(rhs)
      && get<1>(lhs) == get<1>(rhs)
      && get<2>(lhs) == get<2>(rhs)
    ;
  };
}

bool ribi::Geometry::IsPlane(const std::vector<ribi::Geometry::Coordinat3D>& v) const noexcept
{
  if (v.size() < 3) return false;
  if (v.size() == 3) return true;
  #ifndef NDEBUG
  if (v.size() > 4)
  {
    TRACE("ERROR");
  }
  #endif
  assert(v.size() == 4);
  Plane plane(v[0],v[1],v[2]);
  return plane.IsInPlane(v[3]);
}

std::function<bool(const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs)>
  ribi::Geometry::OrderByX() const noexcept
{
  return [](const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs)
  {
    using boost::geometry::get;
    if (get<0>(lhs) < get<0>(rhs)) return true;
    if (get<0>(lhs) > get<0>(rhs)) return false;
    if (get<1>(lhs) < get<1>(rhs)) return true;
    if (get<1>(lhs) > get<1>(rhs)) return false;
    return get<2>(lhs) < get<2>(rhs);
  };
}

std::function<bool(const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs)>
  ribi::Geometry::OrderByZ() const noexcept
{
  return [](const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs)
  {
    using boost::geometry::get;
    if (get<2>(lhs) < get<2>(rhs)) return true;
    if (get<2>(lhs) > get<2>(rhs)) return false;
    if (get<1>(lhs) < get<1>(rhs)) return true;
    if (get<1>(lhs) > get<1>(rhs)) return false;
    return get<0>(lhs) < get<0>(rhs);
  };
}

#ifndef NDEBUG
void ribi::Geometry::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Geometry::Test");
  const bool verbose { true };
  const double pi { boost::math::constants::pi<double>() };
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;
  const Geometry g;
  if (verbose) TRACE("CalcPlane");
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
    const auto t(g.CalcPlane(p1,p2,p3));
    const double a { t[0] };
    const double b { t[1] };
    const double c { t[2] };
    const double d { t[3] };
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
  if (verbose) TRACE("CalcPlane");
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
    const auto t(g.CalcPlane(p1,p2,p3));
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

  }
  if (verbose) TRACE("Fmod");
  {
    const double expected_min = 1.0 - 0.00001;
    const double expected_max = 1.0 + 0.00001;
    assert(g.Fmod(3.0,2.0) > expected_min && g.Fmod(3.0,2.0) < expected_max);
    assert(g.Fmod(13.0,2.0) > expected_min && g.Fmod(13.0,2.0) < expected_max);
    assert(g.Fmod(-1.0,2.0) > expected_min && g.Fmod(-1.0,2.0) < expected_max);
    assert(g.Fmod(-3.0,2.0) > expected_min && g.Fmod(-3.0,2.0) < expected_max);
    assert(g.Fmod(-13.0,2.0) > expected_min && g.Fmod(-13.0,2.0) < expected_max);
  }
  if (verbose) TRACE("GetAngle");
  {
    const double angle =  g.GetAngle(0.0,-1.0); //North
    const double expected = 0.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(1.0,-1.0); //North-East
    const double expected = 0.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(1.0,0.0); //East
    const double expected = 0.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(1.0,1.0); //South-East
    const double expected = 0.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(0.0,1.0); //South
    const double expected = 1.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(-1.0,1.0); //South-West
    const double expected = 1.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(-1.0,0.0); //West
    const double expected = 1.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(-1.0,-1.0); //North-West
    const double expected = 1.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  if (verbose) TRACE("GetDistance");
  {
    const double distance = g.GetDistance(3.0,4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = g.GetDistance(-3.0,4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = g.GetDistance(3.0,-4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = g.GetDistance(-3.0,-4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  if (verbose) TRACE("IsClockWise of two angles, doubles");
  {
    assert( g.IsClockwise(-2.5 * pi,-2.0 * pi));
    assert(!g.IsClockwise(-2.0 * pi,-2.5 * pi));
    assert( g.IsClockwise(-1.5 * pi,-1.0 * pi));
    assert(!g.IsClockwise(-1.0 * pi,-1.5 * pi));
    assert( g.IsClockwise(-0.5 * pi, 0.0 * pi));
    assert(!g.IsClockwise( 0.0 * pi,-0.5 * pi));
    assert( g.IsClockwise( 0.0 * pi, 0.5 * pi));
    assert(!g.IsClockwise( 0.5 * pi, 0.0 * pi));
    assert( g.IsClockwise( 0.5 * pi, 1.0 * pi));
    assert(!g.IsClockwise( 1.0 * pi, 0.5 * pi));
    assert( g.IsClockwise( 1.5 * pi, 2.0 * pi));
    assert(!g.IsClockwise( 2.0 * pi, 1.5 * pi));
    assert( g.IsClockwise( 2.5 * pi, 3.0 * pi));
    assert(!g.IsClockwise( 3.0 * pi, 2.5 * pi));
  }
  if (verbose) TRACE("IsClockWise of two, vector");
  {
    assert( g.IsClockwise( {-2.5 * pi,-2.0 * pi } ));
    assert(!g.IsClockwise( {-2.0 * pi,-2.5 * pi } ));
    assert( g.IsClockwise( {-1.5 * pi,-1.0 * pi } ));
    assert(!g.IsClockwise( {-1.0 * pi,-1.5 * pi } ));
    assert( g.IsClockwise( {-0.5 * pi, 0.0 * pi } ));
    assert(!g.IsClockwise( { 0.0 * pi,-0.5 * pi } ));
    assert( g.IsClockwise( { 0.0 * pi, 0.5 * pi } ));
    assert(!g.IsClockwise( { 0.5 * pi, 0.0 * pi } ));
    assert( g.IsClockwise( { 0.5 * pi, 1.0 * pi } ));
    assert(!g.IsClockwise( { 1.0 * pi, 0.5 * pi } ));
    assert( g.IsClockwise( { 1.5 * pi, 2.0 * pi } ));
    assert(!g.IsClockwise( { 2.0 * pi, 1.5 * pi } ));
    assert( g.IsClockwise( { 2.5 * pi, 3.0 * pi } ));
    assert(!g.IsClockwise( { 3.0 * pi, 2.5 * pi } ));
  }
  if (verbose) TRACE("IsClockWise of three, vector");
  {
    assert( g.IsClockwise( {-2.5 * pi,-2.0 * pi,-1.75 * pi} ));
    assert(!g.IsClockwise( {-2.0 * pi,-2.5 * pi,-1.75 * pi} ));
    assert( g.IsClockwise( {-1.5 * pi,-1.0 * pi,-0.75 * pi} ));
    assert(!g.IsClockwise( {-1.0 * pi,-1.5 * pi,-0.75 * pi} ));
    assert( g.IsClockwise( {-0.5 * pi, 0.0 * pi, 0.25 * pi } ));
    assert(!g.IsClockwise( { 0.0 * pi,-0.5 * pi, 0.25 * pi } ));
    assert( g.IsClockwise( { 0.0 * pi, 0.5 * pi, 0.75 * pi } ));
    assert(!g.IsClockwise( { 0.5 * pi, 0.0 * pi, 0.75 * pi } ));
    assert( g.IsClockwise( { 0.5 * pi, 1.0 * pi, 1.25 * pi } ));
    assert(!g.IsClockwise( { 1.0 * pi, 0.5 * pi, 1.25 * pi } ));
    assert( g.IsClockwise( { 1.5 * pi, 2.0 * pi, 2.25 * pi } ));
    assert(!g.IsClockwise( { 2.0 * pi, 1.5 * pi, 2.25 * pi } ));
    assert( g.IsClockwise( { 2.5 * pi, 3.0 * pi, 3.25 * pi } ));
    assert(!g.IsClockwise( { 3.0 * pi, 2.5 * pi, 3.25 * pi } ));
  }
  if (verbose) TRACE("IsClockWise of four, vector");
  {
    //Correct order
    assert( g.IsClockwise( {-2.5 * pi,-2.0 * pi,-1.5 * pi,-1.0 * pi} ));
    assert( g.IsClockwise( {-2.0 * pi,-1.5 * pi,-1.0 * pi,-0.5 * pi} ));
    assert( g.IsClockwise( {-1.5 * pi,-1.0 * pi,-0.5 * pi, 0.0 * pi} ));
    assert( g.IsClockwise( {-1.0 * pi,-0.5 * pi, 0.0 * pi, 0.5 * pi} ));
    assert( g.IsClockwise( {-0.5 * pi, 0.0 * pi, 0.5 * pi, 1.0 * pi} ));
    assert( g.IsClockwise( { 0.0 * pi, 0.5 * pi, 1.0 * pi, 1.5 * pi} ));
    assert( g.IsClockwise( { 0.5 * pi, 1.0 * pi, 1.5 * pi, 2.0 * pi} ));
    assert( g.IsClockwise( { 1.0 * pi, 1.5 * pi, 2.0 * pi, 2.5 * pi} ));
    assert( g.IsClockwise( { 1.5 * pi, 2.0 * pi, 2.5 * pi, 3.0 * pi} ));
    assert( g.IsClockwise( { 2.0 * pi, 2.5 * pi, 3.0 * pi, 3.5 * pi} ));
    assert( g.IsClockwise( { 2.5 * pi, 3.0 * pi, 3.5 * pi, 4.0 * pi} ));

    //Swap [0] and [1]
    assert(!g.IsClockwise( {-2.0 * pi,-2.5 * pi,-1.5 * pi,-1.0 * pi} ));
    assert(!g.IsClockwise( {-1.5 * pi,-2.0 * pi,-1.0 * pi,-0.5 * pi} ));
    assert(!g.IsClockwise( {-1.0 * pi,-1.5 * pi,-0.5 * pi, 0.0 * pi} ));
    assert(!g.IsClockwise( {-0.5 * pi,-1.0 * pi, 0.0 * pi, 0.5 * pi} ));
    assert(!g.IsClockwise( { 0.0 * pi,-0.5 * pi, 0.5 * pi, 1.0 * pi} ));
    assert(!g.IsClockwise( { 0.5 * pi, 0.0 * pi, 1.0 * pi, 1.5 * pi} ));
    assert(!g.IsClockwise( { 1.0 * pi, 0.5 * pi, 1.5 * pi, 2.0 * pi} ));
    assert(!g.IsClockwise( { 1.5 * pi, 1.0 * pi, 2.0 * pi, 2.5 * pi} ));
    assert(!g.IsClockwise( { 2.0 * pi, 1.5 * pi, 2.5 * pi, 3.0 * pi} ));
    assert(!g.IsClockwise( { 2.5 * pi, 2.0 * pi, 3.0 * pi, 3.5 * pi} ));
    assert(!g.IsClockwise( { 3.0 * pi, 2.5 * pi, 3.5 * pi, 4.0 * pi} ));

    //Swap [2] and [3]
    assert(!g.IsClockwise( {-2.5 * pi,-2.0 * pi,-1.0 * pi,-1.5 * pi} ));
    assert(!g.IsClockwise( {-2.0 * pi,-1.5 * pi,-0.5 * pi,-1.0 * pi} ));
    assert(!g.IsClockwise( {-1.5 * pi,-1.0 * pi, 0.0 * pi,-0.5 * pi} ));
    assert(!g.IsClockwise( {-1.0 * pi,-0.5 * pi, 0.5 * pi, 0.0 * pi} ));
    assert(!g.IsClockwise( {-0.5 * pi, 0.0 * pi, 1.0 * pi, 0.5 * pi} ));
    assert(!g.IsClockwise( { 0.0 * pi, 0.5 * pi, 1.5 * pi, 1.0 * pi} ));
    assert(!g.IsClockwise( { 0.5 * pi, 1.0 * pi, 2.0 * pi, 1.5 * pi} ));
    assert(!g.IsClockwise( { 1.0 * pi, 1.5 * pi, 2.5 * pi, 2.0 * pi} ));
    assert(!g.IsClockwise( { 1.5 * pi, 2.0 * pi, 3.0 * pi, 2.5 * pi} ));
    assert(!g.IsClockwise( { 2.0 * pi, 2.5 * pi, 3.5 * pi, 3.0 * pi} ));
    assert(!g.IsClockwise( { 2.5 * pi, 3.0 * pi, 4.0 * pi, 3.5 * pi} ));
  }
  if (verbose) TRACE("IsConvex, two dimensions");
  {
    /* Polygons used:

    0123456789012    0123456789012
   0+------------   0+------------
   1|               1|
   2| A---------B   2| A---------B
   3| E        /    3|  \   D   /
   4|  \      /     4|   \ / \ /
   5|   D----C      5|    E   C
    |                |

       Convex           Concave

    */

    //Convex shape
    {
      const std::vector<boost::geometry::model::d2::point_xy<double>> points {
        { 2.0, 2.0}, //A
        {12.0, 2.0}, //B
        { 9.0, 5.0}, //C
        { 4.0, 5.0}, //D
        { 2.0, 3.0}  //E
      };

      boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;
      boost::geometry::append(polygon, points);
      assert(g.IsConvex(polygon));
    }
    //Concave shape
    {
      const std::vector<boost::geometry::model::d2::point_xy<double>> points {
        { 2.0, 2.0}, //A
        {12.0, 2.0}, //B
        { 9.0, 5.0}, //C
        { 7.0, 3.0}, //D
        { 5.0, 5.0}  //E
      };

      boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;
      boost::geometry::append(polygon, points);
      assert(!g.IsConvex(polygon));
    }
  }
  if (verbose) TRACE("IsClockwise in three dimensions, points in XY plane");
  {
    /*

       0 1 2 3
     0 +------X
       |
     1 | A       (seen from above, Z = 1)
       | |\
     2 | C-B
       |
     3 |
       Y

    */

    const Coordinat3D a(1.0, 1.0, 1.0);
    const Coordinat3D b(2.0, 2.0, 1.0);
    const Coordinat3D c(1.0, 2.0, 1.0);
    const std::vector<Coordinat3D> coordinats { a,b,c };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const Coordinat3D above(x, y, 2.0);
        const Coordinat3D below(x, y,-1.0);
        assert( g.IsClockwise(coordinats,above));
        assert(!g.IsClockwise(coordinats,below));
      }
    }
  }
  if (verbose) TRACE("IsClockwise in three dimensions, points in XY plane");
  {
    /*
       0 1 2 3
     0 +------X
       |
     1 | A       (seen from above, Z = 1)
       | |\
     2 | B-C
       |
     3 |
       Y

    */
    const Coordinat3D a(1.0, 1.0, 1.0);
    const Coordinat3D b(1.0, 2.0, 1.0);
    const Coordinat3D c(2.0, 2.0, 1.0);
    const std::vector<Coordinat3D> coordinats { a,b,c };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const Coordinat3D above(x, y, 2.0);
        const Coordinat3D below(x, y,-1.0);
        assert(!g.IsClockwise(coordinats,above));
        assert( g.IsClockwise(coordinats,below));
      }
    }
  }
  if (verbose) TRACE("IsClockwise, clockwise, in three dimensions, four points in XY plane");
  {
    /*

       0 1 2 3
     0 +------X
       |
     1 | A-B     (seen from above, Z = 1)
       | | |
     2 | D-C
       |
     3 |
       Y

    */
    const Coordinat3D a(1.0, 1.0, 1.0);
    const Coordinat3D b(2.0, 1.0, 1.0);
    const Coordinat3D c(2.0, 2.0, 1.0);
    const Coordinat3D d(1.0, 2.0, 1.0);
    const std::vector<Coordinat3D> coordinats { a,b,c,d };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const Coordinat3D above(x, y, 2.0);
        const Coordinat3D below(x, y,-1.0);
        assert( g.IsClockwiseHorizontal(coordinats));
        assert( g.IsClockwise(coordinats,above));
        assert(!g.IsCounterClockwiseHorizontal(coordinats));
        assert(!g.IsClockwise(coordinats,below));
      }
    }
  }
  if (verbose) TRACE("IsClockwise, counter-clockwise, in three dimensions, four points in XY plane");
  {
    /*
       0 1 2 3
     0 +------X
       |
     1 | A-D     (seen from above, Z = 1)
       | | |
     2 | B-C
       |
     3 |
       Y

    */
    const Coordinat3D a(1.0, 1.0, 1.0);
    const Coordinat3D b(1.0, 2.0, 1.0);
    const Coordinat3D c(2.0, 2.0, 1.0);
    const Coordinat3D d(2.0, 1.0, 1.0);
    const std::vector<Coordinat3D> coordinats { a,b,c,d };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const Coordinat3D above(x, y, 2.0);
        const Coordinat3D below(x, y,-1.0);
        assert(!g.IsClockwise(coordinats,above));
        assert( g.IsClockwise(coordinats,below));
      }
    }
  }
  if (verbose) TRACE("IsClockwise, indetermined direction, in three dimensions, four points in XY plane");
  {
    /*
       0 1 2 3
     0 +------X
       |
     1 | A-D     (seen from above, Z = 1)
       |  x
     2 | C-B
       |
     3 |
       Y

    */
    const Coordinat3D a(1.0, 1.0, 1.0);
    const Coordinat3D b(2.0, 2.0, 1.0);
    const Coordinat3D c(1.0, 2.0, 1.0);
    const Coordinat3D d(2.0, 1.0, 1.0);
    const std::vector<Coordinat3D> coordinats { a,b,c,d };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const Coordinat3D above(x, y, 2.0);
        const Coordinat3D below(x, y,-1.0);
        assert(!g.IsClockwise(coordinats,above));
        assert(!g.IsClockwise(coordinats,below));
      }
    }
  }
  TRACE("Finished ribi::Geometry::Test successfully");
}
#endif

std::string ribi::Geometry::ToStr(const boost::geometry::model::d2::point_xy<double>& p) const noexcept
{
  std::stringstream s;
  s
    << "("
    << boost::geometry::get<0>(p)
    << ","
    << boost::geometry::get<1>(p)
    << ")"
  ;
  return s.str();
}

std::string ribi::Geometry::ToStr(const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p) const noexcept
{
  std::stringstream s;
  s
    << "("
    << boost::geometry::get<0>(p)
    << ","
    << boost::geometry::get<1>(p)
    << ","
    << boost::geometry::get<2>(p)
    << ")"
  ;
  return s.str();
}

boost::geometry::model::d2::point_xy<double> ribi::operator-(
  const boost::geometry::model::d2::point_xy<double>& a,
  const boost::geometry::model::d2::point_xy<double>& b
) noexcept
{
  return std::remove_const<std::remove_reference<decltype(a)>::type>::type(
    boost::geometry::get<0>(a) - boost::geometry::get<0>(b),
    boost::geometry::get<1>(a) - boost::geometry::get<1>(b)
  );
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>
  ribi::operator-(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& a,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& b
  ) noexcept
{
  return std::remove_const<std::remove_reference<decltype(a)>::type>::type(
  //return boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>(
    boost::geometry::get<0>(a) - boost::geometry::get<0>(b),
    boost::geometry::get<1>(a) - boost::geometry::get<1>(b),
    boost::geometry::get<2>(a) - boost::geometry::get<2>(b)
  );
}
