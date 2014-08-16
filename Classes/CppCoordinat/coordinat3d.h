//---------------------------------------------------------------------------
/*
Coordinat, coordinat classes
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
//From http://www.richelbilderbeek.nl/CppCoordinat.htm
//---------------------------------------------------------------------------
#ifndef RIBI_COORDINAT3D_H
#define RIBI_COORDINAT3D_H

//typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

#ifdef USE_CUSTOM_RIBI_COORDINAT3D
#include <array>
#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#ifndef _WIN32
#include <boost/geometry/geometries/polygon.hpp>
#endif
#pragma GCC diagnostic pop

namespace ribi {

///An X-Y-Z coordinat
//Note: I dislike to write this class: I wish there was a library (STL, Boost)
//with an alternative.
struct Coordinat3D
{
  explicit Coordinat3D(
    const double x = 0.0,
    const double y = 0.0,
    const double z = 0.0
  ) noexcept;

  explicit Coordinat3D(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p
  ) noexcept
  : Coordinat3D(
    boost::geometry::get<0>(p),
    boost::geometry::get<1>(p),
    boost::geometry::get<2>(p)
  ) {}

  void ChangeX(const double dx) noexcept { m_co[0] += dx; }
  void ChangeY(const double dy) noexcept { m_co[1] += dy; }
  void ChangeZ(const double dz) noexcept { m_co[2] += dz; }

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  double GetX() const noexcept { return m_co[0]; }
  double GetY() const noexcept { return m_co[1]; }
  double GetZ() const noexcept { return m_co[2]; }

  void SetX(const double x) noexcept { m_co[0] = x; }
  void SetY(const double y) noexcept { m_co[1] = y; }
  void SetZ(const double z) noexcept { m_co[2] = z; }

  boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>
    ToBoostGeometryPoint() const noexcept
  {
    return boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>(
      m_co[0],m_co[1],m_co[2]
    );
  }

  Coordinat3D& operator+=(const Coordinat3D& rhs) noexcept;
  Coordinat3D& operator-=(const Coordinat3D& rhs) noexcept;

  Coordinat3D& operator/=(const double f);
  Coordinat3D& operator*=(const double f) noexcept;

  private:
  static const int dimensionality = 3;
  std::array<double,dimensionality> m_co;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const Coordinat3D& lhs, const Coordinat3D& rhs) noexcept;
bool operator<(const Coordinat3D& lhs, const Coordinat3D& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const Coordinat3D& n) noexcept;

Coordinat3D operator-(
  const Coordinat3D& v1,
  const Coordinat3D& v2) noexcept;

Coordinat3D operator+(
  const Coordinat3D& v1,
  const Coordinat3D& v2) noexcept;

///Divide all components of the coordinat by f
Coordinat3D operator/(
  const Coordinat3D& c,
  const double f);

///Multiply all components of the coordinat by f
Coordinat3D operator*(
  const Coordinat3D& c,
  const double f) noexcept;

///Calculate the point in the center of the collection of points
Coordinat3D CalcCenter(const std::vector<Coordinat3D>& points) noexcept;

///Calculate the cross product
Coordinat3D CalcCrossProduct(
  const Coordinat3D& a,
  const Coordinat3D& b
) noexcept;

///Calculate the cross product
double CalcDotProduct(
  const Coordinat3D& a,
  const Coordinat3D& b
) noexcept;

///Calculate the normal of a triangle
///The normal will be (0,0,-1) if a,b and c lie in the XY plane and ordered clockwise (when viewed from above)
///The normal will be (0,0, 1) if a,b and c lie in the XY plane and ordered counter-clockwise (when viewed from above)
///I use this convention as it appears to be used most extensively
Coordinat3D CalcNormal(
  const Coordinat3D& a,
  const Coordinat3D& b,
  const Coordinat3D& c
) noexcept;

///Calculate the distance between two coordinats
double Distance(const Coordinat3D& lhs,const Coordinat3D& rhs) noexcept;

///When viewing a coordinat as a vector from origin, calculate its length
double Length(const Coordinat3D& v) noexcept;

} //~namespace ribi

#endif

#endif // RIBI_COORDINAT3D_H
