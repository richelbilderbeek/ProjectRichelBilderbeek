//---------------------------------------------------------------------------
/*
Plane, 3D plane class
Copyright (C) 2013-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppPlane.htm
//---------------------------------------------------------------------------
#ifndef RIBI_PLANE_H
#define RIBI_PLANE_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/shared_ptr.hpp>
#include "planex.h"
#include "planey.h"
#include "planez.h"
#ifndef _WIN32
#include <boost/geometry/geometries/polygon.hpp>
#endif
#pragma GCC diagnostic pop

namespace ribi {

///Any 3D plane, even a single point
///Can be constructed from its equation and at least three 3D points
//A plane stores its coefficients in the following form:
// A.x + B.y + C.z = D
//Converting this to z being a function of x and y:
// -C.z =  A  .x + B  .y - D
//    z = -A/C.x - B/C.y + D/C
struct Plane
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;
  ///Construct a Plane from three points
  /*

   |
   |   /
   +--+
   |\/|
   |/\|
 --+--+---------
  /|
 / |

  */
  ///By default, create the plane Z = 0
  explicit Plane(
    const Coordinat3D& p1, //= Coordinat3D(0.0,0.0,0.0),
    const Coordinat3D& p2, //= Coordinat3D(0.0,1.0,0.0),
    const Coordinat3D& p3  //= Coordinat3D(1.0,0.0,0.0)
  ) noexcept;

  ///Get the 2D projection of these 3D points,
  ///Assumes these are in a Plane
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
  std::vector<boost::geometry::model::d2::point_xy<double>> CalcProjection(
    const std::vector<Coordinat3D>& points
  ) const;

  ///If the Plane can be expressed as X = A*Y + B*Z + C, return the X
  double CalcX(const double y, const double z) const;

  ///If the Plane can be expressed as Y = A*X + B*Z + C, return the Y
  double CalcY(const double x, const double z) const;

  ///If the Plane can be expressed as Z = A*X + B*Y + C, return the Z
  double CalcZ(const double x, const double y) const;

  ///If the Plane can be expressed as X = A*Y + B*Z + C, return the coefficients,
  std::vector<double> GetCoefficientsX() const;

  ///If the Plane can be expressed as Y = A*X + B*Z + C, return the coefficients,
  std::vector<double> GetCoefficientsY() const;

  ///If the Plane can be expressed as Z = A*X + B*Y + C, return the coefficients,
  std::vector<double> GetCoefficientsZ() const;

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  ///Checks if the coordinat is in the plane
  bool IsInPlane(const Coordinat3D& coordinat) const noexcept;

  ///If possible, convert the Plane to a x(y,z), e.g 'x=(2*y) + (3*z) + 5' (spaces exactly as shown)
  std::string ToFunctionX() const;

  ///If possible, convert the Plane to a y(x,z), e.g 'y=(2*x) + (3*z) + 5' (spaces exactly as shown)
  std::string ToFunctionY() const;

  ///If possible, convert the Plane to a z(x,y), e.g 'z=(2*x) + (3*y) + 5' (spaces exactly as shown)
  std::string ToFunctionZ() const;

  private:
  ~Plane() noexcept {}

  ///A non-horizontal plane; a plane that can be expressed as 'X(Y,Z) = A*Y + B*Z + C'
  const boost::shared_ptr<const PlaneX> m_plane_x;

  ///A non-horizontal plane; a plane that can be expressed as 'Y(X,Z) = A*X + B*Z + C'
  const boost::shared_ptr<const PlaneY> m_plane_y;

  ///A non-vertical plane; a plane that can be expressed as 'Z(X,Y) = A*X + B*Y + C'
  const boost::shared_ptr<const PlaneZ> m_plane_z;

  const std::vector<Coordinat3D> m_points;

  static boost::shared_ptr<PlaneX> CreatePlaneX(
    const std::vector<double>& coefficients_x
  ) noexcept;

  static boost::shared_ptr<PlaneY> CreatePlaneY(
    const std::vector<double>& coefficients_y
  ) noexcept;

  static boost::shared_ptr<PlaneZ> CreatePlaneZ(
    const std::vector<double>& coefficients_z
  ) noexcept;

  static boost::shared_ptr<PlaneX> CreatePlaneX(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  ) noexcept;

  static boost::shared_ptr<PlaneY> CreatePlaneY(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  ) noexcept;

  static boost::shared_ptr<PlaneZ> CreatePlaneZ(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend void boost::checked_delete<>(      Plane*);
  friend void boost::checked_delete<>(const Plane*);
  friend struct std::default_delete<      Plane>;
  friend struct std::default_delete<const Plane>;
  friend class boost::detail::sp_ms_deleter<      Plane>;
  friend class boost::detail::sp_ms_deleter<const Plane>;
  friend std::ostream& operator<<(std::ostream& os, const Plane& plane) noexcept;
};

std::ostream& operator<<(std::ostream& os, const Plane& plane) noexcept;

} //~namespace ribi

#endif // RIBI_PLANE_H
