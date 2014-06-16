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

std::vector<boost::geometry::model::d2::point_xy<double>> ribi::Geometry::CalcProjection(
  const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points) const
{
  assert(points.size() >= 3);
  assert(IsPlane(points));
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

  const std::vector<boost::geometry::model::d2::point_xy<double>> coordinats2d(
    plane->CalcProjection(points)
  );
  return coordinats2d;
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
  ribi::Geometry::CreateShapeHeart(const double scale) noexcept
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
  ribi::Geometry::CreateShapeHouse(const double scale) noexcept
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
) noexcept
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
  ribi::Geometry::CreateShapeTriangle(const double scale) noexcept
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

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
std::vector<std::string>
  ribi::Geometry::GetRegexMatches(
  const std::string& s,
  const std::string& regex_str
) const noexcept
{
  const boost::xpressive::sregex r
    = boost::xpressive::sregex::compile(regex_str)
  ;

  std::vector<std::string> v;
  boost::xpressive::sregex_iterator cur(s.begin(),s.end(),r);
  boost::xpressive::sregex_iterator end;
  for( ; cur != end; ++cur )
  {
    const boost::xpressive::smatch& what = *cur;
    v.push_back(what[0]);
  }
  return v;
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
  const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& observer
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
    assert(Geometry().IsPlane(points));
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
  for (auto point: points)
  {
    //TRACE(ToStr(point));
    boost::geometry::append(polygon,point);
  };
  assert(boost::geometry::num_points(polygon) == points.size());
  const bool is_convex = IsConvex(polygon);
  return is_convex;
}

bool ribi::Geometry::IsConvex(const std::vector<Coordinat3D>& points) const noexcept
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
  if(!IsPlane(points))
  {
    TRACE("ERROR");
    TRACE(points.size());
    for (auto point: points) { TRACE(Geometry().ToStr(point)); }
    TRACE("BREAK");
  }
  assert(IsPlane(points));
  #endif // NDEBUG
  if (verbose)
  {
    std::stringstream s;
    s << "{";
    for (auto point3d: points)
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
    const boost::shared_ptr<Plane> plane(new Plane(points[v[0]],points[v[1]],points[v[2]]));
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

    const std::vector<boost::geometry::model::d2::point_xy<double>> coordinats2d(
      plane->CalcProjection(points)
    );

    #ifndef NDEBUG
    if (verbose)
    {
      std::stringstream s;
      s << "{";
      for (auto coordinat2d: coordinats2d)
      {

        s << Geometry().ToStr(coordinat2d) << ",";
      }
      std::string co_str(s.str());
      co_str[co_str.size() - 1] = '}';
      TRACE(co_str);
    }
    #endif

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
  const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& observer
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
    
    assert(Geometry().IsPlane(points));
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

bool ribi::Geometry::IsPlane(const std::vector<Coordinat3D>& v) const noexcept
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

#ifndef NDEBUG
void ribi::Geometry::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Geometry::Test");
  const bool verbose = false;
  const double pi { boost::math::constants::pi<double>() };
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;
  const Geometry g;
  if (verbose) { TRACE("CalcPlane"); }
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
  if (verbose) { TRACE("CalcPlane"); }
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
  if (verbose) { TRACE("Fmod"); }
  {
    const double expected_min = 1.0 - 0.00001;
    const double expected_max = 1.0 + 0.00001;
    assert(g.Fmod(3.0,2.0) > expected_min && g.Fmod(3.0,2.0) < expected_max);
    assert(g.Fmod(13.0,2.0) > expected_min && g.Fmod(13.0,2.0) < expected_max);
    assert(g.Fmod(-1.0,2.0) > expected_min && g.Fmod(-1.0,2.0) < expected_max);
    assert(g.Fmod(-3.0,2.0) > expected_min && g.Fmod(-3.0,2.0) < expected_max);
    assert(g.Fmod(-13.0,2.0) > expected_min && g.Fmod(-13.0,2.0) < expected_max);
  }
  if (verbose) { TRACE("GetAngle"); }
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
  if (verbose) { TRACE("GetDistance"); }
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
      const std::vector<Coordinat2D> points {
        { 2.0, 2.0}, //A
        {12.0, 2.0}, //B
        { 9.0, 5.0}, //C
        { 4.0, 5.0}, //D
        { 2.0, 3.0}  //E
      };

      Polygon polygon;
      boost::geometry::append(polygon, points);
      assert(g.IsConvex(polygon));
    }
    //Concave shape
    {
      const std::vector<Coordinat2D> points {
        { 2.0, 2.0}, //A
        {12.0, 2.0}, //B
        { 9.0, 5.0}, //C
        { 7.0, 3.0}, //D
        { 5.0, 5.0}  //E
      };

      Polygon polygon;
      boost::geometry::append(polygon, points);
      assert(!g.IsConvex(polygon));
    }
  }
  if (verbose) TRACE("Convex shape, 2D, from error #1");
  {

    /*

       __--3
     2-
     |
     |
     |
     |  __-0
     1--


    */
    {
      const std::vector<Coordinat2D> points {
        {17.4971,33.0765},
        {9.28854,29.5636},
        {9.28854,40.6764},
        {17.4971,44.4009}
      };
      assert(g.IsConvex(points));
    }
  }
  if (verbose) TRACE("Convex shape, 2D, from error #2");
  {
    //From 3D points:
    /*
    // (2.35114,3.23607,5) (index: 644)'
    // (1.17557,2.35781,5) (index: 658)'
    // (2.35114,3.23607,6) (index: 668)'
    // (1.17557,2.35781,6) (index: 682)'
    */
    /*

       __--2
     3-   /
         /
        /
       /
      / __-0
     1--

    */
    {
      const std::vector<Coordinat2D> points {
        {17.497 ,33.0765},
        { 9.2885,29.5636},
        {17.497 ,44.4009},
        { 9.2885,40.6764}
      };
      assert(!g.IsConvex(points));
    }
  }


  if (verbose) TRACE("Convex shape, 2D, from error #3, point 0");
  {
    /*
        __--2
     1--    |
     |      |
     |      |
     |      |
     |      |
     |      3
     0

    */
    {
      const std::vector<Coordinat2D> points {
        { 9.2885,29.5636},
        { 9.2885,40.6764},
        {17.497 ,44.4009},
        {17.497 ,33.0765}
      };

      assert(g.IsConvex(points));
    }
  }

  if (verbose) TRACE("Convex shape, 2D, from error #3, point 5");
  {
    /*
            3
     0      |
     |      |
     |      |
     |      |
     |      |
     |  __--2
     1--

    */
    {
      const std::vector<Coordinat2D> points {
        { 9.2885,40.6764},
        { 9.2885,29.5636},
        {17.497 ,33.0765},
        {17.497 ,44.4009}
      };

      assert(g.IsConvex(points));
    }
  }

  if (verbose) TRACE("Convex shape, 2D, from error #3, point 5");
  {
    /*

    2-3
    |
    1-0

    */
    {
      const std::vector<Coordinat2D> points {
        {15.9835,631.923},
        {8.24075,628.579},
        {8.24075,679.58 },
        {15.9835,682.926}
      };

      assert(g.IsConvex(points));
    }
  }


  if (verbose) TRACE("Convex shape, 3D, points in Y=0 plane");
  {
    if (verbose) TRACE("Convex shape, 3D, points in Y=0 plane, Z shape");
    {
      /*
                  |####/
        3---2     |###/#
           /      +##+##
          /       |#/###
         /        |/####
        1---0   --+--+--
                 /|
      */
      const std::vector<Coordinat3D> points {
        g.CreatePoint(1.0,0.0,0.0),
        g.CreatePoint(0.0,0.0,0.0),
        g.CreatePoint(1.0,0.0,1.0),
        g.CreatePoint(0.0,0.0,1.0)
      };

      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    if (verbose) TRACE("Convex shape, 3D, points in Y=0 plane, C shape");
    {
      /*

        2---3 Z=1.0
        |
        |
        |
        1---0 Z=0.0

      */
      const std::vector<Coordinat3D> points {
        g.CreatePoint(1.0,0.0,0.0),
        g.CreatePoint(0.0,0.0,0.0),
        g.CreatePoint(0.0,0.0,1.0),
        g.CreatePoint(1.0,0.0,1.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
    }
  }
  if (verbose) TRACE("Convex shape, 3D, points in X=Y plane");
  {
    {
      /*
                  |    |/     _-
                  |  _-2    _-
        3---2     |_- /   _-
           /      3  /  _-
          /       | / _0
         /        |/_-
        1---0   --1-----
                 /|
      */
      const std::vector<Coordinat3D> points {
        g.CreatePoint(1.0,1.0,0.0),
        g.CreatePoint(0.0,0.0,0.0),
        g.CreatePoint(1.0,1.0,1.0),
        g.CreatePoint(0.0,0.0,1.0)
      };
      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    //Convex shape, 3D, points in X=Y plane
    {
      /*

                  |    |/     _-
                  |  _-3    _-
        2---3     |_- /   _-
        |         2  /  _-
        |         | / _0
        |         |/_-
        1---0   --1-----
                 /|

      */
      const std::vector<Coordinat3D> points {
        g.CreatePoint(1.0,1.0,0.0),
        g.CreatePoint(0.0,0.0,0.0),
        g.CreatePoint(0.0,0.0,1.0),
        g.CreatePoint(1.0,1.0,1.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
    }
  }
  if (verbose) TRACE("Convex shape, 3D, points in 2X=Y plane, not at origin");
  {
    {
      const std::vector<Coordinat3D> points {
        g.CreatePoint(2.0,4.0,0.0),
        g.CreatePoint(1.0,1.0,0.0),
        g.CreatePoint(2.0,4.0,1.0),
        g.CreatePoint(1.0,1.0,1.0)
      };
      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    {
      const std::vector<Coordinat3D> points {
        g.CreatePoint(2.0,2.0,0.0),
        g.CreatePoint(1.0,1.0,0.0),
        g.CreatePoint(1.0,1.0,1.0),
        g.CreatePoint(2.0,2.0,1.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
    }
  }
  if (verbose) TRACE("Convex shape, 3D, points in 2X=Y plane, above Z=0");
  {
    {
      const std::vector<Coordinat3D> points {
        g.CreatePoint(2.0,4.0,1.0),
        g.CreatePoint(1.0,1.0,1.0),
        g.CreatePoint(2.0,4.0,2.0),
        g.CreatePoint(1.0,1.0,2.0)
      };
      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    {
      const std::vector<Coordinat3D> points {
        g.CreatePoint(2.0,2.0,1.0),
        g.CreatePoint(1.0,1.0,1.0),
        g.CreatePoint(1.0,1.0,2.0),
        g.CreatePoint(2.0,2.0,2.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
    }
  }
  if (verbose) TRACE("Convex shape, 3D, from error");
  {
    {
      /*

        3---2 Z=6.0
           /
          /
         /
        1---0 Z=5.0

      */
      const std::vector<Coordinat3D> points {
        g.CreatePoint(2.35114,3.23607,5.0),
        g.CreatePoint(1.17557,2.35781,5.0),
        g.CreatePoint(2.35114,3.23607,6.0),
        g.CreatePoint(1.17557,2.35781,6.0)
      };
      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    {
      /*

        2---3 Z=6.0
        |
        |
        |
        1---0 Z=5.0

      */
      const std::vector<Coordinat3D> points {
        g.CreatePoint(2.35114,3.23607,5.0),
        g.CreatePoint(1.17557,2.35781,5.0),
        g.CreatePoint(1.17557,2.35781,6.0),
        g.CreatePoint(2.35114,3.23607,6.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
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
  //IsPlane
  {
    const Coordinat3D a(-3.64472,-0.25,0.0);
    const Coordinat3D b(-4.52988,-0.25,0.0);
    const Coordinat3D c(-3.64472,-0.25,10.0);
    const Coordinat3D d(-4.52988,-0.25,10.0);
    const std::vector<Coordinat3D> v = { a,b,c,d };
    assert(Geometry().IsPlane(v));
  }
  if (verbose) TRACE("Translate");
  {
    //Translate (0.5,1.0) to origin
    const auto house = g.CreateHouseShape();
    const auto translated_house = g.Translate(house,-0.5,-1.0);
    boost::geometry::model::ring<Coordinat2D> translated_points;
    boost::geometry::convert(translated_house,translated_points);
    const std::vector<Coordinat2D> translated_points_expected {
      { 0.0, 1.0}, //0
      { 0.5, 0.0}, //1
      { 0.5,-1.0}, //2
      {-0.5,-1.0}, //3
      {-0.5, 0.0}  //4
    };
    assert(
      std::equal(
        translated_points.begin(),translated_points.end(),
        translated_points_expected.begin(),
        [](const Coordinat2D& a,const Coordinat2D& b)
        {
          return boost::geometry::equals(a,b);
        }
      )
      && "Points must be translated as expected"
    );
  }
  if (verbose) TRACE("Scale up twice, from origin");
  {
    //Scale twice up, from origin
    const auto house = g.CreateHouseShape();
    const auto rescaled_house = g.Rescale(house,2.0);
    boost::geometry::model::ring<Coordinat2D> rescaled_points;
    boost::geometry::convert(rescaled_house,rescaled_points);
    const std::vector<Coordinat2D> rescaled_points_expected {
      {1.0, 4.0}, //0
      {2.0, 2.0}, //1
      {2.0, 0.0}, //2
      {0.0, 0.0}, //3
      {0.0, 2.0}  //4
    };
    assert(
      std::equal(
        rescaled_points.begin(),rescaled_points.end(),
        rescaled_points_expected.begin(),
        [](const Coordinat2D& a,const Coordinat2D& b)
        {
          //std::cout << "(" << a.x() << "," << a.y() << ")-("
          //  << b.x() << "," << b.y() << ")" << std::endl;
          return boost::geometry::equals(a,b);
        }
      )
      && "Points must be rescaled as expected"
    );
  }
  if (verbose) TRACE("Scale up twice, from non-origin");
  {
    //Scale up, from center at (0.5,1.0)
    /*

      3-
       |
      2-    0
       |   / \
      1-  4 * 1
       |  |   |
      0-  3---2
       |
       +--|---|---|
          0   1   2

    */
    const auto house = g.CreateHouseShape();
    const auto rescaled_house = g.Rescale(house,2.0,0.5,1.0);
    boost::geometry::model::ring<Coordinat2D> rescaled_points;
    boost::geometry::convert(rescaled_house,rescaled_points);
    const std::vector<Coordinat2D> rescaled_points_expected {
      { 0.5, 3.0}, //0
      { 1.5, 1.0}, //1
      { 1.5,-1.0}, //2
      {-0.5,-1.0}, //3
      {-0.5, 1.0}  //4
    };
    assert(
      std::equal(
        rescaled_points.begin(),rescaled_points.end(),
        rescaled_points_expected.begin(),
        [](const Coordinat2D& a,const Coordinat2D& b)
        {
          //std::cout << "(" << a.x() << "," << a.y() << ")-("
          //  << b.x() << "," << b.y() << ")" << std::endl;
          return boost::geometry::equals(a,b);
        }
      )
      && "Points must be rescaled as expected"
    );
  }
  if (verbose) { TRACE("GetRegexMatches on GetRegexShapes"); }
  {
    const auto v
      = g.GetRegexMatches(
        "POLYGON((0 0,0 1,1 0)),LINESTRING(0 0,0 1,1 0)",
        g.GetRegexShapes()
    );
    assert(v.size() == 2);
    assert(v[0] == "POLYGON((0 0,0 1,1 0))");
    assert(v[1] == "LINESTRING(0 0,0 1,1 0)");
  }
  if (verbose) { TRACE("WktToSvg"); }
  {
    const std::string s
      = g.WktToSvg("POLYGON((0 0,0 1,1 0)),LINESTRING(0 0,0 1,1 0)",1.0)
    ;
    assert(!s.empty());
  }

  if (verbose) { TRACE("GetLineLineIntersections"); }
  #ifdef TODO_RICHEL
  {
    typedef boost::geometry::model::d2::point_xy<double> Point;
    typedef boost::geometry::model::linestring<Point> Line;
    typedef boost::geometry::model::box<Point> Rect;
    //Assume line segment (0,0)-(2,2) intersects line segment (2,0)-(0,2) at point (1,1)
    {
      const Line line1 = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(2.0,2.0) } ));
      const Line line2 = CreateLine( std::vector<Point>( { Point(2.0,0.0), Point(0.0,2.0) } ));
      assert( GetLineLineIntersections(line1,line2).size() == 1);
      assert( fuzzy_equal_to()(GetLineLineIntersections(line1,line2)[0].x(),1.0) );
      assert( fuzzy_equal_to()(GetLineLineIntersections(line1,line2)[0].y(),1.0) );
    }
    //Lines are finite, however, as the line segment
    //(0,0)-(0.2,0.2) does not intersect line segment (2,0)-(0,2) at point (1,1)
    {
      const Line line1 = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(0.2,0.2) } ));
      const Line line2 = CreateLine( std::vector<Point>( { Point(2.0,0.0), Point(0.0,2.0) } ));
      assert( GetLineLineIntersections(line1,line2).size() == 0);
    }
    //Assume line segment (0,0)-(2,2) intersects with rectangle (1,0)-(3,9) at point (1,1)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(2.0,2.0) } ));
      const Rect rect(Point(1.0,0.0), Point(3.0,3.9));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 1);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
    }
    //Assume line segment (0,0)-(2,2) intersects with rectangle (0,1)-(3,9) at point (1,1)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(2.0,2.0) } ));
      const Rect rect(Point(0.0,1.0), Point(3.0,9.0));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 1);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
    }
    //Assume line segment (0,0)-(2,2) intersects with rectangle (1,1)-(3,3) at point (1,1) once
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(2.0,2.0) } ));
      const Rect rect(Point(1.0,1.0), Point(3.0,3.0));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 1);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
    }

    //Assume line segment (0,0)-(4,4) intersects with rectangle (1,0)-(3,9) at points (1,1) and (3,3)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(4.0,4.0) } ));
      const Rect rect(Point(1.0,0.0), Point(3.0,3.9));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 2);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
      assert( fuzzy_equal_to()(v[1].x(),3.0) );
      assert( fuzzy_equal_to()(v[1].y(),3.0) );
    }
    //Assume line segment (0,0)-(4,4) intersects with rectangle (0,1)-(3,9) at points (1,1) and (3,3)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(4.0,4.0) } ));
      const Rect rect(Point(0.0,1.0), Point(3.0,9.0));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 2);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
      assert( fuzzy_equal_to()(v[1].x(),3.0) );
      assert( fuzzy_equal_to()(v[1].y(),3.0) );
    }
    //Assume line segment (0,0)-(4,4) intersects with rectangle (1,1)-(3,3) at points (1,1) and (3,3)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(4.0,4.0) } ));
      const Rect rect(Point(1.0,1.0), Point(3.0,3.0));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 2);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
      assert( fuzzy_equal_to()(v[1].x(),3.0) );
      assert( fuzzy_equal_to()(v[1].y(),3.0) );
    }
  }
  #endif //#ifdef TODO_RICHEL
  TRACE("Finished ribi::Geometry::Test successfully");
}
#endif

std::string ribi::Geometry::ToStr(const boost::geometry::model::d2::point_xy<double>& p) const noexcept
{
  std::stringstream s;
  s << p;
  return s.str();
  /*
  s
    << "("
    << boost::geometry::get<0>(p)
    << ","
    << boost::geometry::get<1>(p)
    << ")"
  ;
  return s.str();
  */
}

std::string ribi::Geometry::ToStr(const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p) const noexcept
{
  std::stringstream s;
  s << p;
  return s.str();
  /*
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
  */
}

std::string ribi::Geometry::ToStr(
  const boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>& polygon
) const noexcept
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

ribi::Geometry::Shapes ribi::Geometry::WktToShapes(const std::string& wkt) const
{
  std::vector<std::string> v;
  const std::string regex_str = GetRegexShapes();
  for (const auto s: GetRegexMatches(wkt,regex_str))
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
      Polygon polygon;
      boost::geometry::read_wkt(s,polygon);
      polygons.push_back(polygon);
    }
    catch (std::exception&)
    {
      //OK
    }

    try
    {
      Linestring linestring;
      boost::geometry::read_wkt(s,linestring);
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
