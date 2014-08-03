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
#ifndef RIBI_PLANEX_H
#define RIBI_PLANEX_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/make_shared.hpp>
//#include "planez.h"
#include "apfloat.h"
#pragma GCC diagnostic pop

namespace ribi {

struct PlaneZ;

///A 3D plane that can have its X expressed as a function of Y and Z.
///Can be constructed from its equation and at least three 3D points
///A plane stores its coefficients in the following form:
/// A.z + B.x + C.y = D
///Converting this to x being a function of y and z:
/// -B.x =  A  .z + C  .y - D
///    x = -A/B.z - C/B.y + D/B
///where A,B,C and D can be obtained by GetCoefficients
///Easier is to express X as
///  x = Ay + Bz + C
///where A,B,C can be obtained by GetFunctionA/B/C
struct PlaneX
{
  typedef apfloat Double;
  typedef boost::geometry::model::d2::point_xy<apfloat> Coordinat2D;
  typedef boost::geometry::model::point<apfloat,3,boost::geometry::cs::cartesian> Coordinat3D;
  typedef std::vector<Double> Doubles;
  typedef std::vector<Coordinat2D> Coordinats2D;
  typedef std::vector<Coordinat3D> Coordinats3D;

  ///Create plane X = 0.0
  PlaneX() noexcept;

  ///Construct from three points
  explicit PlaneX(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  );

  Double CalcError(const Coordinat3D& coordinat) const noexcept;

  Double CalcMaxError(const Coordinat3D& coordinat) const noexcept;

  ///Get the 2D projection of these 3D points,
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
  Coordinats2D CalcProjection(const Coordinats3D& points) const;

  ///Throws when cannot calculate X, which is when the plane is horizontal
  Double CalcX(const Double& y, const Double& z) const;

  Doubles GetCoefficients() const noexcept;

  ///x = Ay + Bz + C
  ///Will throw if A cannot be calculated
  Double GetFunctionA() const;

  ///x = Ay + Bz + C
  ///Will throw if B cannot be calculated
  Double GetFunctionB() const;

  ///x = Ay + Bz + C
  ///Will throw if C cannot be calculated
  Double GetFunctionC() const;

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  ///Checks if the coordinat is in the plane
  bool IsInPlane(const Coordinat3D& coordinat) const noexcept;

  private:
  ~PlaneX() noexcept;

  ///A PlaneX is actually a PlaneZ used with its coordinats rotated from (X,Y,Z) to (Z,Y,Y)
  const std::unique_ptr<PlaneZ> m_plane_z;

  ///Calculates m_min_error per GetFunctionC()
  static Double CalcMinErrorPerC() noexcept;

  ///Will throw if plane cannot be created
  static std::unique_ptr<PlaneZ> Create(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  );

  static Doubles Rotate(const Doubles& coefficients) noexcept;

  ///Rotates the X,Y and Z value of a Coordinat
  static Coordinat3D Rotate(const Coordinat3D& point) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///Convert the PlaneX to a x(y,z), e.g 'x=(2*y) + (3*z) + 5' (spaces exactly as shown)
  std::string ToFunction() const;

  friend void boost::checked_delete<>(      PlaneX*);
  friend void boost::checked_delete<>(const PlaneX*);
  friend struct std::default_delete<      PlaneX>;
  friend struct std::default_delete<const PlaneX>;
  friend class boost::detail::sp_ms_deleter<      PlaneX>;
  friend class boost::detail::sp_ms_deleter<const PlaneX>;
  friend std::ostream& operator<<(std::ostream& os,const PlaneX& planex);
};

std::ostream& operator<<(std::ostream& os,const PlaneX& planex);

} //~namespace ribi

#endif // RIBI_PLANEX_H
