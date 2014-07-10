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
  const Doubles& coefficients
)
  : m_coefficients(coefficients)
{
  #ifndef NDEBUG
  Test();
  #endif
  const bool verbose = false;
  assert(GetCoefficients().size() == 4);

  if (m_coefficients[2] == 0.0)
  {
    if (verbose) { TRACE(Container().ToStr(m_coefficients)); }
    throw std::logic_error("PlaneZ (from coeffients) cannot be expressed in less than 3D space");
  }

  try
  {
    TRACE(GetFunctionA());
    TRACE(GetFunctionB());
    TRACE(GetFunctionC());
    assert(GetFunctionA() == 0.0 || GetFunctionA() != 0.0);
    assert(GetFunctionB() == 0.0 || GetFunctionB() != 0.0);
    assert(GetFunctionC() == 0.0 || GetFunctionC() != 0.0);
  }
  catch (...)
  {
    assert(!"Should not get here");
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

apfloat ribi::PlaneZ::CalcErrorAsApfloat(const Coordinat3D& coordinat) const noexcept
{
  const apfloat x = boost::geometry::get<0>(coordinat);
  const apfloat y = boost::geometry::get<1>(coordinat);
  const apfloat z = boost::geometry::get<2>(coordinat);
  const auto expected = z;
  const auto calculated = CalcZ(x,y);
  const auto error = abs(calculated - expected);
  return error;
}

apfloat ribi::PlaneZ::CalcMaxError(const Coordinat3D& coordinat) const noexcept
{
  const bool verbose = false;
  const apfloat x = boost::geometry::get<0>(coordinat);
  const apfloat y = boost::geometry::get<1>(coordinat);
  //const apfloat z = boost::geometry::get<2>(coordinat);
  const auto coefficients = GetCoefficients();
  const auto a = coefficients[0];
  const auto b = coefficients[1];
  const auto c = coefficients[2];
  const apfloat e = boost::numeric::bounds<double>::smallest();
  assert(e > 0.0);

  if (verbose)
  {
    TRACE(Geometry().ToStr(coordinat));
    TRACE(x);
    TRACE(y);
    TRACE(a);
    TRACE(b);
    TRACE(c);
  }

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

    if (verbose)
    {
      TRACE(rc_x);
      TRACE(rc_y);
      TRACE(max_error_x);
      TRACE(max_error_y);
      TRACE(max_error);
    }
    return max_error;
  }
  return e;
}

std::vector<apfloat> ribi::PlaneZ::CalcPlaneZ(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
) noexcept
{
  
  const auto v(
    Geometry().CalcPlane(
      p1,
      p2,
      p3
    )
  );
  assert(v.size() == 4);
  return v;
}

ribi::PlaneZ::Coordinats2D ribi::PlaneZ::CalcProjection(
  const Coordinats3D& points
) const
{
  assert(points.size() >= 3);
  const apfloat x_origin = 0.0;
  const apfloat y_origin = 0.0;
  const apfloat z_origin = CalcZ(x_origin,y_origin);

  Coordinats2D v;
  for (const auto point: points)
  {
    const Double x(boost::geometry::get<0>(point));
    const Double y(boost::geometry::get<1>(point));
    const Double z(boost::geometry::get<2>(point));
    const Double dx =
      sqrt( //Apfloat does not add the std::
          ((x - x_origin) * (x - x_origin))
        + ((z - z_origin) * (z - z_origin))
      ) * (x - x_origin)
    ;
    const Double dy =
      sqrt( //Apfloat does not add the std::
          ((y - y_origin) * (y - y_origin))
        + ((z - z_origin) * (z - z_origin))
      ) * (y - y_origin)
    ;

    Coordinat2D point_xy(dx,dy);
    v.push_back(point_xy);
  }
  return v;
}

ribi::PlaneZ::Double ribi::PlaneZ::CalcZ(const Double& x, const Double& y) const
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

apfloat ribi::PlaneZ::GetFunctionA() const
{
  const bool verbose = false;
  const auto coeff_a = m_coefficients[0];
  const auto coeff_c = m_coefficients[2];
  static const apfloat zero(0.0);
  assert(coeff_c != zero);
  if (verbose)
  {
    TRACE(coeff_c);
  }
  const auto a = -coeff_a/coeff_c;
  return a;
}

apfloat ribi::PlaneZ::GetFunctionB() const
{
  const auto coeff_b = m_coefficients[1];
  const auto coeff_c = m_coefficients[2];
  static const apfloat zero(0.0);
  assert(coeff_c != zero);
  const auto b = -coeff_b/coeff_c;
  return b;
}

apfloat ribi::PlaneZ::GetFunctionC() const
{
  const auto coeff_c = m_coefficients[2];
  const auto coeff_d = m_coefficients[3];
  static const apfloat zero(0.0);
  assert(coeff_c != zero);

  try
  {
    const auto c = coeff_d/coeff_c;
    return c;
  }
  catch (...)
  {
    assert(!"Should not get here");
    throw;
  }
}

std::vector<double> ribi::PlaneZ::GetTestSeries() noexcept
{
  return
  {
     1.0,
    -1.0,
     std::numeric_limits<double>::epsilon(),
    -std::numeric_limits<double>::epsilon(),
     1.e8,
    -1.e8,
    0.0,
     std::numeric_limits<double>::denorm_min(),
    -std::numeric_limits<double>::denorm_min(),
     1.e64,
    -1.e64,
    std::numeric_limits<double>::min(),
    std::numeric_limits<double>::max()
  };
}

std::string ribi::PlaneZ::GetVersion() const noexcept
{
  return "1.6";
}

std::vector<std::string> ribi::PlaneZ::GetVersionHistory() const noexcept
{
  return {
    "2014-03-10: version 1.0: initial version, split off from Plane",
    "2014-03-10: version 1.1: bug fixed, only occurred at debugging",
    "2014-03-13: version 1.2: bug fixed",
    "2014-04-01: version 1.3: use of std::unique_ptr",
    "2014-07-03: version 1.4: use of apfloat",
    "2014-07-09: version 1.5: use double in interface only"
    "2014-07-10: version 1.6: use of apfloat only"
  };
}

bool ribi::PlaneZ::IsInPlane(const Coordinat3D& coordinat) const noexcept
{
  try
  {
    const apfloat error = CalcErrorAsApfloat(coordinat);
    const apfloat max_error = CalcMaxError(coordinat); //std::numeric_limits<double>::epsilon();
    return error <= max_error;
  }
  catch (std::exception& e)
  {
    TRACE("ERROR");
    TRACE(e.what())
    assert(!"Should not get here");
    throw;
  }
}

/*
std::vector<apfloat> ribi::PlaneZ::ToApfloats(const std::vector<double>& v) noexcept
{
  std::vector<apfloat> w;
  for (const auto i: v) { w.push_back(i); }
  return w;
}
*/

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
