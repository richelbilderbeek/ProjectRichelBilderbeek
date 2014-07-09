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
#include "planex.h"

#include <cassert>

#include "container.h"
#include "geometry.h"
#include "planez.h"
#include "trace.h"
#pragma GCC diagnostic pop

///Create plane X = 0.0
ribi::PlaneX::PlaneX() noexcept
  : PlaneX(
    Coordinat3D(0.0,0.0,0.0),
    Coordinat3D(0.0,1.0,0.0),
    Coordinat3D(0.0,0.0,1.0)
  )
{
  #ifndef NDEBUG
  Test();
  #endif
}


ribi::PlaneX::PlaneX(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
) : m_plane_z{Create(p1,p2,p3)}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::PlaneX::~PlaneX() noexcept
{
  //Nothing to do
}

apfloat ribi::PlaneX::CalcErrorAsApfloat(const Coordinat3D& coordinat) const noexcept
{
  const apfloat x = boost::geometry::get<0>(coordinat);
  const apfloat y = boost::geometry::get<1>(coordinat);
  const apfloat z = boost::geometry::get<2>(coordinat);
  const auto expected = x;
  const apfloat calculated = CalcX(y,z);
  const apfloat error = abs(calculated - expected);
  return error;
}

apfloat ribi::PlaneX::CalcMaxErrorAsApfloat(const Coordinat3D& coordinat) const noexcept
{
  //const apfloat x = boost::geometry::get<0>(coordinat);
  const apfloat y = boost::geometry::get<1>(coordinat);
  const apfloat z = boost::geometry::get<2>(coordinat);
  const auto coefficients = GetCoefficients();
  const auto a = coefficients[0];
  const auto b = coefficients[1];
  const auto c = coefficients[2];
  const apfloat e = boost::numeric::bounds<double>::smallest();
  assert(e > 0.0);
  //    x = -A/B.z - C/B.y + D/B
  //If B is zero, the slope in X and Y cannot be calculated
  if (b.sign())
  {
    const auto rc_y = -c / b;
    const auto rc_z = -a / b;
    const auto max_error_x = 0.0;
    const auto max_error_z = abs(e * rc_z * z) + 0.0;
    const auto max_error_y = abs(e * rc_y * y) + 0.0;
    const auto max_error = max_error_x + max_error_y + max_error_z;
    return max_error;
  }
  return e;
}

ribi::PlaneX::Coordinats2D ribi::PlaneX::CalcProjection(
  const Coordinats3D& points
) const
{
  assert(m_plane_z);
  auto v(points);
  for(auto& i: v) { i = Rotate(i); }
  try
  {
    return m_plane_z->CalcProjection(v);
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("PlaneX::CalcProjection: cannot calculate projection");
  }
}

ribi::PlaneX::Apfloat ribi::PlaneX::CalcX(const Apfloat& y, const Apfloat& z) const
{
  assert(m_plane_z);
  try
  {
    return m_plane_z->CalcZ(y,z);
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("ribi::PlaneX::CalcX: cannot calculate X of a horizontal plane");
  }
}

double ribi::PlaneX::CalcX(const double y, const double z) const
{
  return Geometry().ToDouble(CalcX(Apfloat(y),Apfloat(z)));
}

std::unique_ptr<ribi::PlaneZ> ribi::PlaneX::Create(
  const Coordinat3D& p1,
  const Coordinat3D& p2,
  const Coordinat3D& p3
)
{
  std::unique_ptr<PlaneZ> p(
    new PlaneZ(
      Rotate(p1),
      Rotate(p2),
      Rotate(p3)
    )
  );
  assert(p);
  return p;
}

std::vector<apfloat> ribi::PlaneX::GetCoefficients() const noexcept
{
  const auto v(m_plane_z->GetCoefficients());
  assert(v.size() == 4);
  return { v[2],v[0],v[1],v[3] };
}

double ribi::PlaneX::GetFunctionA() const
{
  assert(m_plane_z);
  return m_plane_z->GetFunctionA();
}

double ribi::PlaneX::GetFunctionB() const
{
  assert(m_plane_z);
  return m_plane_z->GetFunctionB();
}

double ribi::PlaneX::GetFunctionC() const
{
  assert(m_plane_z);
  return m_plane_z->GetFunctionC();
}

std::string ribi::PlaneX::GetVersion() const noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::PlaneX::GetVersionHistory() const noexcept
{
  return {
    "2014-03-10: version 1.0: initial version, split off from PlaneZ",
    "2014-03-13: version 1.1: bug fixed",
    "2014-04-01: version 1.2: use of std::unique_ptr",
    "2014-06-13: version 1.3: shortened time to compile, allow obtaining the constants in function 'x = Ay + Bz + C'",
    "2014-07-03: version 1.4: use of apfloat",
  };
}

bool ribi::PlaneX::IsInPlane(const Coordinat3D& coordinat) const noexcept
{
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
}

std::vector<apfloat> ribi::PlaneX::Rotate(const std::vector<apfloat>& coefficients) noexcept
{
  assert(coefficients.size() == 4);
  return
  {
    coefficients[2],
    coefficients[0],
    coefficients[1],
    coefficients[3]
  };
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::PlaneX::Rotate(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& point
) noexcept
{
  return Coordinat3D(
    boost::geometry::get<1>(point),
    boost::geometry::get<2>(point),
    boost::geometry::get<0>(point)
  );
}



std::string ribi::PlaneX::ToFunction() const
{
  std::stringstream s;
  s << (*this);
  return s.str();
  /*
  try
  {
    std::string s = m_plane_z->ToFunction();
    // 'z=(2*x) + (3*y) + 5'
    //          =>
    // 'x=(2*y) + (3*z) + 5'
    assert(!s.empty());
    s = boost::algorithm::replace_all_copy(s,"*y","*z");
    s = boost::algorithm::replace_all_copy(s,"*x","*y");
    s = boost::algorithm::replace_all_copy(s,"z=","x=");
    return s;
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("ribi::PlaneX::ToFunction: cannot calculate X of a horizontal plane");
  }
  */
}

std::ostream& ribi::operator<<(std::ostream& os,const PlaneX& planex)
{

  assert(planex.m_plane_z);
  try
  {
    os
      << "x=("
      << planex.m_plane_z->GetFunctionA() << "*y) + ("
      << planex.m_plane_z->GetFunctionB() << "*z) + "
      << planex.m_plane_z->GetFunctionC()
      //<< ", coefficients: "
      //<< Container().ToStr(planex.GetCoefficients())
    ;
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("ribi::PlaneX::operator<<: cannot display function of a horizontal plane");
  }
  return os;
}
