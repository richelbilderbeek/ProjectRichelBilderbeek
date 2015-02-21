//---------------------------------------------------------------------------
/*
Plane, 3D plane class
Copyright (C) 2013-2015 Richel Bilderbeek

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

apfloat ribi::PlaneX::CalcError(const Coordinat3D& coordinat) const noexcept
{
  const apfloat x = boost::geometry::get<0>(coordinat);
  const apfloat y = boost::geometry::get<1>(coordinat);
  const apfloat z = boost::geometry::get<2>(coordinat);
  const auto expected = x;
  const apfloat calculated = CalcX(y,z);
  const apfloat error = abs(calculated - expected);
  return error;
}

ribi::PlaneX::Double ribi::PlaneX::CalcMinErrorPerC() noexcept
{
  //min_error_per_c will be about 0.000000001
  //stub_value increases this jut a little, by a 0.000001%
  const double stub_value = 0.000000001 * 1.00000001;
  #define USE_STUB
  #ifdef USE_STUB
  return stub_value;
  #else //USE_STUB
  //PlaneX calculates its own tolerance for errors, by measuring it
  static Double min_error_per_c = 0.0;
  if (min_error_per_c > 0.0) return min_error_per_c;

  //const double low = std::numeric_limits<double>::denorm_min();
  //const double high = std::numeric_limits<double>::max();
  const double low  = 1.0e-16;
  const double high = 1.0e+16;
  const double min_x = low;
  const double max_x = high;
  const double min_y = low;
  const double max_y = high;
  const double min_z = low;
  const double max_z = high;
  const apfloat zero(0.0);

  for (double z = min_z; z < max_z; z*=10.0)
  {
    for (double y = min_y; y < max_y; y*=10.0)
    {
      for (double x = min_x; x < max_x; x*=10.0)
      //const double x = y;
      {
        const Coordinat3D p1(  x,0.0,0.0);
        const Coordinat3D p2(  x,  y,0.0);
        const Coordinat3D p3(  x,0.0,z);
        const PlaneX p(p1,p2,p3);
        for (const auto& p4: { p1, p2, p3 } )
        {
          const auto error = p.CalcError(p4);
          const auto error_per_c = error / p.GetFunctionC();
          assert(error_per_c >= zero);
          //TRACE(apfloat(min_error_per_c) / p.GetFunctionC());
          if (error_per_c > min_error_per_c)
          {
            min_error_per_c = error_per_c;
            //TRACE(min_error_per_c);
            //TRACE(x);
            //TRACE(y);
            //TRACE(z);
            //TRACE(p.GetFunctionC());
            //TRACE(apfloat(min_error_per_c) / p.GetFunctionC());
            //std::stringstream s;
            //s << Geometry().ToStr(p4) << " " << min_error;
            //TRACE(s.str());
          }
        }
      }
    }
    //TRACE(min_error_per_c);
  }
  //TRACE(min_error_per_c); //0.000000001e0
  assert(min_error_per_c > zero);
  assert(min_error_per_c < stub_value);
  assert(min_error_per_c > 0.99 * stub_value);
  return min_error_per_c;
  #endif //USE_STUB
}

apfloat ribi::PlaneX::CalcMaxError(const Coordinat3D& /*coordinat*/) const noexcept
{
  assert(CalcMinErrorPerC() > apfloat(0.0));
  const auto max_error = abs(CalcMinErrorPerC() * GetFunctionC());
  assert(max_error >= apfloat(0.0));
  return max_error;
  /*
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
    assert(max_error >= 0.0);
    return max_error;
  }
  assert(e > 0.0);
  return e;
  */
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

ribi::PlaneX::Double ribi::PlaneX::CalcX(const Double& y, const Double& z) const
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

apfloat ribi::PlaneX::GetFunctionA() const
{
  assert(m_plane_z);
  return m_plane_z->GetFunctionA();
}

apfloat ribi::PlaneX::GetFunctionB() const
{
  assert(m_plane_z);
  return m_plane_z->GetFunctionB();
}

apfloat ribi::PlaneX::GetFunctionC() const
{
  assert(m_plane_z);
  return m_plane_z->GetFunctionC();
}

std::string ribi::PlaneX::GetVersion() const noexcept
{
  return "1.6";
}

std::vector<std::string> ribi::PlaneX::GetVersionHistory() const noexcept
{
  return {
    "2014-03-10: version 1.0: initial version, split off from PlaneZ",
    "2014-03-13: version 1.1: bug fixed",
    "2014-04-01: version 1.2: use of std::unique_ptr",
    "2014-06-13: version 1.3: shortened time to compile, allow obtaining the constants in function 'x = Ay + Bz + C'",
    "2014-07-03: version 1.4: use of apfloat",
    "2014-07-09: version 1.5: use double in interface only",
    "2014-07-10: version 1.6: use of apfloat only"
  };
}

bool ribi::PlaneX::IsInPlane(const Coordinat3D& coordinat) const noexcept
{
  try
  {
    const apfloat error = CalcError(coordinat);
    const apfloat max_error = CalcMaxError(coordinat);
    return error <= max_error;
  }
  catch (std::exception& e)
  {
    TRACE("ERROR");
    TRACE(e.what());
    assert(!"Should not get here");
    throw;
  }
}

std::vector<apfloat> ribi::PlaneX::Rotate(const Doubles& coefficients) noexcept
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

ribi::PlaneX::Coordinat3D ribi::PlaneX::Rotate(
  const Coordinat3D& point
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
    ;
  }
  catch (std::logic_error&)
  {
    throw std::logic_error("ribi::PlaneX::operator<<: cannot display function of a horizontal plane");
  }
  return os;
}
