#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "plane.h"

#include <cassert>

#include "geometry.h"
#include "trace.h"
#pragma GCC diagnostic pop

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
  TRACE(points.size());
  {
    const auto plane (m_plane_x);
    if (plane) { try { TRACE(plane->ToFunction()); } catch(std::logic_error&) { /* OK */ } }
  }
  {
    const auto plane (m_plane_y);
    if (plane) { try { TRACE(plane->ToFunction()); } catch(std::logic_error&) { /* OK */ } }
  }
  {
    const auto plane (m_plane_z);
    if (plane) { try { TRACE(plane->ToFunction()); } catch(std::logic_error&) { /* OK */ } }
  }
  for (auto point: points)
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
  if (!m_plane_x)
  {
    throw std::logic_error("Plane::CalcX: cannot express the plane as 'X = A*Y + B*Z + C'");
  }
  return m_plane_x->CalcX(y,z);
}

double ribi::Plane::CalcY(const double x, const double z) const
{
  if (!m_plane_y)
  {
    throw std::logic_error("Plane::CalcY: cannot express the plane as 'Y = A*X + B*Y + C'");
  }
  return m_plane_y->CalcY(x,z);
}

double ribi::Plane::CalcZ(const double x, const double y) const
{
  if (!m_plane_z)
  {
    throw std::logic_error("Plane::CalcZ: cannot express the plane as 'Z = A*X + B*Y + C'");
  }
  return m_plane_z->CalcZ(x,y);
}

/*
boost::shared_ptr<ribi::PlaneZ> ribi::Plane::CreatePlaneZ(
  const std::vector<double>& coefficients_z
) noexcept
{
  try
  {
    const boost::shared_ptr<PlaneZ> p(new PlaneZ(coefficients_z));
    return p;
  }
  catch (std::exception&)
  {
    return nullptr;
  }
}
*/

boost::shared_ptr<ribi::PlaneX> ribi::Plane::CreatePlaneX(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
) noexcept
{
  try
  {
    const boost::shared_ptr<PlaneX> p(new PlaneX(p1,p2,p3));
    return p;
  }
  catch (std::exception&)
  {
    return nullptr;
  }
}

boost::shared_ptr<ribi::PlaneY> ribi::Plane::CreatePlaneY(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
) noexcept
{
  try
  {
    const boost::shared_ptr<PlaneY> p(new PlaneY(p1,p2,p3));
    return p;
  }
  catch (std::exception&)
  {
    return nullptr;
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
    const boost::shared_ptr<PlaneZ> p(new PlaneZ(p1,p2,p3));
    return p;
  }
  catch (std::exception&)
  {
    return nullptr;
  }
}

boost::shared_ptr<ribi::PlaneX> ribi::Plane::CreatePlaneX(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p4
) noexcept
{
  try
  {
    const boost::shared_ptr<PlaneX> p(new PlaneX(p1,p2,p3,p4));
    return p;
  }
  catch (std::exception&)
  {
    return nullptr;
  }
}

boost::shared_ptr<ribi::PlaneY> ribi::Plane::CreatePlaneY(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p4
) noexcept
{
  try
  {
    const boost::shared_ptr<PlaneY> p(new PlaneY(p1,p2,p3,p4));
    return p;
  }
  catch (std::exception&)
  {
    return nullptr;
  }
}

boost::shared_ptr<ribi::PlaneZ> ribi::Plane::CreatePlaneZ(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p4
) noexcept
{
  try
  {
    const boost::shared_ptr<PlaneZ> p(new PlaneZ(p1,p2,p3,p4));
    return p;
  }
  catch (std::exception&)
  {
    return nullptr;
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


std::string ribi::Plane::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Plane::GetVersionHistory() const noexcept
{
  return {
    "2014-03-07: version 1.0: initial version",
    "2014-03-10: version 1.1: allow vertical planes"
  };
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
  //typedef boost::geometry::model::d2::point_xy<double> Point2D;
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Point3D;
  using boost::geometry::get;

  //Plane that can be expressed in all three forms
  {
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    typedef point<double,3,cartesian> Point;
    const double p1_x { 1.0 };
    const double p1_y { 2.0 };
    const double p1_z { 3.0 };
    const double p2_x { 4.0 };
    const double p2_y { 6.0 };
    const double p2_z { 9.0 };
    const double p3_x {12.0 };
    const double p3_y {11.0 };
    const double p3_z { 9.0 };
    const Plane p(
      Point(p1_x,p1_y,p1_z),
      Point(p2_x,p2_y,p2_z),
      Point(p3_x,p3_y,p3_z)
    );
    assert(!p.ToFunctionX().empty());
    assert(!p.ToFunctionY().empty());
    assert(!p.ToFunctionZ().empty());
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
  ///Plane X = 2
  {
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    typedef point<double,3,cartesian> Point;
    const double p1_x { 2.0 };
    const double p1_y { 2.0 };
    const double p1_z { 3.0 };
    const double p2_x { 2.0 };
    const double p2_y { 6.0 };
    const double p2_z { 9.0 };
    const double p3_x { 2.0 };
    const double p3_y {11.0 };
    const double p3_z { 9.0 };
    const Plane p(
      Point(p1_x,p1_y,p1_z),
      Point(p2_x,p2_y,p2_z),
      Point(p3_x,p3_y,p3_z)
    );
    assert(!p.ToFunctionX().empty());
    TRACE(p.ToFunctionX());
    try { p.ToFunctionY(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }
    try { p.ToFunctionZ(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }
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
  //Plane Y = 3
  {
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    typedef point<double,3,cartesian> Point;
    const double p1_x {  2.0 };
    const double p1_y {  3.0 };
    const double p1_z {  5.0 };
    const double p2_x {  7.0 };
    const double p2_y {  3.0 };
    const double p2_z {  9.0 };
    const double p3_x { 11.0 };
    const double p3_y {  3.0 };
    const double p3_z { 13.0 };
    const Plane p(
      Point(p1_x,p1_y,p1_z),
      Point(p2_x,p2_y,p2_z),
      Point(p3_x,p3_y,p3_z)
    );
    assert(!p.ToFunctionY().empty());
    TRACE(p.ToFunctionY());
    try { p.ToFunctionX(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }
    try { p.ToFunctionZ(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }
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
  //Plane Z = 5
  {
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    typedef point<double,3,cartesian> Point;
    const double p1_x {  2.0 };
    const double p1_y {  3.0 };
    const double p1_z {  5.0 };
    const double p2_x {  7.0 };
    const double p2_y { 11.0 };
    const double p2_z {  5.0 };
    const double p3_x { 13.0 };
    const double p3_y { 17.0 };
    const double p3_z {  5.0 };
    const Plane p(
      Point(p1_x,p1_y,p1_z),
      Point(p2_x,p2_y,p2_z),
      Point(p3_x,p3_y,p3_z)
    );
    assert(!p.ToFunctionZ().empty());
    TRACE(p.ToFunctionZ());
    try { p.ToFunctionX(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }
    try { p.ToFunctionY(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }
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
  //CalcProjection, from a crash in the program
  {
    //assert(!"TODO");
    /*
    TRACE 's.str()' line 42 in file '..\..\..\Projects\Classes\CppPlane\plane.cpp':'(0.000515,0.000754,0.0015)'
    TRACE 's.str()' line 42 in file '..\..\..\Projects\Classes\CppPlane\plane.cpp':'(-0.000515,0.000754,0.0015)'
    TRACE 's.str()' line 42 in file '..\..\..\Projects\Classes\CppPlane\plane.cpp':'(0.000515,0.000754,0.002)'
    TRACE 's.str()' line 42 in file '..\..\..\Projects\Classes\CppPlane\plane.cpp':'(-0.000515,0.000754,0.002)'
    */
  }
  TRACE("Finished ribi::Plane::Test successfully");
}
#endif

std::string ribi::Plane::ToFunctionX() const
{
  if (!m_plane_x)
  {
    throw std::logic_error("Plane::ToFunctionX: no plane X: plane cannot be expressed as X = A*Y + B*Z");
  }
  try
  {
     return m_plane_x->ToFunction();
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("Plane::ToFunctionX: plane cannot be expressed as X = A*Y + B*Z");
  }
}

std::string ribi::Plane::ToFunctionY() const
{
  if (!m_plane_y)
  {
    throw std::logic_error("Plane::ToFunctionY: no plane Y: plane cannot be expressed as Y = A*X + B*Z");
  }
  try
  {
     return m_plane_y->ToFunction();
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("Plane::ToFunctionY: plane cannot be expressed as Y = A*X + B*Z");
  }
}
std::string ribi::Plane::ToFunctionZ() const
{
  if (!m_plane_z)
  {
    throw std::logic_error("Plane::ToFunctionZ: no plane Z: plane cannot be expressed as Z = A*X + B*Y");
  }
  try
  {
     return m_plane_z->ToFunction();
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("Plane::ToFunctionZ: plane cannot be expressed as Z = A*X + B*Y");
  }
}


