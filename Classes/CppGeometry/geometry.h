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
#ifndef RIBI_GEOMETRY_H
#define RIBI_GEOMETRY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <cassert>
#include <functional>
#include <string>
#include <tuple>
#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#ifndef _WIN32
#include <boost/geometry/geometries/polygon.hpp>
#endif
#pragma GCC diagnostic pop

namespace ribi {

///Goemetry functions, working with Boost.Geometry
struct Geometry
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  typedef boost::geometry::model::linestring<Coordinat2D> Linestring;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;
  typedef boost::geometry::model::box<Coordinat2D> Rect;

  typedef std::vector<Linestring> Linestrings;
  typedef std::vector<Polygon> Polygons;
  typedef std::pair<Polygons,Linestrings> Shapes;

  Geometry();

  Coordinat2D CalcCenter(const std::vector<Coordinat2D>& v) const noexcept;
  Coordinat3D CalcCenter(const std::vector<Coordinat3D>& v) const noexcept;

  Coordinat3D CalcCrossProduct(
    const Coordinat3D& a,
    const Coordinat3D& b
  ) const noexcept;

  double CalcDotProduct(
    const Coordinat3D& a,
    const Coordinat3D& b
  ) const noexcept;

  Coordinat3D CalcNormal(
    const Coordinat3D& a,
    const Coordinat3D& b,
    const Coordinat3D& c
  ) const noexcept;

  ///Determine the plane that goes through these three points
  ///Returns a std::vector of size 4
  ///CalcPlane return the coefficients in the following form:
  /// A.x + B.y + C.z = D
  ///Converting this to z being a function of x and y:
  /// -C.z = A.x + B.y - D
  /// z = -A/C.x - B/C.y + D/C
  std::vector<double> CalcPlane(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  ) const noexcept;

  std::vector<Coordinat2D> CalcProjection(const std::vector<Coordinat3D>& v) const;

  Coordinat2D Coordinat2DToBoostGeometryPointXy(
    const Coordinat2D& c
  ) const noexcept;

  std::vector<Coordinat2D> Coordinats2DToBoostGeometryPointsXy(
    const std::vector<Coordinat2D>& v
  ) const noexcept;

  Coordinat3D CreatePoint(
    const double x,
    const double y,
    const double z
  ) const noexcept;

  Rect CreateRect(
    const double left,
    const double top,
    const double width,
    const double height
  ) const noexcept;

  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
    CreateHouseShape() const noexcept;

  static Polygon CreateShapeHeart(const double scale = 1.0) noexcept;
  static Polygon CreateShapeHouse(const double scale = 1.0) noexcept;
  static Polygon CreateShapePolygon(const int n, const double rotation = 0.0, const double scale = 0.0) noexcept;
  static Polygon CreateShapeTriangle(const double scale = 1.0) noexcept;

  ///Functor for X-Y-Z ordering
  std::function<bool(const ribi::Geometry::Coordinat2D& lhs, const ribi::Geometry::Coordinat2D& rhs)> Equals2d() const noexcept;
  std::function<bool(const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs)> Equals() const noexcept;

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi

  /*
   Y          Y
   |    (11)  |  (1)
 -2|          |
   |          |
 -1| (10)     |      (2)
   |          |
  0+----------0--------X
   |          |
 +1| (8)      |      (4)
   |          |
 +2|          |
   |     (7)  |  (5)
   +----------+--------X
        - - -   + + +
        3 2 1 0 1 2 3

  Approximate coordinat for a point for every hour, with the approximate angle
   1: ( 1,-2) :  1/6 * pi
   2: ( 2,-1) :  2/6 * pi
   3: ( 3, 0) :  3/6 * pi
   4: ( 2, 1) :  4/6 * pi
   5: ( 1, 2) :  5/6 * pi
   6: ( 0, 3) :  6/6 * pi
   7: (-1, 2) :  7/6 * pi
   8: (-2, 1) :  8/6 * pi
   9: (-3, 0) :  9/6 * pi
  10: (-2,-1) : 10/6 * pi
  11: (-1,-2) : 11/6 * pi
  12: ( 0,-3) : 12/6 * pi

  */
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  double GetAngle(const double dx, const double dy) const noexcept;

  double GetAngle(const Coordinat2D& p) const noexcept;

  template <class T>
  T GetBottom(const boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>& r) const noexcept
  {
    using boost::geometry::get;
    using boost::geometry::min_corner;
    using boost::geometry::max_corner;
    const auto bottom(get<max_corner,1>(r));
    #ifndef NDEBUG
    const auto top   (get<min_corner,1>(r));
    assert(top <= bottom);
    #endif
    return bottom;
  }

  //From www.richelbilderbeek.nl/CppGetDistance.htm
  double GetDistance(const double dx, const double dy) const noexcept;
  double GetDistance(const Coordinat2D& a, const Coordinat2D& b) const noexcept;

  template <class T>
  T GetHeight(const boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>& r) const noexcept
  {
    using boost::geometry::get;
    using boost::geometry::min_corner;
    using boost::geometry::max_corner;
    const auto top   (get<min_corner,1>(r));
    const auto bottom(get<max_corner,1>(r));
    assert(top <= bottom);
    return bottom - top;
  }


  template <class T>
  T GetLeft(const boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>& r) const noexcept
  {
    using boost::geometry::get;
    using boost::geometry::min_corner;
    using boost::geometry::max_corner;
    const auto left (get<min_corner,0>(r));
    #ifndef NDEBUG
    const auto right(get<max_corner,0>(r));
    assert(left <= right);
    #endif
    return left;
  }

  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  std::vector<std::string>
    GetRegexMatches(
    const std::string& s,
    const std::string& regex_str
  ) const noexcept;

  std::string GetRegexShapes() const noexcept { return R"((POLYGON\(\(.*?\)\))|(LINESTRING\(.*?\)))"; }

  template <class T>
  T GetRight(const boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>& r) const noexcept
  {
    using boost::geometry::get;
    using boost::geometry::min_corner;
    using boost::geometry::max_corner;
    const auto right(get<max_corner,0>(r));
    #ifndef NDEBUG
    const auto left (get<min_corner,0>(r));
    assert(left <= right);
    #endif
    return right;
  }

  template <class T>
  T GetTop(const boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>& r) const noexcept
  {
    using boost::geometry::get;
    using boost::geometry::min_corner;
    using boost::geometry::max_corner;
    const auto top   (get<min_corner,1>(r));
    #ifndef NDEBUG
    const auto bottom(get<max_corner,1>(r));
    assert(top <= bottom);
    #endif
    return top;
  }

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  template <class T>
  T GetWidth(const boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>& r) const noexcept
  {
    using boost::geometry::get;
    using boost::geometry::min_corner;
    using boost::geometry::max_corner;
    const auto left (get<min_corner,0>(r));
    const auto right(get<max_corner,0>(r));
    assert(left <= right);
    return right - left;
  }
  ///Are two angles ordered clockwise
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  ///
  ///Yes: 0.0 * pi and 0.5 * pi
  ///No : 0.5 * pi and 0.0 * pi
  bool IsClockwise(const double a, const double b) const noexcept;

  ///Are the angles ordered clockwise?
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  ///
  ///Yes: 0.0 * pi and 0.5 * pi
  ///No : 0.5 * pi and 0.0 * pi
  bool IsClockwise(const std::vector<double>& angles) const noexcept;

  ///Are the points ordered clockwise in the XYZ plane, seen from the observer?
  //bool IsClockwise(const std::vector<Coordinat3D>& points, const Coordinat3D& observer) const noexcept;
  bool IsClockwise(const std::vector<Coordinat3D>& points, const Coordinat3D& observer) const noexcept;

  ///Are two angles ordered counter-clockwise
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  ///
  ///Yes: 0.5 * pi and 0.0 * pi
  ///No : 0.0 * pi and 0.5 * pi
  bool IsCounterClockwise(const double a, const double b) const noexcept;

  ///Are the angles ordered counter-clockwise?
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  ///
  ///Yes: 0.5 * pi and 0.0 * pi
  ///No : 0.0 * pi and 0.5 * pi
  bool IsCounterClockwise(const std::vector<double>& angles) const noexcept;

  ///Are the points ordered counterclockwise in the XYZ plane, seen from the observer?
  bool IsCounterClockwise(const std::vector<Coordinat3D>& points, const Coordinat3D& observer) const noexcept;

  ///Are the points ordered clockwise in the XY plane seen from above
  /// (e.g. from coordinat {0,0,1} )
  //bool IsClockwiseHorizontal(const std::vector<Coordinat3D>& points) const noexcept;
  //bool IsClockwiseHorizontal(const std::vector<Coordinat2D>& points) const noexcept;
  bool IsClockwiseHorizontal(const std::vector<Coordinat2D>& v) const noexcept;
  bool IsClockwiseHorizontal(const std::vector<Coordinat3D>& v) const noexcept;


  ///Creates a polygon from the points and checks if the polygon is convex
  /*

   A---------B      A---------B
   E        /        \   D   /
    \      /          \ / \ /
     D----C            E   C

     Convex           Concave

  */
  bool IsConvex(boost::geometry::model::polygon<Coordinat2D> polygon) const noexcept;
  bool IsConvex(const std::vector<Coordinat2D>& points) const noexcept;
  bool IsConvex(const std::vector<Coordinat3D>& points) const noexcept;

  ///Are the points ordered counter-clockwise in the XY plane seen from above
  /// (e.g. from coordinat {0,0,1} )
  //bool IsCounterClockwiseHorizontal(const std::vector<Coordinat3D>& points) const noexcept;
  bool IsCounterClockwiseHorizontal(const std::vector<Coordinat2D>& v) const noexcept;
  bool IsCounterClockwiseHorizontal(const std::vector<Coordinat3D>& v) const noexcept;

  bool IsEqual2d(const ribi::Geometry::Coordinat2D& lhs, const ribi::Geometry::Coordinat2D& rhs) const noexcept { return Equals2d()(lhs,rhs); }
  bool IsEqual(const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs) const noexcept { return Equals()(lhs,rhs); }

  ///Determines if these coordinats are in a plane
  bool IsPlane(const std::vector<Coordinat3D>& v) const noexcept;

  ///Functor for X-Y ordering
  std::function<bool(const ribi::Geometry::Coordinat2D& lhs, const ribi::Geometry::Coordinat2D& rhs)> Order2dByX() const noexcept;

  ///Functor for X-Y-Z ordering
  std::function<bool(const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs)> OrderByX() const noexcept;

  ///Functor for Z-Y-X ordering
  std::function<bool(const ribi::Geometry::Coordinat3D& lhs, const ribi::Geometry::Coordinat3D& rhs)> OrderByZ() const noexcept;

  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
    Rescale(
      const boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>& shape,
      const double scale,
      const double scale_origin_x = 0.0,
      const double scale_origin_y = 0.0
    ) const noexcept;

  std::string ToStr(const Coordinat2D& p) const noexcept;
  std::string ToStr(const Coordinat3D& p) const noexcept;
  std::string ToStr(const Polygon& polygon) const noexcept;

  //Create a complete SVG file contents
  std::string ToSvg(
    const Polygons& polygons,
    const double stroke_width = 1.0
  ) const noexcept;

  std::string ToSvg(
    const Polygons& polygons,
    const Linestrings& linestrings,
    const double stroke_width = 1.0
  ) const noexcept;

  std::string ToSvg(
    const Shapes& shapes,
    const double stroke_width = 1.0
  ) const noexcept { return ToSvg(shapes.first,shapes.second,stroke_width); }

  //Create the line this geometry is in an SVG file
  std::string ToSvgStr(
    const std::vector<Polygon>& polygons,
    const double stroke_width = 1.0
  ) const noexcept;

  std::string ToSvgStr(
    const Polygon& polygon,
    const double stroke_width = 1.0
  ) const noexcept;

  std::string ToSvgStr(
    const Linestrings& linestrings,
    const double stroke_width = 1.0
  ) const noexcept;

  std::string ToSvgStr(
    const Linestring& linestring,
    const double stroke_width = 1.0
  ) const noexcept;

  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
    Translate(
      const boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>& shape,
      const double dx,
      const double dy
    ) const noexcept;


  Shapes WktToShapes(const std::string& wkt) const;
  Shapes WktToShapes(const std::vector<std::string>& wkt) const;
  std::string WktToSvg(const std::string& wkt, const double svg_stroke_width) const;
  std::string WktToSvg(const std::vector<std::string>& wkt, const double svg_stroke_width) const;

  private:
  ///Take the floating point modulus
  double Fmod(const double x, const double mod) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

boost::geometry::model::d2::point_xy<double> operator-(
  const boost::geometry::model::d2::point_xy<double>& a,
  const boost::geometry::model::d2::point_xy<double>& b
) noexcept;

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> operator-(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& a,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& b
) noexcept;

} //~namespace ribi

#endif // RIBI_GEOMETRY_H
