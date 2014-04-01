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
#ifndef PLANEZ_H
#define PLANEZ_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/make_shared.hpp>
#ifndef _WIN32
#include <boost/geometry/geometries/polygon.hpp>
#endif
#pragma GCC diagnostic pop

namespace ribi {

///A 3D plane that can have its Z expressed as a function of X and Y.
///Can be constructed from its equation and at least three 3D points
//A plane stores its coefficients in the following form:
// A.x + B.y + C.z = D
//Converting this to z being a function of x and y:
// -C.z =  A  .x + B  .y - D
//    z = -A/C.x - B/C.y + D/C
struct PlaneZ
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  ///Create plane Z = 0.0
  PlaneZ() : PlaneZ(Coordinat3D(0.0,0.0,0.0),Coordinat3D(1.0,0.0,0.0),Coordinat3D(0.0,1.0,0.0))
  {
    #ifndef NDEBUG
    Test();
    #endif
  }

  ///Construct from its coefficients
  explicit PlaneZ(const std::vector<double>& coefficients);

  ///Construct from three points
  explicit PlaneZ(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  ) noexcept : PlaneZ(CalcPlaneZ(p1,p2,p3))
  {
    #ifndef NDEBUG
    Test();
    #endif
  }

  ///Get the 2D projection of these 3D points,
  ///Assumes these are in a plane
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

  ///Throws when cannot calculate Z, which is when the plane is vertical
  double CalcZ(const double x, const double y) const;

  const std::vector<double>& GetCoefficients() const noexcept { return m_coefficients; }

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  ///Convert the NonVerticalPlane to a z(x,y), e.g 'z=(2*x) + (3*y) + 5' (spaces exactly as shown)
  std::string ToFunction() const;

  private:
  ~PlaneZ() noexcept {}

  //m_coefficients.size == 4
  const std::vector<double> m_coefficients;

  static std::vector<double> CalcPlaneZ(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend void boost::checked_delete<>(      PlaneZ*);
  friend void boost::checked_delete<>(const PlaneZ*);
  friend struct std::default_delete<      PlaneZ>;
  friend struct std::default_delete<const PlaneZ>;
  friend class boost::detail::sp_ms_deleter<      PlaneZ>;
  friend class boost::detail::sp_ms_deleter<const PlaneZ>;
};

} //~namespace ribi

#endif // PLANEZ_H
