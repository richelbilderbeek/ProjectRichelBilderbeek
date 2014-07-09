//---------------------------------------------------------------------------
/*
Geometry, class with geometry functions
Copyright (C) 2014-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGeometry.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "geometry.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>
#include <boost/xpressive/xpressive.hpp>
#ifndef WIN32
#include <boost/geometry/geometries/linestring.hpp>
#endif

#include <QPen>
#include <QPoint>
#include <QRect>

#include "ribi_regex.h"
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
  typedef Coordinat2D T;
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

ribi::Geometry::Coordinat3D ribi::Geometry::CalcCrossProduct(
  const Coordinat3D& a,
  const Coordinat3D& b
) const noexcept
{
  using boost::geometry::get;
  return Coordinat3D(
    (get<1>(a) * get<2>(b)) - (get<2>(a) * get<1>(b)),
    (get<2>(a) * get<0>(b)) - (get<0>(a) * get<2>(b)),
    (get<0>(a) * get<1>(b)) - (get<1>(a) * get<0>(b))
  );
}

ribi::Geometry::ApCoordinat3D ribi::Geometry::CalcCrossProduct(
  const ApCoordinat3D& a,
  const ApCoordinat3D& b
) const noexcept
{
  using boost::geometry::get;
  return ApCoordinat3D(
    (get<1>(a) * get<2>(b)) - (get<2>(a) * get<1>(b)),
    (get<2>(a) * get<0>(b)) - (get<0>(a) * get<2>(b)),
    (get<0>(a) * get<1>(b)) - (get<1>(a) * get<0>(b))
  );
}

double ribi::Geometry::CalcDotProduct(
  const Coordinat3D& a,
  const Coordinat3D& b
) const noexcept
{
  using boost::geometry::get;
  return
      (get<0>(a) * get<0>(b))
    + (get<1>(a) * get<1>(b))
    + (get<2>(a) * get<2>(b))
  ;
}

ribi::Geometry::Coordinat3D ribi::Geometry::CalcNormal(
  const Coordinat3D& a,
  const Coordinat3D& b,
  const Coordinat3D& c
) const noexcept
{
  const auto u(c - a);
  const auto v(b - a);
  return CalcCrossProduct(u,v);
}

std::vector<double> ribi::Geometry::CalcPlane(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
) const noexcept
{
  const std::vector<apfloat> v
    = CalcPlane(ToApfloat(p1),ToApfloat(p2),ToApfloat(p3)
  );
  return ToDouble(v);
}

std::vector<apfloat> ribi::Geometry::CalcPlane(
  const ApCoordinat3D& p1,
  const ApCoordinat3D& p2,
  const ApCoordinat3D& p3
) const noexcept
{
  using boost::geometry::get;
  const auto v1 = p3 - p1;
  const auto v2 = p2 - p1;

  const auto cross = CalcCrossProduct(v1,v2);

  const auto a = get<0>(cross);
  const auto b = get<1>(cross);
  const auto c = get<2>(cross);

  const auto x = get<0>(p1);
  const auto y = get<1>(p1);
  const auto z = get<2>(p1);

  const auto term1 = a * x;
  const auto term2 = b * y;
  const auto term3 = c * z;
  const auto d = term1 + term2 + term3;

  return { a,b,c,d };
}

ribi::Geometry::ApCoordinats2D ribi::Geometry::CalcProjection(
  const ribi::Geometry::ApCoordinats3D& points) const
{
  assert(points.size() >= 3);
  #ifdef FIX_ISSUE_224
  assert(IsPlane(points));
  #else
  #ifndef NDEBUG
  if(!IsPlane(points))
  {
    TRACE("Warning: points appear not to be in a plane");
  }
  #endif
  #endif
  const std::unique_ptr<Plane> plane(new Plane(points[0],points[1],points[2]));
  assert(plane);

  #ifndef NDEBUG
  const bool verbose = false;
  if (verbose)
  {
    TRACE(plane->CanCalcX());
    TRACE(plane->CanCalcY());
    TRACE(plane->CanCalcZ());
    //try { TRACE(plane->ToFunctionX()); } catch (std::exception&) {}
    //try { TRACE(plane->ToFunctionY()); } catch (std::exception&) {}
    //try { TRACE(plane->ToFunctionZ()); } catch (std::exception&) {}
  }
  #endif

  return plane->CalcProjection(points);
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
  ribi::Geometry::CreateHouseShape() const noexcept
{
  /*

    3-
     |
    2-    0
     |   / \
    1-  4   1
     |  |   |
    0-  3---2
     |
     +--|---|---|
        0   1   2

  */
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  //typedef boost::geometry::model::polygon<Coordinat2D> Polygon;


  const std::vector<Coordinat2D> points {
    {0.5, 2.0}, //0
    {1.0, 1.0}, //1
    {1.0, 0.0}, //2
    {0.0, 0.0}, //3
    {0.0, 1.0}  //4
  };

  boost::geometry::model::polygon<Coordinat2D> house;
  boost::geometry::append(house, points);
  return house;
}

ribi::Geometry::Coordinat3D ribi::Geometry::CreatePoint(
  const double x,
  const double y,
  const double z
) const noexcept
{
  const auto c(Coordinat3D(x,y,z));
  return c;
}

ribi::Geometry::Rect ribi::Geometry::CreateRect(
  const double left,
  const double top,
  const double width,
  const double height
) const noexcept
{
  boost::geometry::model::box<Coordinat2D> rect(
    Coordinat2D(left        , top         ),
    Coordinat2D(left + width, top + height)
  );
  return rect;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
  ribi::Geometry::CreateShapeHeart(const double scale) const noexcept
{
  const std::vector<boost::geometry::model::d2::point_xy<double>> points {
    { 0.0 * scale, 1.0 * scale}, //0
    { 1.0 * scale, 2.0 * scale}, //1
    { 2.0 * scale, 1.0 * scale}, //2
    { 2.0 * scale, 0.0 * scale}, //3
    { 0.0 * scale,-2.0 * scale}, //4
    {-2.0 * scale, 0.0 * scale}, //5
    {-2.0 * scale, 1.0 * scale}, //6
    {-1.0 * scale, 2.0 * scale}  //7
  };
  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
  boost::geometry::append(v, points);
  return v;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
  ribi::Geometry::CreateShapeHouse(const double scale) const noexcept
{
  const std::vector<boost::geometry::model::d2::point_xy<double>> points {
    { 0.0 * scale, 2.0 * scale}, //0
    { 1.0 * scale, 1.0 * scale}, //1
    { 1.0 * scale,-1.0 * scale}, //2
    {-1.0 * scale,-1.0 * scale}, //3
    {-1.0 * scale, 1.0 * scale}  //4
  };
  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
  boost::geometry::append(v, points);
  return v;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
  ribi::Geometry::CreateShapePolygon(
  const int n,
  const double rotation,
  const double scale
) const noexcept
{
  assert(n >= 3 && "A polygon has at least three edges");
  const double tau { boost::math::constants::two_pi<double>() };
  std::vector<boost::geometry::model::d2::point_xy<double>> points;
  for (int i=0; i!=n; ++i)
  {
    const double angle { tau * static_cast<double>(i) / static_cast<double>(n) };
    const double x {  std::sin(angle + rotation) };
    const double y { -std::cos(angle + rotation) };
    boost::geometry::model::d2::point_xy<double> point(x * scale, y * scale);
    points.push_back(point);
  }

  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
  boost::geometry::append(v, points);
  return v;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
  ribi::Geometry::CreateShapeTriangle(const double scale) const noexcept
{
  const std::vector<boost::geometry::model::d2::point_xy<double>> points {
    { 0.0 * scale, 0.0 * scale}, //0
    { 1.0 * scale, 0.0 * scale}, //1
    { 0.0 * scale, 1.0 * scale}  //2
  };
  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
  boost::geometry::append(v, points);
  return v;
}

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
  //return GetDistance(
  //  boost::geometry::model::d2::point_xy<double>(0.0,0.0),
  //  boost::geometry::model::d2::point_xy<double>(dx,dy)
  //);
  return std::sqrt( (dx * dx) + (dy * dy) );
}

double ribi::Geometry::GetDistance(
  const boost::geometry::model::d2::point_xy<double>& a,
  const boost::geometry::model::d2::point_xy<double>& b
  ) const noexcept
{
  //return GetDistance(a.x() - b.x(),a.y() - b.y());
  return boost::geometry::distance(a,b);
}



std::string ribi::Geometry::GetVersion() const noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::Geometry::GetVersionHistory() const noexcept
{
  return {
    "2014-02-25: version 1.0: initial version",
    "2014-03-11: version 1.1: removed use of custom coordinat classes, use Boost.Geometry instead"
    "2014-03-25: version 1.2: fixed bug in IsConvex",
    "2014-05-01: version 1.3: minor improments and cleanup"
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

bool ribi::Geometry::IsClockwise(
  const ApCoordinats3D& points,
  const ApCoordinat3D& observer
) const noexcept
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
    const bool is_clockwise { direction > 0.0 };
    return is_clockwise;
  }
  else
  {
    assert(n_points == 4);
    //See if the points in the projection are in the same direction
    #ifdef FIX_ISSUE_224
    assert(Geometry().IsPlane(points));
    #endif
    const std::unique_ptr<Plane> plane(new Plane(points[0],points[1],points[2]));
    assert(plane);
    const auto v(
      ToDoubleSafe(
        plane->CalcProjection(
          {
            points[0],
            points[1],
            points[2],
            points[3]
          }
        )
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
    [this,center](const Coordinat2D& coordinat)
    {
      return GetAngle(
        coordinat.x() - center.x(),
        coordinat.y() - center.y()
      );
    }
  );
  return IsClockwise(angles);
}

bool ribi::Geometry::IsConvex(Polygon polygon) const noexcept
{
  //assert(boost::geometry::num_points(polygon) == points.size()
  //  && "Points and polygon have the same number of points");
  const bool verbose = false;
  boost::geometry::correct(polygon);
  Polygon hull;
  boost::geometry::convex_hull(polygon, hull);
  const bool is_convex_first = boost::geometry::equals(polygon,hull);
  if (verbose) { TRACE(is_convex_first); }
  if (is_convex_first)
  {
    return true;
  }
  //Correct for bug https://svn.boost.org/trac/boost/ticket/9873
  //A polygon is convex when it does not use the edge with the possibly longest distance
  const std::vector<Coordinat2D> v = polygon.outer();
  //Find longest distance
  double max_dist = 0.0;
  const int sz = static_cast<int>(v.size());
  for (int i=0; i!=sz; ++i)
  {
    for (int j=i+1; j!=sz; ++j)
    {
      const double dist = GetDistance(v[i],v[j]);
      if (dist > max_dist) { max_dist = dist; }
    }
  }

  for (int i=1; i!=sz; ++i)
  {
    const double dist = GetDistance(v[i-1],v[i]);
    if (dist == max_dist) return false;
  }
  return true;
}

bool ribi::Geometry::IsConvex(const std::vector<Coordinat2D>& points) const noexcept
{
  Polygon polygon;
  for (const auto point: points)
  {
    //TRACE(ToStr(point));
    boost::geometry::append(polygon,point);
  };
  assert(boost::geometry::num_points(polygon) == points.size());
  const bool is_convex = IsConvex(polygon);
  return is_convex;
}

bool ribi::Geometry::IsConvex(const ApCoordinats3D& points) const noexcept
{
  const bool verbose = false;

  #ifndef NDEBUG
  assert(points.size() >= 3);
  if (points.size() == 3)
  {
    //Three different points are always convex
    assert(!boost::geometry::equals(points[0],points[1]));
    assert(!boost::geometry::equals(points[0],points[2]));
    assert(!boost::geometry::equals(points[1],points[2]));
    return true;
  }
  assert(points.size() == 4);
  #ifdef FIXING_ISSUE_224
  if(!IsPlane(points))
  {
    TRACE("ERROR");
    TRACE(points.size());
    for (const auto point: points) { TRACE(Geometry().ToStr(point)); }
    TRACE("BREAK");
  }
  assert(IsPlane(points));
  #endif // FIXING_ISSUE_224
  #endif // NDEBUG
  if (verbose)
  {
    std::stringstream s;
    s << "{";
    for (const auto point3d: points)
    {
      s << ToStr(point3d) << ",";
    }
    std::string po_str(s.str());
    po_str[po_str.size() - 1] = '}';
    TRACE(po_str);
  }
  //Use the first three points for a Plane
  for (const std::vector<int> v:
    {
      std::vector<int>( {0,1,2} ),
      std::vector<int>( {0,1,3} ),
      std::vector<int>( {0,2,1} ),
      std::vector<int>( {0,2,3} ),
      std::vector<int>( {0,3,1} ),
      std::vector<int>( {0,3,2} ),
      std::vector<int>( {1,0,2} ),
      std::vector<int>( {1,0,3} ),
      std::vector<int>( {1,2,0} ),
      std::vector<int>( {1,2,3} ),
      std::vector<int>( {1,3,0} ),
      std::vector<int>( {1,3,2} ),
      std::vector<int>( {2,0,1} ),
      std::vector<int>( {2,0,3} ),
      std::vector<int>( {2,1,0} ),
      std::vector<int>( {2,1,3} ),
      std::vector<int>( {2,3,0} ),
      std::vector<int>( {2,3,1} ),
      std::vector<int>( {3,0,1} ),
      std::vector<int>( {3,0,2} ),
      std::vector<int>( {3,1,0} ),
      std::vector<int>( {3,1,2} ),
      std::vector<int>( {3,2,0} ),
      std::vector<int>( {3,2,1} )
    }
  )
  {
    const boost::shared_ptr<Plane> plane(
      new Plane(
        points[v[0]],
        points[v[1]],
        points[v[2]]
      )
    );
    assert(plane);

    #ifndef NDEBUG
    if (verbose)
    {
      TRACE(*plane);
      TRACE(plane->CanCalcX());
      TRACE(plane->CanCalcY());
      TRACE(plane->CanCalcZ());
      //try { TRACE(plane->ToFunctionX()); } catch (std::exception&) {}
      //try { TRACE(plane->ToFunctionY()); } catch (std::exception&) {}
      //try { TRACE(plane->ToFunctionZ()); } catch (std::exception&) {}
    }
    #endif

    const ApCoordinats2D apcoordinats2d = plane->CalcProjection(points);
    const Coordinats2D coordinats2d = ToDoubleSafe(apcoordinats2d);
    if (IsConvex(coordinats2d)) return true;
  }
  return false;
}

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

bool ribi::Geometry::IsCounterClockwise(
  const ribi::Geometry::ApCoordinats3D& points,
  const ribi::Geometry::ApCoordinat3D& observer
) const noexcept
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
    return direction < 0.0; //Difference between CW ('>') and CCW ('<')
  }
  else
  {
    assert(n_points == 4);
    //See if the points in the projection are in the same direction
    #ifdef FIX_ISSUE_224
    assert(Geometry().IsPlane(points));
    #endif // FIX_ISSUE_224
    const std::unique_ptr<Plane> plane(new Plane(points[0],points[1],points[2]));
    assert(plane);
    const auto v(
      plane->CalcProjection(
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
    return IsCounterClockwise(a,observer);
  }
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
  for (const auto point3d: points3d)
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

std::function<bool(const ribi::Geometry::Coordinat2D& lhs, const ribi::Geometry::Coordinat2D& rhs)>
  ribi::Geometry::Equals2d() const noexcept
{
  return [](const ribi::Geometry::Coordinat2D& lhs, const ribi::Geometry::Coordinat2D& rhs)
  {
    using boost::geometry::get;
    return
      get<0>(lhs) == get<0>(rhs)
      && get<1>(lhs) == get<1>(rhs)
    ;
  };
}

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

bool ribi::Geometry::IsPlane(const std::vector<ApCoordinat3D>& v) const noexcept
{
  const bool verbose = false;
  using boost::geometry::get;

  if (v.size() < 3) return false;
  if (v.size() == 3) return true;
  #ifndef NDEBUG
  if (v.size() > 4)
  {
    TRACE("ERROR");
    TRACE(v.size());
    TRACE("BREAK");
  }
  #endif
  assert(v.size() == 4);

  try
  {
    const std::unique_ptr<Plane> plane(new Plane(v[0],v[1],v[2]));
    assert(plane);
    return plane->IsInPlane(v[3]);
  }
  catch (std::logic_error& e)
  {
    if (verbose)
    {
      std::stringstream s;
      s << "Geometry::IsPlane: not in plane, as plane cannot be constructed ('"
        << e.what() << "')"
      ;
      TRACE(s.str());
    }
    return false;
  }
}


std::function<bool(const ribi::Geometry::Coordinat2D& lhs, const ribi::Geometry::Coordinat2D& rhs)>
  ribi::Geometry::Order2dByX() const noexcept
{
  return [](const ribi::Geometry::Coordinat2D& lhs, const ribi::Geometry::Coordinat2D& rhs)
  {
    using boost::geometry::get;
    if (get<0>(lhs) < get<0>(rhs)) return true;
    if (get<0>(lhs) > get<0>(rhs)) return false;
    return get<1>(lhs) < get<1>(rhs);
  };
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

ribi::Geometry::Linestring ribi::Geometry::Rescale(
  const Linestring& linestring,
  const double scale,
  const double scale_origin_x,
  const double scale_origin_y
) const noexcept
{
  std::vector<Coordinat2D> v;


  for (const auto& point:linestring)
  {
    const double x = point.x();
    const double dx = x - scale_origin_x;
    const double new_x = scale_origin_x + (scale * dx);

    const double y = point.y();
    const double dy = y - scale_origin_y;
    const double new_y = scale_origin_y + (scale * dy);

    v.push_back(Coordinat2D(new_x,new_y));
  }

  Linestring new_linestring;
  boost::geometry::append(new_linestring,v);
  return new_linestring;
}


ribi::Geometry::Linestrings ribi::Geometry::Rescale(
  const Linestrings& linestrings,
  const double scale,
  const double scale_origin_x,
  const double scale_origin_y
) const noexcept
{
  Linestrings new_linestrings;
  for (const auto linestring: linestrings)
  {
    new_linestrings.push_back(
      Rescale(linestring,scale,scale_origin_x,scale_origin_y)
    );
  }
  return new_linestrings;
}

ribi::Geometry::Polygon ribi::Geometry::Rescale(
  const Polygon& polygon,
  const double scale,
  const double scale_origin_x,
  const double scale_origin_y
) const noexcept
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

  boost::geometry::model::ring<Coordinat2D> points;
  boost::geometry::convert(polygon,points);

  for (auto& point:points)
  {
    const double x = point.x();
    const double dx = x - scale_origin_x;
    const double new_x = scale_origin_x + (scale * dx);

    const double y = point.y();
    const double dy = y - scale_origin_y;
    const double new_y = scale_origin_y + (scale * dy);

    point = Coordinat2D(new_x,new_y);
  }

  Polygon new_polygon;
  boost::geometry::append(new_polygon, points);
  return new_polygon;
}

ribi::Geometry::Polygons ribi::Geometry::Rescale(
  const Polygons& polygons,
  const double scale,
  const double scale_origin_x,
  const double scale_origin_y
) const noexcept
{
  Polygons new_polygons;
  for (const auto polygon: polygons)
  {
    new_polygons.push_back(
      Rescale(polygon,scale,scale_origin_x,scale_origin_y)
    );
  }
  return new_polygons;
}

ribi::Geometry::Shapes ribi::Geometry::Rescale(
  const Shapes& shapes,
  const double scale,
  const double scale_origin_x,
  const double scale_origin_y
) const noexcept
{
  Shapes new_shapes;
  new_shapes.first
    = Rescale(shapes.first,scale,scale_origin_x,scale_origin_y);
  new_shapes.second
    = Rescale(shapes.second,scale,scale_origin_x,scale_origin_y);
  return new_shapes;
}


ribi::Geometry::ApCoordinat3D ribi::Geometry::ToApfloat(const Coordinat3D& p) const noexcept
{
  using boost::geometry::get;
  return ApCoordinat3D(
    get<0>(p),
    get<1>(p),
    get<2>(p)
  );
}

double ribi::Geometry::ToDouble(const apfloat& a) const
{
  std::stringstream s;
  s << std::fixed << std::setprecision(99) << a;
  //s << pretty << a;
  //TRACE(s.str());
  const double x = boost::lexical_cast<double>(s.str());
  return x;
}

std::vector<double> ribi::Geometry::ToDouble(const std::vector<apfloat>& v) const
{
  std::vector<double> w;
  std::transform(std::begin(v),std::end(v),std::back_inserter(w),
    [this](const apfloat& f) { return ToDouble(f); }
  );
  assert(v.size() == w.size());
  return w;
}

ribi::Geometry::Polygon ribi::Geometry::ToPolygon(const Linestring& linestring) const noexcept
{
  std::vector<Coordinat2D> v;
  for (const auto point: linestring) { v.push_back(point); }

  Polygon polygon;
  if (v.empty()) return polygon;
  if (boost::geometry::equals(v.front(),v.back())) { v.pop_back(); }

  boost::geometry::append(polygon,v);
  return polygon;
}

std::string ribi::Geometry::ToStr(const apfloat& f) const noexcept
{
  try
  {
    std::stringstream s;
    s << f;
    return s.str();
  }
  catch (...)
  {
    assert(!"Should not get here");
    throw;
  }
}

std::string ribi::Geometry::ToStr(const Coordinat2D& p) const noexcept
{
  std::stringstream s;
  s << p;
  return s.str();
}

std::string ribi::Geometry::ToStr(const Coordinat3D& p) const noexcept
{
  std::stringstream s;
  s << p;
  return s.str();
}

std::string ribi::Geometry::ToStr(const Linestring& linestring) const noexcept
{
  std::stringstream s;
  s << linestring;
  return s.str();
}

std::string ribi::Geometry::ToStr(const Polygon& polygon) const noexcept
{
  std::stringstream s;
  s << polygon;
  return s.str();
}

std::string ribi::Geometry::ToSvg(
  const Polygons& polygons,
  const double stroke_width
) const noexcept
{
  assert(stroke_width > 0.0);
  std::stringstream s;
  s
    << std::setprecision(99)
    << R"*(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)*"
    << '\n'
    << ToSvgStr(polygons,stroke_width) << '\n'
    << R"*(</svg>)*"
  ;
  return s.str();
}

std::string ribi::Geometry::ToSvg(
  const Polygons& polygons,
  const Linestrings& linestrings,
  const double stroke_width
) const noexcept
{
  assert(stroke_width > 0.0);
  std::stringstream s;
  s
    << std::setprecision(99)
    << R"*(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)*"
    << '\n'
    << ToSvgStr(polygons,stroke_width) << '\n'
    << ToSvgStr(linestrings,stroke_width) << '\n'
    << R"*(</svg>)*"
  ;
  return s.str();
}

std::string ribi::Geometry::ToSvgStr(
  const Polygons& polygons,
  const double stroke_width
) const noexcept
{
  assert(stroke_width > 0.0);
  std::stringstream s;
  for (const Polygon& polygon: polygons)
  {
    s << ToSvgStr(polygon,stroke_width) << '\n';
  }
  return s.str();
}

std::string ribi::Geometry::ToSvgStr(
  const Linestrings& linestrings,
  const double stroke_width
) const noexcept
{
  assert(stroke_width > 0.0);
  std::stringstream s;
  for (const Linestring& linestring: linestrings)
  {
    s << ToSvgStr(linestring,stroke_width) << '\n';
  }
  return s.str();
}

std::string ribi::Geometry::ToSvgStr(
  const Polygon& polygon,
  const double stroke_width
) const noexcept
{
  if (stroke_width <= 0.0) { return ""; }
  assert(stroke_width > 0.0);
  const std::vector<Coordinat2D> points = polygon.outer();
  const int n_points = static_cast<int>(points.size());
  if (n_points < 3) { return ""; }
  assert(n_points >= 3 && "A polygon has at least three points");
  //Move to first point
  std::stringstream s;
  s
    << std::setprecision(99)
    <<  R"*(  <path d="M )*"
    << points[0].x()
    << " "
    << points[0].y()
  ;
  //Draw lines to others
  s << " L ";
  for (int i=1; i!=n_points; ++i)
  {
    s
      << points[i].x()
      << " "
      << points[i].y()
      << " "
    ;

    //No trailing comma
    if (i != n_points - 1)
    {
      s << ",";
    }
  }
  s
    << R"*(z" stroke="black" fill="none" stroke-width=")*"
    << stroke_width
    << R"*("/>)*"
  ;
  return s.str();
}

std::string ribi::Geometry::ToSvgStr(
  const Linestring& linestring,
  const double stroke_width
) const noexcept
{
  if (stroke_width <= 0.0) { return ""; }
  assert(stroke_width > 0.0);
  const std::vector<Coordinat2D> points = linestring;
  const int n_points = static_cast<int>(points.size());
  if (n_points < 2) { return ""; }
  assert(n_points >= 2 && "A linestring has at least two points");
  //Move to first point
  std::stringstream s;
  s
    << std::setprecision(99)
    <<  R"*(  <path d="M )*"
    << points[0].x()
    << " "
    << points[0].y()
  ;
  //Draw lines to others
  s << " L ";
  for (int i=1; i!=n_points; ++i)
  {
    s
      << points[i].x()
      << " "
      << points[i].y()
      << " "
    ;

    //No trailing comma
    if (i != n_points - 1) { s << ","; }
  }
  s
    << R"*(" stroke="black" fill="none" stroke-width=")*"
    << stroke_width
    << R"*("/>)*"
  ;
  return s.str();
}

std::string ribi::Geometry::ToWkt(
  const Polygons& polygons,
  const Linestrings& linestrings
) const noexcept
{
  std::string s;
  for (const auto polygon:polygons)
  {
    const auto w = boost::geometry::wkt<>(polygon);
    std::stringstream t;
    t << w << ',';
    s += t.str();
  }
  for (const auto linestring:linestrings)
  {
    const auto w = boost::geometry::wkt<>(linestring);
    std::stringstream t;
    t << w << ',';
    s += t.str();
  }
  if (!s.empty()) s.pop_back();
  return s;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
  ribi::Geometry::Translate(
    const boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>& shape,
    const double dx,
    const double dy
  ) const noexcept
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

  boost::geometry::model::ring<Coordinat2D> points;
  boost::geometry::convert(shape,points);

  for (auto& point:points)
  {
    point = Coordinat2D(point.x() + dx, point.y() + dy);
  }

  Polygon new_shape;
  boost::geometry::append(new_shape, points);
  return new_shape;
}

ribi::Geometry::Linestring ribi::Geometry::WktToLinestring(const std::string& wkt) const
{
  Linestring linestring;
  boost::geometry::read_wkt(wkt,linestring);
  return linestring;
}

ribi::Geometry::Polygon ribi::Geometry::WktToPolygon(const std::string& wkt) const
{
  Polygon polygon;
  boost::geometry::read_wkt(wkt,polygon);
  return polygon;
}

ribi::Geometry::Shapes ribi::Geometry::WktToShapes(const std::string& wkt) const
{
  std::vector<std::string> v;
  const std::string regex_str = Regex().GetRegexShapes();
  for (const auto s: Regex().GetRegexMatches(wkt,regex_str))
  {
    v.push_back(s);
  }
  return WktToShapes(v);
}

ribi::Geometry::Shapes ribi::Geometry::WktToShapes(const std::vector<std::string>& wkt) const
{
  Polygons polygons;
  Linestrings linestrings;
  for (const auto s: wkt)
  {
    try
    {
      const auto polygon = WktToPolygon(s);
      //boost::geometry::read_wkt(s,polygon);
      polygons.push_back(polygon);
    }
    catch (std::exception&)
    {
      //OK
    }

    try
    {
      const auto linestring = WktToLinestring(s);
      //Linestring linestring;
      //boost::geometry::read_wkt(s,linestring);
      linestrings.push_back(linestring);
    }
    catch (std::exception&)
    {
      //OK
    }
  }
  const auto shapes = std::make_pair(polygons,linestrings);
  return shapes;
}


std::string ribi::Geometry::WktToSvg(const std::string& wkt, const double svg_stroke_width) const
{
  return ToSvg(WktToShapes(wkt),svg_stroke_width);
}

std::string ribi::Geometry::WktToSvg(const std::vector<std::string>& wkt, const double svg_stroke_width) const
{
  return ToSvg(WktToShapes(wkt),svg_stroke_width);
}

ribi::Geometry::Coordinat2D ribi::operator-(
  const ribi::Geometry::Coordinat2D& a,
  const ribi::Geometry::Coordinat2D& b
) noexcept
{
  return std::remove_const<std::remove_reference<decltype(a)>::type>::type(
    boost::geometry::get<0>(a) - boost::geometry::get<0>(b),
    boost::geometry::get<1>(a) - boost::geometry::get<1>(b)
  );
}

ribi::Geometry::Coordinat3D ribi::operator-(
    const ribi::Geometry::Coordinat3D& a,
    const ribi::Geometry::Coordinat3D& b
  ) noexcept
{
  return std::remove_const<std::remove_reference<decltype(a)>::type>::type(
    boost::geometry::get<0>(a) - boost::geometry::get<0>(b),
    boost::geometry::get<1>(a) - boost::geometry::get<1>(b),
    boost::geometry::get<2>(a) - boost::geometry::get<2>(b)
  );
}

ribi::Geometry::ApCoordinat3D ribi::operator-(
    const ribi::Geometry::ApCoordinat3D& a,
    const ribi::Geometry::ApCoordinat3D& b
  ) noexcept
{
  return std::remove_const<std::remove_reference<decltype(a)>::type>::type(
    boost::geometry::get<0>(a) - boost::geometry::get<0>(b),
    boost::geometry::get<1>(a) - boost::geometry::get<1>(b),
    boost::geometry::get<2>(a) - boost::geometry::get<2>(b)
  );
}

std::ostream& ribi::operator<<(std::ostream& os, const Geometry::Coordinat2D& p) noexcept
{
  using boost::geometry::get;
  os << '(' << get<0>(p) << ',' << get<1>(p) << ')';
  return os;
}

std::ostream& ribi::operator<<(std::ostream& os, const Geometry::Coordinat3D& p) noexcept
{
  using boost::geometry::get;
  os << '(' << get<0>(p) << ',' << get<1>(p) << ',' << get<2>(p) << ')';
  return os;
}

std::ostream& ribi::operator<<(std::ostream& os, const Geometry::Linestring& p) noexcept
{
  const auto points = p;
  const int n_points = static_cast<int>(points.size());
  for (int i=0; i!=n_points; ++i)
  {
    os << points[i];
    if (i != n_points-1) { os << ','; }
  }
  return os;
}

std::ostream& ribi::operator<<(std::ostream& os, const Geometry::Polygon& p) noexcept
{
  const auto points = p.outer();
  const int n_points = static_cast<int>(points.size());
  for (int i=0; i!=n_points; ++i)
  {
    os << points[i];
    if (i != n_points-1) { os << ','; }
  }
  return os;
}

std::ostream& ribi::operator<<(std::ostream& os,const QPen& pen) noexcept
{
  os << pen.color() << " (" << pen.widthF() << ')';
  return os;
}

std::ostream& ribi::operator<<(std::ostream& os,const QPoint& point) noexcept
{
  os << '(' << point.x() << ',' << point.y() << ')';
  return os;
}

std::ostream& ribi::operator<<(std::ostream& os,const QPointF& point) noexcept
{
  os << '(' << point.x() << ',' << point.y() << ')';
  return os;
}

std::ostream& ribi::operator<<(std::ostream& os,const QRect& rect) noexcept
{
  os
    << '(' << rect.left() << ',' << rect.top() << ')'
    << ','
    << '(' << rect.width() << 'x' << rect.height() << ')'
  ;
  return os;
}

std::ostream& ribi::operator<<(std::ostream& os,const QRectF& rect) noexcept
{
  os
    << '(' << rect.left() << ',' << rect.top() << ')'
    << ','
    << '(' << rect.width() << 'x' << rect.height() << ')'
  ;
  return os;

}
