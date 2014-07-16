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
#include "plane.h"

#include <cassert>

#include "container.h"
#include "geometry.h"
#include "planex.h"
#include "planey.h"
#include "planez.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::Plane::Plane(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
) noexcept
: m_plane_x(CreatePlaneX(p1,p2,p3)),
  m_plane_y(CreatePlaneY(p1,p2,p3)),
  m_plane_z(CreatePlaneZ(p1,p2,p3)),
  m_points( {p1,p2,p3} )
{
  #ifndef NDEBUG
  Test();
  
  assert(Geometry().IsEqual3d(m_points[0],p1));
  assert(Geometry().IsEqual3d(m_points[1],p2));
  assert(Geometry().IsEqual3d(m_points[2],p3));
  #endif

  if (m_plane_z)
  {
    try
    {
      m_plane_z->GetFunctionA();
      m_plane_z->GetFunctionB();
      m_plane_z->GetFunctionC();
    }
    catch (...)
    {
      assert(!"Should not get here");
    }
  }

}

apfloat ribi::Plane::CalcError(const Coordinat3D& coordinat) const noexcept
{
  const bool verbose = false;
  const apfloat x = boost::geometry::get<0>(coordinat);
  const apfloat y = boost::geometry::get<1>(coordinat);
  const apfloat z = boost::geometry::get<2>(coordinat);

  apfloat min_error = std::numeric_limits<double>::max();

  if (verbose)
  {
    std::stringstream s;
    s << std::setprecision(99) << (*this);
    TRACE(s.str());
    if (CanCalcX()) { TRACE(Container().ToStr(GetCoefficientsX())); }
    if (CanCalcY()) { TRACE(Container().ToStr(GetCoefficientsY())); }
    if (CanCalcZ()) { TRACE(Container().ToStr(GetCoefficientsZ())); }
  }

  //Absolute method
  if (CanCalcX())
  {
    const auto expected = x;
    const apfloat calculated = CalcX(y,z);
    const apfloat error = abs(calculated - expected);
    min_error = std::min(error,min_error);
  }
  if (CanCalcY())
  {
    const auto expected = y;
    const auto calculated = CalcY(x,z);
    const auto error = abs(calculated - expected);
    min_error = std::min(error,min_error);
  }
  if (CanCalcZ())
  {
    const auto expected = z;
    const auto calculated = CalcZ(x,y);
    const auto error = abs(calculated - expected);
    min_error = std::min(error,min_error);
  }
  assert(min_error >= 0.0);
  return min_error;
}

apfloat ribi::Plane::CalcMaxError(const Coordinat3D& coordinat) const noexcept
{
  apfloat max_error{std::numeric_limits<double>::denorm_min()};
  if (CanCalcX())
  {
    max_error = std::max(max_error,m_plane_x->CalcMaxError(coordinat));
  }
  if (CanCalcY())
  {
    max_error = std::max(max_error,m_plane_y->CalcMaxError(coordinat));
  }
  if (CanCalcZ())
  {
    max_error = std::max(max_error,m_plane_z->CalcMaxError(coordinat));
  }
  return max_error;
}


ribi::Plane::Coordinats2D ribi::Plane::CalcProjection(
  const Coordinats3D& points
) const
{
  if (!m_plane_x && !m_plane_y && !m_plane_z)
  {
    throw std::logic_error("Plane::CalcProjection: cannot express any plane");
  }
  try { if (m_plane_x) { return m_plane_x->CalcProjection(points); }}
  catch (std::logic_error&) { /* OK, try next plane */ }

  try { if (m_plane_y) { return m_plane_y->CalcProjection(points); }}
  catch (std::logic_error&) { /* OK, try next plane */ }

  try { if (m_plane_z) { return m_plane_z->CalcProjection(points); }}
  catch (std::logic_error&) { /* OK, try next plane */ }

  TRACE("ERROR");
  TRACE("INITIAL POINTS");
  for (const auto& point: m_points)
  {
    std::stringstream s;
    s
      << "("
      << boost::geometry::get<0>(point) << ","
      << boost::geometry::get<1>(point) << ","
      << boost::geometry::get<2>(point)
      << ")"
    ;
    TRACE(s.str());
  }

  TRACE(points.size());
  {
    if (m_plane_x)
    {
      try { TRACE(*m_plane_x); } catch(std::logic_error&) { TRACE("Failed m_plane_x"); }
      try { m_plane_x->CalcProjection(points); } catch (std::logic_error&) { TRACE("Failed m_plane_x->CalcProjection"); }
    }
  }
  {
    if (m_plane_y)
    {
      try { TRACE(*m_plane_y); } catch(std::logic_error&) { TRACE("Failed m_plane_y"); }
      try { m_plane_y->CalcProjection(points); } catch (std::logic_error&) { TRACE("Failed m_plane_y->CalcProjection"); }
    }
  }
  {
    if (m_plane_z)
    {
      try { TRACE(*m_plane_z); } catch(std::logic_error&) { TRACE("Failed m_plane_z"); }
      try { m_plane_z->CalcProjection(points); } catch (std::logic_error&) { TRACE("Failed m_plane_z->CalcProjection"); }
    }
  }
  for (const auto& point: points)
  {
    std::stringstream s;
    s
      << "("
      << boost::geometry::get<0>(point) << ","
      << boost::geometry::get<1>(point) << ","
      << boost::geometry::get<2>(point)
      << ")"
    ;
    TRACE(s.str());
  }
  assert(!"Should not get here");
  throw std::logic_error("Plane::CalcProjection: unexpected behavior");
}

ribi::Plane::Double ribi::Plane::CalcX(const Double& y, const Double& z) const
{
  if (!CanCalcX())
  {
    throw std::logic_error("Plane::CalcX: cannot express the plane as 'X = A*Y + B*Z + C'");
  }
  return m_plane_x->CalcX(y,z);
}

ribi::Plane::Double ribi::Plane::CalcY(const ribi::Plane::Double& x, const ribi::Plane::Double& z) const
{
  if (!CanCalcY())
  {
    throw std::logic_error("Plane::CalcY: cannot express the plane as 'Y = A*X + B*Y + C'");
  }
  return m_plane_y->CalcY(x,z);
}

ribi::Plane::Double ribi::Plane::CalcZ(const ribi::Plane::Double& x, const ribi::Plane::Double& y) const
{
  if (!CanCalcZ())
  {
    throw std::logic_error("Plane::CalcZ: cannot express the plane as 'Z = A*X + B*Y + C'");
  }
  return m_plane_z->CalcZ(x,y);
}

bool ribi::Plane::CanCalcX() const noexcept
{
  return m_plane_x.get();
}
bool ribi::Plane::CanCalcY() const noexcept
{
  return m_plane_y.get();
}

bool ribi::Plane::CanCalcZ() const noexcept
{
  return m_plane_z.get();
}

boost::shared_ptr<ribi::PlaneX> ribi::Plane::CreatePlaneX(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
) noexcept
{
  const bool verbose = false;
  try
  {
    const boost::shared_ptr<PlaneX> p(
      boost::make_shared<PlaneX>(p1,p2,p3)
    );
    assert(p);
    return p;
  }
  catch (std::exception& e)
  {
    if (verbose) { TRACE(e.what()); }
    return boost::shared_ptr<PlaneX>();
  }
}

boost::shared_ptr<ribi::PlaneY> ribi::Plane::CreatePlaneY(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
) noexcept
{
  try
  {
    const boost::shared_ptr<PlaneY> p
      = boost::make_shared<PlaneY>(p1,p2,p3);
    assert(p);
    return p;
  }
  catch (std::exception&)
  {
    return boost::shared_ptr<PlaneY>();
  }
}

boost::shared_ptr<ribi::PlaneZ> ribi::Plane::CreatePlaneZ(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
) noexcept
{
  try
  {
    const boost::shared_ptr<PlaneZ> p
      = boost::make_shared<PlaneZ>(p1,p2,p3);
    assert(p);
    return p;
  }
  catch (std::exception&)
  {
    return boost::shared_ptr<PlaneZ>();
  }
}

std::vector<apfloat> ribi::Plane::GetCoefficientsX() const
{
  if (!m_plane_x)
  {
    throw std::logic_error("Plane::GetCoefficientsX: cannot express the plane as 'X = A*Y + B*Z + C'");
  }
  return m_plane_x->GetCoefficients();
}

std::vector<apfloat> ribi::Plane::GetCoefficientsY() const
{
  if (!m_plane_y)
  {
    throw std::logic_error("Plane::GetCoefficientsY: cannot express the plane as 'Y = A*X + B*Z + C'");
  }
  return m_plane_y->GetCoefficients();
}

std::vector<apfloat> ribi::Plane::GetCoefficientsZ() const
{
  if (!m_plane_z)
  {
    throw std::logic_error("Plane::GetCoefficientsZ: cannot express the plane as 'Z = A*X + B*Y + C'");
  }
  return m_plane_z->GetCoefficients();
}


std::string ribi::Plane::GetVersion() noexcept
{
  return "1.7";
}

std::vector<std::string> ribi::Plane::GetVersionHistory() noexcept
{
  return {
    "2014-03-07: version 1.0: initial version",
    "2014-03-10: version 1.1: allow vertical planes",
    "2014-03-13: version 1.2: bug fixed",
    "2014-04-01: version 1.3: use of std::unique_ptr",
    "2014-06-13: version 1.4: added operator<<, ToStr calls operator<<, shortened time to compile",
    "2014-06-16: version 1.5: improved detection of planes that can be expressed in less than three dimensions"
    "2014-07-03: version 1.6: use of apfloat, improved accuracy",
    "2014-07-10: version 1.7: use of apfloat only",
    "2014-07-15: version 1.8: multiple bugfixes"
  };
}

bool ribi::Plane::IsInPlane(const Coordinat3D& coordinat) const noexcept
{
  assert(m_plane_x || m_plane_y || m_plane_z);
  return
       (m_plane_x && m_plane_x->IsInPlane(coordinat))
    || (m_plane_y && m_plane_y->IsInPlane(coordinat))
    || (m_plane_z && m_plane_z->IsInPlane(coordinat))
  ;
}

std::ostream& ribi::operator<<(std::ostream& os, const Plane& plane) noexcept
{
  os << '(';
  const auto n_points = static_cast<int>(plane.m_points.size());
  for (/* const */ auto i=0; i!=n_points; ++i)
  {
    os << Geometry().ToStr(plane.m_points[i]);
    os << (i != n_points - 1 ? ',' : ')');
  }
  os << ',';
  if (plane.m_plane_x)
  {
    try { os << (*plane.m_plane_x); }
    catch (std::exception&) { os << "divnull"; }
  }
  else
  {
    os << "null";
  }
  os << ',';
  if (plane.m_plane_y)
  {
    try { os << (*plane.m_plane_y); }
    catch (std::exception&) { os << "divnull"; }
  }
  else
  {
    os << "null";
  }
  os << ',';
  if (plane.m_plane_z)
  {
    try { os << (*plane.m_plane_z); }
    catch (std::exception&) { os << "divnull"; }
  }
  else
  {
    os << "null";
  }
  return os;
}
