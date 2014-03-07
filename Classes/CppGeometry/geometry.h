#ifndef RIBI_GEOMETRY_H
#define RIBI_GEOMETRY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
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

struct Coordinat2D;
struct Coordinat3D;

struct Geometry
{
  Geometry();

  boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> CalcCrossProduct(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& a,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& b
  ) const noexcept;

  ///Determine the plane that goes through these three points
  ///Returns a std::vector of size 4
  ///CalcPlane return the coefficients in the following form:
  /// A.x + B.y + C.z = D
  ///Converting this to z being a function of x and y:
  /// -C.z = A.x + B.y - D
  /// z = -A/C.x - B/C.y + D/C
  std::vector<double> CalcPlane(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
  ) const noexcept;

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

  Appriximate coordinat for a point for every hour, with the approximate angle
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

  //From www.richelbilderbeek.nl/CppGetDistance.htm
  double GetDistance(const double dx, const double dy) const noexcept;

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

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
  bool IsClockwise(const std::vector<Coordinat3D>& points, const Coordinat3D& observer) const noexcept;

  ///Are the points ordered clockwise in the XY plane seen from above
  /// (e.g. from coordinat {0,0,1} )
  bool IsClockwiseHorizontal(const std::vector<Coordinat3D>& points) const noexcept;
  bool IsClockwiseHorizontal(const std::vector<Coordinat2D>& points) const noexcept;


  ///Creates a polygon from the points and checks if the polygon is convex
  /*

   A---------B      A---------B
   E        /        \   D   /
    \      /          \ / \ /
     D----C            E   C

     Convex           Concave

  */
  bool IsConvex(boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon) const noexcept;
  bool IsConvex(const std::vector<Coordinat3D>& points) const noexcept;

  private:
  ///Take the floating point modulus
  double Fmod(const double x, const double mod) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>
  operator-(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& a,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& b
  ) noexcept;

} //~namespace ribi

#endif // RIBI_GEOMETRY_H
