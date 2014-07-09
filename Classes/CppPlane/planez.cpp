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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "planez.h"

#include <cassert>

#include "container.h"
#include "geometry.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::PlaneZ::PlaneZ() noexcept
  : PlaneZ(
    Coordinat3D(0.0,0.0,0.0),
    Coordinat3D(1.0,0.0,0.0),
    Coordinat3D(0.0,1.0,0.0)
  )
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::PlaneZ::PlaneZ(
  const std::vector<apfloat>& coefficients
)
  : m_coefficients(coefficients)
{
  #ifndef NDEBUG
  Test();
  #endif
  const bool verbose = false;
  assert(GetCoefficients().size() == 4);

  //Sometimes due to rounding errors, m_coefficients[2] is not zero,
  //where it should have been. If m_coefficients[2] equals zero,
  //a division by itself is prevented by throwing an exception.
  //Throw an exception as if m_coefficients[2] equalled zero
  //if (std::abs(m_coefficients[2]) < 1.0e-14)
  //if (abs(m_coefficients[2]) < 1.0e-14)
  //Nonsense with abfloats
  //if (abs(m_coefficients[2]) < GetLeastCoefficient())
  if (m_coefficients[2] == 0.0)
  {
    if (verbose) { TRACE(Container().ToStr(m_coefficients)); }
    throw std::logic_error("Plane (from coeffients) that can be expressed in less than 3D space");
  }
}

ribi::PlaneZ::PlaneZ(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
) : PlaneZ(CalcPlaneZ(p1,p2,p3))
{
  #ifndef NDEBUG
  Test();
  #endif
  const bool verbose = false;
  assert(GetCoefficients().size() == 4);
  //Sometimes due to rounding errors, m_coefficients[2] is not zero,
  //where it should have been. If m_coefficients[2] equals zero,
  //a division by itself is prevented by throwing an exception.
  //Throw an exception as if m_coefficients[2] equalled zero
  //if (std::abs(m_coefficients[2]) < 1.0e-14)
  //if (abs(m_coefficients[2]) < GetLeastCoefficient())
  if (m_coefficients[2] == 0.0)
  {
    if (verbose) { TRACE(Container().ToStr(m_coefficients)); }
    throw std::logic_error("Plane (from points) that can be expressed in less than 3D space");
  }
}

ribi::PlaneZ::~PlaneZ() noexcept
{
  //OK
}

apfloat ribi::PlaneZ::CalcMaxErrorAsApfloat(const Coordinat3D& coordinat) const noexcept
{
  const apfloat x = boost::geometry::get<0>(coordinat);
  const apfloat y = boost::geometry::get<1>(coordinat);
  //const apfloat z = boost::geometry::get<2>(coordinat);
  const auto coefficients = GetCoefficients();
  const auto a = coefficients[0];
  const auto b = coefficients[1];
  const auto c = coefficients[2];
  const apfloat e = boost::numeric::bounds<double>::smallest();
  assert(e > 0.0);
  // z = -A/C.x - B/C.y + D/C = (-A.x - B.y + D) / C
  //If C is zero, the slope in X and Y cannot be calculated
  if (c.sign())
  {
    const auto rc_x = -a / c;
    const auto rc_y = -b / c;
    const auto max_error_x = abs(e * rc_x * x) + 0.0;
    const auto max_error_y = abs(e * rc_y * y) + 0.0;
    const auto max_error_z = 0.0;
    const auto max_error = max_error_x + max_error_y + max_error_z;
    return max_error;
  }
  return e;
}

std::vector<apfloat> ribi::PlaneZ::CalcPlaneZ(
  const ribi::PlaneZ::Coordinat3D& p1,
  const ribi::PlaneZ::Coordinat3D& p2,
  const ribi::PlaneZ::Coordinat3D& p3
) noexcept
{
  
  const auto v(
    Geometry().CalcPlane(
      Geometry().ToApfloat(p1),
      Geometry().ToApfloat(p2),
      Geometry().ToApfloat(p3)
    )
  );
  assert(v.size() == 4);
  return v;
}

std::vector<boost::geometry::model::d2::point_xy<double>> ribi::PlaneZ::CalcProjection(
  const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points
) const
{
  assert(points.size() >= 3);
  const double x_origin { 0.0 };
  const double y_origin { 0.0 };
  const double z_origin { CalcZ(x_origin,y_origin) };

  std::vector<boost::geometry::model::d2::point_xy<double>> v;
  for (const auto point: points)
  {
    const auto x(boost::geometry::get<0>(point));
    const auto y(boost::geometry::get<1>(point));
    const auto z(boost::geometry::get<2>(point));
    const double dx {
      std::sqrt(
          ((x - x_origin) * (x - x_origin))
        + ((z - z_origin) * (z - z_origin))
      ) * (x - x_origin)
    };
    const double dy {
      std::sqrt(
          ((y - y_origin) * (y - y_origin))
        + ((z - z_origin) * (z - z_origin))
      ) * (y - y_origin)
    };
    boost::geometry::model::d2::point_xy<double> point_xy(dx,dy);
    v.push_back(point_xy);
  }
  return v;
}

ribi::PlaneZ::Apfloat ribi::PlaneZ::CalcZ(const Apfloat& x, const Apfloat& y) const
{
  // z = -A/C.x - B/C.y + D/C = (-A.x - B.y + D) / C
  const bool verbose = false;
  const auto a = m_coefficients[0];
  const auto b = m_coefficients[1];
  const auto c = m_coefficients[2];
  const auto d = m_coefficients[3];
  if (c == 0.0)
  {
    throw std::logic_error("ribi::PlaneZ::CalcZ: cannot calculate Z of a vertical plane");
  }
  //if (abs(c) < GetLeastCoefficient())
  //{
  //  throw std::logic_error("ribi::PlaneZ::CalcZ: cannot calculate Z of a near-vertical plane");
  //}
  //const apfloat result = ((-a*x) - (b*y) + d) / c;
  const apfloat term1 = -a*x;
  const apfloat term2 = -b*y;
  const apfloat numerator = term1 + term2 + d;
  if (verbose)
  {
    TRACE(numerator);
    TRACE(c);
  }
  const apfloat result = numerator / c;
  return result;
}

double ribi::PlaneZ::CalcZ(const double x, const double y) const
{
  return Geometry().ToDouble(CalcZ(Apfloat(x),Apfloat(y)));
}

apfloat ribi::PlaneZ::GetFunctionAasApfloat() const
{
  const bool verbose = false;
  const auto coeff_a = m_coefficients[0];
  const auto coeff_c = m_coefficients[2];
  static const apfloat zero(0.0);

  if (coeff_c == zero)
  {
    throw std::logic_error("ribi::PlaneZ::GetFunctionA: cannot calculate A of a vertical plane");
  }

  if (verbose)
  {
    TRACE(coeff_c);
  }
  const auto a = -coeff_a/coeff_c;
  return a;
}

double ribi::PlaneZ::GetFunctionA() const
{
  return Geometry().ToDouble(GetFunctionAasApfloat());
}

apfloat ribi::PlaneZ::GetFunctionBasApfloat() const
{
  const auto coeff_b = m_coefficients[1];
  const auto coeff_c = m_coefficients[2];
  static const apfloat zero(0.0);

  if (coeff_c == zero)
  {
    throw std::logic_error("ribi::PlaneZ::GetFunctionB: cannot calculate B of a vertical plane");
  }

  const auto b = -coeff_b/coeff_c;
  return b;
}

double ribi::PlaneZ::GetFunctionB() const
{
  return Geometry().ToDouble(GetFunctionBasApfloat());
}

apfloat ribi::PlaneZ::GetFunctionCasApfloat() const
{
  const auto coeff_c = m_coefficients[2];
  const auto coeff_d = m_coefficients[3];
  static const apfloat zero(0.0);

  if (coeff_c == zero)
  {
    throw std::logic_error("ribi::PlaneZ::GetFunctionC: cannot calculate C of a vertical plane");
  }

  const auto c =  coeff_d/coeff_c;
  return c;
}

double ribi::PlaneZ::GetFunctionC() const
{
  return Geometry().ToDouble(GetFunctionCasApfloat());
}

/*
apfloat ribi::PlaneZ::GetLeastCoefficient() noexcept
{
  const std::string s = "0.000000010000000000000008881e-108";
  char * const cstr = const_cast<char*>(s.c_str()); //apfloat is not const-correct
  const apfloat result(cstr);
  return result;
}
*/

std::string ribi::PlaneZ::GetVersion() const noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::PlaneZ::GetVersionHistory() const noexcept
{
  return {
    "2014-03-10: version 1.0: initial version, split off from Plane",
    "2014-03-10: version 1.1: bug fixed, only occurred at debugging",
    "2014-03-13: version 1.2: bug fixed",
    "2014-04-01: version 1.3: use of std::unique_ptr",
    "2014-07-03: version 1.4: use of apfloat"
  };
}


std::vector<apfloat> ribi::PlaneZ::ToApfloats(const std::vector<double>& v) noexcept
{
  std::vector<apfloat> w;
  for (const auto i: v) { w.push_back(i); }
  return w;
}

std::string ribi::PlaneZ::ToFunction() const
{
  std::stringstream s;
  s << (*this);
  return s.str();
}

std::ostream& ribi::operator<<(std::ostream& os, const PlaneZ& planez)
{
  try
  {
    os
      << "z=("
      << planez.GetFunctionA() << "*x) + ("
      << planez.GetFunctionB() << "*y) + "
      << planez.GetFunctionC()
    ;
  }
  catch (std::logic_error&)
  {
    const std::string error
      = "ribi::PlaneZ::ToFunction: cannot calculate Z of a vertical plane";
    throw std::logic_error(error.c_str());
  }
  return os;
}
