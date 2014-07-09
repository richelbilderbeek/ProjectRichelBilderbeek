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
#ifndef RIBI_PLANEY_H
#define RIBI_PLANEY_H

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
///Converting this to y being a function of x and z:
/// -C.y =  A  .z + B  .x - D
///    y = -A/C.z - B/C.x + D/C
///Where A,B,C and D can be obtained by using GetCoefficients
///Easier might be to express Y as:
///y = Ax + Bz + C
///Where A,B and C can be obtained by using GetFunctionA/B/C

struct PlaneY
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::d2::point_xy<apfloat> ApCoordinat2D;
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;
  typedef boost::geometry::model::point<apfloat,3,boost::geometry::cs::cartesian> ApCoordinat3D;
  typedef std::vector<Coordinat2D> Coordinats2D;
  typedef std::vector<Coordinat3D> Coordinats3D;
  typedef std::vector<ApCoordinat2D> ApCoordinats2D;
  typedef std::vector<ApCoordinat3D> ApCoordinats3D;
  typedef apfloat Apfloat;
  typedef std::vector<Apfloat> Apfloats;

  ///Create plane Y = 0.0
  PlaneY() noexcept;

  ///Construct from three points
  PlaneY(
    const ApCoordinat3D& p1,
    const ApCoordinat3D& p2,
    const ApCoordinat3D& p3
  );

  apfloat CalcErrorAsApfloat(const ApCoordinat3D& coordinat) const noexcept;

  apfloat CalcMaxErrorAsApfloat(const ApCoordinat3D& coordinat) const noexcept;

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
  ApCoordinats2D CalcProjection(
    const ApCoordinats3D& points
  ) const;

  ///Throws when cannot calculate Y, which is when the plane is horizontal
  //double CalcY(const double y, const double z) const;
  Apfloat CalcY(const Apfloat& y, const Apfloat& z) const;

  ///y = Ax + Bz + C
  ///Will throw if A cannot be calculated
  Apfloat GetFunctionA() const;

  ///y = Ax + Bz + C
  ///Will throw if B cannot be calculated
  Apfloat GetFunctionB() const;

  ///y = Ax + Bz + C
  ///Will throw if C cannot be calculated
  Apfloat GetFunctionC() const;

  Apfloats GetCoefficients() const noexcept;

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  ///Checks if the coordinat is in the plane
  bool IsInPlane(const ApCoordinat3D& coordinat) const noexcept;

  private:
  ~PlaneY() noexcept;

  ///A PlaneY is actually a PlaneZ used with its coordinats rotated from (X,Y,Z) to (Z,Y,Y)
  const std::unique_ptr<PlaneZ> m_plane_z;

  static std::unique_ptr<PlaneZ> Create(
    const ApCoordinat3D& p1,
    const ApCoordinat3D& p2,
    const ApCoordinat3D& p3
  );

  static Apfloats Rotate(const Apfloats& coefficients) noexcept;

  static ApCoordinat3D Rotate(
    const ApCoordinat3D& point
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///Convert the PlaneY to a y(x,z), e.g 'y=(2*x) + (3*z) + 5' (spaces exactly as shown)
  std::string ToFunction() const;

  friend void boost::checked_delete<>(      PlaneY*);
  friend void boost::checked_delete<>(const PlaneY*);
  friend struct std::default_delete<      PlaneY>;
  friend struct std::default_delete<const PlaneY>;
  friend class boost::detail::sp_ms_deleter<      PlaneY>;
  friend class boost::detail::sp_ms_deleter<const PlaneY>;
  friend std::ostream& operator<<(std::ostream& os,const PlaneY& planey);
};

std::ostream& operator<<(std::ostream& os,const PlaneY& planey);

} //~namespace ribi

#endif // RIBI_PLANEY_H
