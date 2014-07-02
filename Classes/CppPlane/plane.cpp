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

#include <boost/make_shared.hpp>
#include <boost/limits.hpp>

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
  
  assert(Geometry().IsEqual(m_points[0],p1));
  assert(Geometry().IsEqual(m_points[1],p2));
  assert(Geometry().IsEqual(m_points[2],p3));
  #endif
}

std::vector<boost::geometry::model::d2::point_xy<double>> ribi::Plane::CalcProjection(
  const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points
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

double ribi::Plane::CalcX(const double y, const double z) const
{
  if (!CanCalcX())
  {
    throw std::logic_error("Plane::CalcX: cannot express the plane as 'X = A*Y + B*Z + C'");
  }
  return m_plane_x->CalcX(y,z);
}

double ribi::Plane::CalcY(const double x, const double z) const
{
  if (!CanCalcY())
  {
    throw std::logic_error("Plane::CalcY: cannot express the plane as 'Y = A*X + B*Y + C'");
  }
  return m_plane_y->CalcY(x,z);
}

double ribi::Plane::CalcZ(const double x, const double y) const
{
  if (!CanCalcZ())
  {
    throw std::logic_error("Plane::CalcZ: cannot express the plane as 'Z = A*X + B*Y + C'");
  }
  return m_plane_z->CalcZ(x,y);
}

bool ribi::Plane::CanCalcX() const noexcept
{
  if (!m_plane_x.get()) return false;
  try
  {
    m_plane_x->GetFunctionA();
    m_plane_x->GetFunctionB();
    m_plane_x->GetFunctionC();
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
    m_plane_y->GetFunctionA();
    m_plane_y->GetFunctionB();
    m_plane_y->GetFunctionC();
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
    m_plane_z->GetFunctionA();
    m_plane_z->GetFunctionB();
    m_plane_z->GetFunctionC();
    return true;
  }
  catch (std::exception&)
  {
    //OK
    return false;
  }
}

boost::shared_ptr<ribi::PlaneX> ribi::Plane::CreatePlaneX(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
) noexcept
{
  try
  {
    const boost::shared_ptr<PlaneX> p(
      boost::make_shared<PlaneX>(p1,p2,p3)
    );
    assert(p);
    return p;
  }
  catch (std::exception&)
  {
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
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
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

std::vector<double> ribi::Plane::GetCoefficientsX() const
{
  if (!m_plane_x)
  {
    throw std::logic_error("Plane::GetCoefficientsX: cannot express the plane as 'X = A*Y + B*Z + C'");
  }
  return m_plane_x->GetCoefficients();
}

std::vector<double> ribi::Plane::GetCoefficientsY() const
{
  if (!m_plane_y)
  {
    throw std::logic_error("Plane::GetCoefficientsY: cannot express the plane as 'Y = A*X + B*Z + C'");
  }
  return m_plane_y->GetCoefficients();
}

std::vector<double> ribi::Plane::GetCoefficientsZ() const
{
  if (!m_plane_z)
  {
    throw std::logic_error("Plane::GetCoefficientsZ: cannot express the plane as 'Z = A*X + B*Y + C'");
  }
  return m_plane_z->GetCoefficients();
}


std::string ribi::Plane::GetVersion() noexcept
{
  return "1.5";
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
  };
}

bool ribi::Plane::IsInPlane(const Coordinat3D& coordinat) const noexcept
{
  const bool verbose = true;
  const double x = boost::geometry::get<0>(coordinat);
  const double y = boost::geometry::get<1>(coordinat);
  const double z = boost::geometry::get<2>(coordinat);
  if (verbose)
  {
    TRACE(x);
    TRACE(y);
    TRACE(z);
    TRACE(*this);
    //TRACE(max_error);
    //try { TRACE(ToFunctionX()); } catch (std::exception&) {}
    //try { TRACE(ToFunctionY()); } catch (std::exception&) {}
    //try { TRACE(ToFunctionZ()); } catch (std::exception&) {}
  }
  try
  {
    const double expected = x;
    if (verbose) { TRACE(expected); }
    const double calculated = CalcX(y,z);
    if (verbose) { TRACE(calculated); }
    const double error = std::abs(calculated - expected);
    if (verbose) { TRACE(error); }
    const double max_error = 0.001;
    //const double max_error
    //  = m_plane_x->GetFunctionA() * boost::numeric::bounds<double>::smallest();
    if (verbose) { TRACE(max_error); }
    const bool is_in_plane = error < max_error;
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
    const double expected = y;
    if (verbose) { TRACE(expected); }
    const double calculated = CalcY(x,z);
    if (verbose) { TRACE(calculated); }
    const double error = std::abs(calculated - expected);
    if (verbose) { TRACE(error); }
    const double max_error = 0.001;
    //const double max_error
    //  = m_plane_?->GetFunction?() * boost::numeric::bounds<double>::smallest();
    if (verbose) { TRACE(max_error); }
    const bool is_in_plane = error < max_error;
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
    const double expected = z;
    if (verbose) { TRACE(expected); }
    const double calculated = CalcZ(x,y);
    if (verbose) { TRACE(calculated); }
    const double error =  std::abs(calculated - expected);
    if (verbose) { TRACE(error); }
    const double max_error = 0.001;
    //const double max_error
    //  = m_plane_?->GetFunction?() * boost::numeric::bounds<double>::smallest();
    if (verbose) { TRACE(max_error); }
    const bool is_in_plane = error < max_error;
    if (verbose) { TRACE(is_in_plane); }
    return is_in_plane;
  }
  catch (std::logic_error& e)
  {
    // OK
    if (verbose) { TRACE(e.what()); }
  }
  return false;
}

#ifndef NDEBUG
void ribi::Plane::Test() noexcept
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Plane::Test");
  const bool verbose = true;
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Point3D;
  using boost::geometry::get;
  Container();
  Geometry();
  { const auto planex = boost::make_shared<PlaneX>(); assert(planex); }
  { const auto planey = boost::make_shared<PlaneY>(); assert(planey); }
  { const auto planez = boost::make_shared<PlaneZ>(); assert(planez); }

  if (verbose) TRACE("Plane that can be expressed in all three forms");
  {
    const Point3D p1( 1.0, 2.0,3.0);
    const Point3D p2( 4.0, 6.0,9.0);
    const Point3D p3(12.0,11.0,9.0);
    const Plane p(p1,p2,p3);
    assert(p.CanCalcX());
    assert(p.CanCalcY());
    assert(p.CanCalcZ());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );

  }
  if (verbose) TRACE("Plane X = 2");
  {
    const Point3D p1(2.0, 2.0,3.0);
    const Point3D p2(2.0, 6.0,9.0);
    const Point3D p3(2.0,11.0,9.0);
    const Plane p(p1,p2,p3);
    assert(p.CanCalcX());
    assert(!p.CanCalcY());
    assert(!p.CanCalcZ());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );
  }
  if (verbose) TRACE("Plane X = 123");
  {
    const Point3D p1(123.0, 2.0,3.0);
    const Point3D p2(123.0, 6.0,9.0);
    const Point3D p3(123.0,11.0,9.0);
    const Plane p(p1,p2,p3);
    assert(p.CanCalcX());
    assert(!p.CanCalcY());
    assert(!p.CanCalcZ());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );
  }
  if (verbose) TRACE("Plane Y = 3");
  {
    const Point3D p1( 2.0, 3.0, 5.0);
    const Point3D p2( 7.0, 3.0, 9.0);
    const Point3D p3(11.0,3.0,13.0);
    const Plane p(p1,p2,p3);

    assert(p.CanCalcY());
    assert(!p.CanCalcX());
    assert(!p.CanCalcZ());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );
  }
  if (verbose) TRACE("Plane Z = 5");
  {
    const Point3D p1( 2.0, 3.0,5.0);
    const Point3D p2( 7.0,11.0,5.0);
    const Point3D p3(13.0,17.0,5.0);
    const Plane p(p1,p2,p3);
    assert(p.CanCalcZ());
    assert(!p.CanCalcX());
    assert(!p.CanCalcY());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );
  }
  if (verbose) TRACE("IsInPlane, X = 0 plane");
  {
    const Point3D p1(0.0,0.0,0.0);
    const Point3D p2(0.0,0.0,1.0);
    const Point3D p3(0.0,1.0,0.0);
    const Plane p(p1,p2,p3);
    assert(p.IsInPlane(Point3D(0.0, 2.0, 2.0)));
    assert(p.IsInPlane(Point3D(0.0, 2.0,-2.0)));
    assert(p.IsInPlane(Point3D(0.0,-2.0, 2.0)));
    assert(p.IsInPlane(Point3D(0.0,-2.0,-2.0)));
  }
  if (verbose) TRACE("IsInPlane, Y = 0 plane");
  {
    const Point3D p1(0.0,0.0,0.0);
    const Point3D p2(0.0,0.0,1.0);
    const Point3D p3(1.0,0.0,0.0);
    const Plane p(p1,p2,p3);
    assert(p.IsInPlane(Point3D( 2.0,0.0, 2.0)));
    assert(p.IsInPlane(Point3D( 2.0,0.0,-2.0)));
    assert(p.IsInPlane(Point3D(-2.0,0.0, 2.0)));
    assert(p.IsInPlane(Point3D(-2.0,0.0,-2.0)));
  }
  if (verbose) TRACE("IsInPlane, Z = 0 plane");
  {
    const Point3D p1(0.0,0.0,0.0);
    const Point3D p2(0.0,1.0,0.0);
    const Point3D p3(1.0,0.0,0.0);
    const Plane p(p1,p2,p3);
    assert(p.IsInPlane(Point3D( 2.0, 2.0,0.0)));
    assert(p.IsInPlane(Point3D( 2.0,-2.0,0.0)));
    assert(p.IsInPlane(Point3D(-2.0, 2.0,0.0)));
    assert(p.IsInPlane(Point3D(-2.0,-2.0,0.0)));
  }
  if (verbose) TRACE("IsInPlane, Z = 0 plane, zooming in, #223");
  {
    for (double i=1.0; i!=0.0; i/=10.0)
    {
      TRACE(i);
      const Point3D p1(0.0,0.0,0.0);
      const Point3D p2(0.0,i,0.0);
      const Point3D p3(i,0.0,0.0);
      const Plane p(p1,p2,p3);
      assert(p.IsInPlane(Point3D( 2.0, 2.0,0.0)));
      assert(p.IsInPlane(Point3D( 2.0,-2.0,0.0)));
      assert(p.IsInPlane(Point3D(-2.0, 2.0,0.0)));
      assert(p.IsInPlane(Point3D(-2.0,-2.0,0.0)));
    }
  }
  if (verbose) TRACE("CalcProjection, from a crash in the program");
  {
    const Point3D p1( 1.0,-0.0,0.0);
    const Point3D p2(-1.0, 0.0,0.0);
    const Point3D p3( 1.0,-0.0,1.0);
    const Point3D p4(-1.0, 0.0,1.0);
    const Plane p(p1,p2,p3);

    assert(p.CanCalcY());
    //assert(!p.ToFunctionY().empty());

    assert(!p.CanCalcX());
    //try { p.ToFunctionX(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }

    assert(!p.CanCalcZ());
    //try { p.ToFunctionZ(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }
    assert(!p.CalcProjection( { p1,p2,p3,p4 } ).empty());
  }
  if (verbose) TRACE("IsInPlane, from #218");
  {
    const Point3D p1(-0.5500000000000004884981308350688777863979339599609375,2.000000000000000444089209850062616169452667236328125,0);
    const Point3D p2(-3.78623595505618038004058689693920314311981201171875,2,0);
    const Point3D p3(-0.5500000000000004884981308350688777863979339599609375,2.000000000000000444089209850062616169452667236328125,10);
    const Point3D p4(-3.78623595505618038004058689693920314311981201171875,2,10);
    const Plane p(p1,p2,p3);
    if(!p.IsInPlane(p4))
    {
      TRACE("ERROR");
      std::stringstream s;
      s
        << std::setprecision(99)
        << p << '\n'
        << Container().ToStr(p.GetCoefficientsX()) << '\n'
        << Container().ToStr(p.GetCoefficientsY()) << '\n'
        << Container().ToStr(p.GetCoefficientsZ()) << '\n'
      ;
      TRACE(s.str());
      TRACE("BREAK");
    }
    assert(p.IsInPlane(p4));
  }
  if (verbose) TRACE("IsInPlane, from >#220");
  {
    TRACE("***********************************************");
    const double x1 = 0.0004035051226622692510832834944523028752882964909076690673828125;
    const double y1 = 0.00023296416881187433805568132161312178141088224947452545166015625;
    const double z1 = 0; //left out the '.0' intentionally

    const double x2 = 0.000403505141811931846741734464245610070065595209598541259765625;
    const double y2 = 0.00023296414405748076185791173298156309101614169776439666748046875;
    const double z2 = 0; //left out the '.0' intentionally

    const double x3 = 0.0004035051226622692510832834944523028752882964909076690673828125;
    const double y3 = 0.00023296416881187433805568132161312178141088224947452545166015625;
    const double z3 = 0.00025000000000000000520417042793042128323577344417572021484375;

    const double x4 = 0.000403505141811931846741734464245610070065595209598541259765625;
    const double y4 = 0.00023296414405748076185791173298156309101614169776439666748046875;
    const double z4 = 0.00025000000000000000520417042793042128323577344417572021484375;

    const Point3D p1(x1,y1,z1);
    const Point3D p2(x2,y2,z2);
    const Point3D p3(x3,y3,z3);
    const Point3D p4(x4,y4,z4);
    const Plane p(p1,p2,p3);
    try
    {
      assert(p.IsInPlane(p4));
    }
    catch (std::exception&)
    {
      TRACE("ERROR");
      std::stringstream s;
      s
        << std::setprecision(99)
        << p << '\n'
        << Container().ToStr(p.GetCoefficientsX()) << '\n'
        << Container().ToStr(p.GetCoefficientsY()) << '\n'
        << Container().ToStr(p.GetCoefficientsZ()) << '\n'
      ;
      TRACE(s.str());
      TRACE("BREAK");
    }
    assert(p.IsInPlane(p4));
  }
  assert(!"yay, solved");
  TRACE("Finished ribi::Plane::Test successfully");
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const Plane& plane) noexcept
{
  os << '(';
  const auto n_points = static_cast<int>(plane.m_points.size());
  for (/* const */ auto i=0; i!=n_points; ++i)
  {
    os << plane.m_points[i];
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
