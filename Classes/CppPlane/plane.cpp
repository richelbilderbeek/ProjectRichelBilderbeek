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
  const ApCoordinat3D& p1,
  const ApCoordinat3D& p2,
  const ApCoordinat3D& p3
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
      m_plane_z->GetFunctionAasApfloat();
      m_plane_z->GetFunctionBasApfloat();
      m_plane_z->GetFunctionCasApfloat();
    }
    catch (...)
    {
      assert(!"Should not get here");
    }
  }

}

/*
double ribi::Plane::CalcError(const Coordinat3D& coordinat) const noexcept
{
  return Geometry().ToDouble(CalcErrorAsApfloat(coordinat));
}
*/

apfloat ribi::Plane::CalcErrorAsApfloat(const ApCoordinat3D& coordinat) const noexcept
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


  #ifdef IMPROVE_ACCURACY_224
  const apfloat max_error = 0.00000001; //One millionth
  try
  {
    const auto expected = x;
    if (verbose) { TRACE(expected); }
    const apfloat calculated = CalcX(y,z);
    if (verbose) { TRACE(calculated); }
    if (expected == 0.0 || calculated == 0.0) throw std::logic_error("Cannot use a fractional error for values of zero");
    const apfloat error = abs(apfloat(1.0) - abs(calculated / expected));
    if (verbose) { TRACE(error); }
    const bool is_in_plane = error <= max_error;
    if (verbose) { TRACE(is_in_plane); }
    return is_in_plane;
  }
  catch (std::logic_error& e)
  {
    // OK
    if (verbose) { TRACE(e.what()); }
  }
  try
  {
    const auto expected = y;
    if (verbose) { TRACE(expected); }
    const auto calculated = CalcY(x,z);
    if (verbose) { TRACE(calculated); }
    if (expected == 0.0 || calculated == 0.0) throw std::logic_error("Cannot use a fractional error for values of zero");
    const apfloat error = abs(apfloat(1.0) - abs(calculated / expected));
    if (verbose) { TRACE(error); }
    const bool is_in_plane = error <= max_error;
    if (verbose) { TRACE(is_in_plane); }
    return is_in_plane;
  }
  catch (std::logic_error& e)
  {
    // OK
    if (verbose) { TRACE(e.what()); }
  }
  try
  {
    const auto expected = z;
    if (verbose) { TRACE(expected); }
    const auto calculated = CalcZ(x,y);
    if (verbose) { TRACE(calculated); }
    if (expected == 0.0 || calculated == 0.0) throw std::logic_error("Cannot use a fractional error for values of zero");
    const apfloat error = abs(apfloat(1.0) - abs(calculated / expected));
    if (verbose) { TRACE(error); }
    const bool is_in_plane = error <= max_error;
    if (verbose) { TRACE(is_in_plane); }
    return is_in_plane;
  }
  catch (std::logic_error& e)
  {
    // OK
    if (verbose) { TRACE(e.what()); }
  }
  #endif // IMPROVE_ACCURACY_224

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
    TRACE(expected);
    const auto calculated = CalcZ(x,y);
    TRACE(calculated);
    const auto error = abs(calculated - expected);
    TRACE(error);
    min_error = std::min(error,min_error);

    #ifdef IMPROVE_ACCURACY_224
    //If the Plane can be expressed as Z = A*X + B*Y + C, return the Z
    // z = -A/C.x - B/C.y + D/C = (-A.x - B.y + D) / C
    const auto a = GetCoefficientsZ()[0];
    const auto b = GetCoefficientsZ()[1];
    const auto c = GetCoefficientsZ()[2];
    const auto d = GetCoefficientsZ()[3];
    // z = -A/C.x - B/C.y + D/C = (-A.x - B.y + D) / C
    TRACE(c.sign());
    if (c.sign())
    {
      std::stringstream s;
      s << std::fixed << std::setprecision(99) << a << ' ' << b << ' ' << c;
      TRACE(s.str());
      //TRACE(b);
      //TRACE(c);
      const auto rc_x = -a / c;
      TRACE(rc_x);
      const auto rc_y = -b / c;
      TRACE(rc_y);
      const auto rc = sqrt( (rc_x * rc_x) + (rc_y * rc_y));
      const apfloat e = boost::numeric::bounds<double>::smallest();
      const auto new_max_error = e * rc;
      TRACE(rc_x);
      TRACE(rc_y);
      TRACE(rc);
      TRACE(new_max_error);
      TRACE(new_max_error);
    }
    if (verbose)
    {
      TRACE(b);
      TRACE(d);
      TRACE(calculated);
    }

    //Error
    // = the rounding off error
    // * SQRT(
    //     ((coefficient of direction Y) ^ 2)
    //   + ((coefficient of direction Z) ^ 2)
    // )

    //const double max_error
    //  = m_plane_?->GetFunction?() * boost::numeric::bounds<double>::smallest();
    #endif
  }
  return min_error;
}

/*
double ribi::Plane::CalcMaxError(const Coordinat3D& coordinat) const noexcept
{
  return Geometry().ToDouble(CalcMaxErrorAsApfloat(coordinat));
}
*/

apfloat ribi::Plane::CalcMaxErrorAsApfloat(const ApCoordinat3D& coordinat) const noexcept
{
  apfloat max_error = 0.0;
  if (CanCalcX())
  {
    max_error = std::max(max_error,m_plane_x->CalcMaxErrorAsApfloat(coordinat));
  }
  if (CanCalcY())
  {
    max_error = std::max(max_error,m_plane_y->CalcMaxErrorAsApfloat(coordinat));
  }
  if (CanCalcZ())
  {
    max_error = std::max(max_error,m_plane_z->CalcMaxErrorAsApfloat(coordinat));
  }
  return max_error;
  /*
  //If the Plane can be expressed as Z = A*X + B*Y + C, return the Z
  // z = -A/C.x - B/C.y + D/C = (-A.x - B.y + D) / C
  const auto f_x = std::make_tuple(&ribi::Plane::CanCalcX,&ribi::Plane::GetCoefficientsX);
  const auto f_y = std::make_tuple(&ribi::Plane::CanCalcY,&ribi::Plane::GetCoefficientsY);
  const auto f_z = std::make_tuple(&ribi::Plane::CanCalcZ,&ribi::Plane::GetCoefficientsZ);
  const auto fs = { f_x, f_y, f_z };
  for (const auto f: fs)
  {
    if (std::bind(std::get<0>(f),this)())
    {
      const auto a = std::bind(std::get<1>(f),this)()[0];
      const auto b = std::bind(std::get<1>(f),this)()[1];
      const auto c = std::bind(std::get<1>(f),this)()[2];
      //const auto d = GetCoefficientsZ()[3];
      const apfloat e = boost::numeric::bounds<double>::smallest();
      assert(e > 0.0);
      // z = -A/C.x - B/C.y + D/C = (-A.x - B.y + D) / C
      //TRACE(c.sign());
      if (c.sign())
      {
        const auto rc_x = -a / c;
        const auto rc_y = -b / c;
        const auto rc = sqrt( (rc_x * rc_x) + (rc_y * rc_y));
        const auto max_error = e * rc;
        return max_error;
      }
      return e;
    }
  }
  return std::numeric_limits<double>::epsilon();
  */
}


ribi::Plane::ApCoordinats2D ribi::Plane::CalcProjection(
  const ApCoordinats3D& points
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
  for (const auto point: m_points)
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
      //try { TRACE(m_plane_x->ToFunction()); } catch(std::logic_error&) { TRACE("Failed m_plane_x->ToFunction()"); }
      try { m_plane_x->CalcProjection(points); } catch (std::logic_error&) { TRACE("Failed m_plane_x->CalcProjection"); }
    }
  }
  {
    if (m_plane_y)
    {
      try { TRACE(*m_plane_y); } catch(std::logic_error&) { TRACE("Failed m_plane_y"); }
      //try { TRACE(m_plane_y->ToFunction()); } catch(std::logic_error&) { TRACE("Failed m_plane_y->ToFunction()"); }
      try { m_plane_y->CalcProjection(points); } catch (std::logic_error&) { TRACE("Failed m_plane_y->CalcProjection"); }
    }
  }
  {
    if (m_plane_z)
    {
      try { TRACE(*m_plane_z); } catch(std::logic_error&) { TRACE("Failed m_plane_z"); }
      //try { TRACE(m_plane_z->ToFunction()); } catch(std::logic_error&) { TRACE("Failed m_plane_z->ToFunction()"); }
      try { m_plane_z->CalcProjection(points); } catch (std::logic_error&) { TRACE("Failed m_plane_z->CalcProjection"); }
    }
  }
  for (const auto point: points)
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

ribi::Plane::Apfloat ribi::Plane::CalcX(const Apfloat& y, const Apfloat& z) const
{
  if (!CanCalcX())
  {
    throw std::logic_error("Plane::CalcX: cannot express the plane as 'X = A*Y + B*Z + C'");
  }
  return m_plane_x->CalcX(y,z);
}

/*
double ribi::Plane::CalcX(const double y, const double z) const
{
  return Geometry().ToDouble(CalcX(Apfloat(y),Apfloat(z)));
}
*/

ribi::Plane::Apfloat ribi::Plane::CalcY(const ribi::Plane::Apfloat& x, const ribi::Plane::Apfloat& z) const
{
  if (!CanCalcY())
  {
    throw std::logic_error("Plane::CalcY: cannot express the plane as 'Y = A*X + B*Y + C'");
  }
  return m_plane_y->CalcY(x,z);
}

/*
double ribi::Plane::CalcY(const double x, const double z) const
{
  return Geometry().ToDouble(CalcY(Apfloat(x),Apfloat(z)));
}
*/

ribi::Plane::Apfloat ribi::Plane::CalcZ(const ribi::Plane::Apfloat& x, const ribi::Plane::Apfloat& y) const
{
  if (!CanCalcZ())
  {
    throw std::logic_error("Plane::CalcZ: cannot express the plane as 'Z = A*X + B*Y + C'");
  }
  return m_plane_z->CalcZ(x,y);
}

/*
double ribi::Plane::CalcZ(const double x, const double y) const
{
  return Geometry().ToDouble(CalcZ(Apfloat(x),Apfloat(y)));
}
*/

bool ribi::Plane::CanCalcX() const noexcept
{
  if (!m_plane_x.get()) return false;
  try
  {
    //m_plane_x->GetFunctionAasApfloat();
    //m_plane_x->GetFunctionBasApfloat();
    //m_plane_x->GetFunctionCasApfloat();
    return true;
  }
  catch (std::exception&)
  {
    //OK
    return false;
  }
}
bool ribi::Plane::CanCalcY() const noexcept
{
  if (!m_plane_y.get()) return false;
  try
  {
    //m_plane_y->GetFunctionAasApfloat();
    //m_plane_y->GetFunctionBasApfloat();
    //m_plane_y->GetFunctionCasApfloat();
    return true;
  }
  catch (std::exception&)
  {
    //OK
    return false;
  }
}

bool ribi::Plane::CanCalcZ() const noexcept
{
  if (!m_plane_z.get()) return false;
  try
  {
    assert(m_plane_z->GetFunctionAasApfloat() == 0.0 || m_plane_z->GetFunctionAasApfloat() != 0.0);
    assert(m_plane_z->GetFunctionBasApfloat() == 0.0 || m_plane_z->GetFunctionBasApfloat() != 0.0);
    assert(m_plane_z->GetFunctionCasApfloat() == 0.0 || m_plane_z->GetFunctionCasApfloat() != 0.0);
    return true;
  }
  catch (std::exception& e)
  {
    TRACE(e.what())
    assert(!"Should not get here");
    throw;
  }
}

boost::shared_ptr<ribi::PlaneX> ribi::Plane::CreatePlaneX(
  const ApCoordinat3D& p1,
  const ApCoordinat3D& p2,
  const ApCoordinat3D& p3
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
  const ApCoordinat3D& p1,
  const ApCoordinat3D& p2,
  const ApCoordinat3D& p3
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
  const ApCoordinat3D& p1,
  const ApCoordinat3D& p2,
  const ApCoordinat3D& p3
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
  return "1.6";
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
    "2014-07-03: version 1.6: use of apfloat, improved accuracy"
  };
}

bool ribi::Plane::IsInPlane(const ApCoordinat3D& coordinat) const noexcept
{
  return
       (m_plane_x && m_plane_x->IsInPlane(coordinat))
    || (m_plane_y && m_plane_y->IsInPlane(coordinat))
    || (m_plane_z && m_plane_z->IsInPlane(coordinat))
  ;
  /*

  bool ribi::PlaneXYZ::IsInPlane(const Coordinat3D& coordinat) const noexcept
  try
  {
    const apfloat error = CalcErrorAsApfloat(coordinat);
    const apfloat max_error = CalcMaxErrorAsApfloat(coordinat); //std::numeric_limits<double>::epsilon();
    return error <= max_error;
  }
  catch (std::exception& e)
  {
    TRACE("ERROR");
    TRACE(e.what())
    assert(!"Should not get here");
    throw;
  }
  */
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
