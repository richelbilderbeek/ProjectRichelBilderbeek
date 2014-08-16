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
#ifdef USE_CUSTOM_RIBI_COORDINAT3D
#include "coordinat3d.h"

#include <array>
#include <cmath>

#include "trace.h"
#include "xml.h"

Coordinat3D::Coordinat3D(const double x, const double y, const double z) noexcept
  : m_co{ { x,y,z } }
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string Coordinat3D::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> Coordinat3D::GetVersionHistory() const noexcept
{
  return {
    "201x-xx-xx: version 1.0: initial version"
    "2014-03-07: version 1.1: initial versioning"
  };
}

Coordinat3D& Coordinat3D::operator+=(const Coordinat3D& rhs) noexcept
{
  m_co[0] += rhs.GetX();
  m_co[1] += rhs.GetY();
  m_co[2] += rhs.GetZ();
  return *this;
}

Coordinat3D& Coordinat3D::operator-=(const Coordinat3D& rhs) noexcept
{
  m_co[0] -= rhs.GetX();
  m_co[1] -= rhs.GetY();
  m_co[2] -= rhs.GetZ();
  return *this;
}

Coordinat3D& Coordinat3D::operator/=(const double f)
{
  assert(f != 0.0);
  m_co[0] /= f;
  m_co[1] /= f;
  m_co[2] /= f;
  return *this;
}

Coordinat3D& Coordinat3D::operator*=(const double f) noexcept
{
  m_co[0] *= f;
  m_co[1] *= f;
  m_co[2] *= f;
  return *this;
}

Coordinat3D ribi::CalcCenter(const std::vector<Coordinat3D>& points) noexcept
{
  Coordinat3D sum;
  for (const auto& point: points)
  {
    sum += point;
  }
  const double n { static_cast<double>(points.size()) };
  const Coordinat3D center(
    sum.GetX() / n,
    sum.GetY() / n,
    sum.GetZ() / n
  );
  return center;
}

Coordinat3D ribi::CalcCrossProduct(
  const Coordinat3D& a,
  const Coordinat3D& b
) noexcept
{
  return Coordinat3D(
    (a.GetY() * b.GetZ()) - (a.GetZ() * b.GetY()),
    (a.GetZ() * b.GetX()) - (a.GetX() * b.GetZ()),
    (a.GetX() * b.GetY()) - (a.GetY() * b.GetX())
  );
}

double ribi::CalcDotProduct(
  const Coordinat3D& a,
  const Coordinat3D& b
) noexcept
{
  return
      (a.GetX() * b.GetX())
    + (a.GetY() * b.GetY())
    + (a.GetZ() * b.GetZ());
}

Coordinat3D ribi::CalcNormal(
  const Coordinat3D& a,
  const Coordinat3D& b,
  const Coordinat3D& c
) noexcept
{
  const Coordinat3D u { c - a};
  const Coordinat3D v { b - a};
  return CalcCrossProduct(u,v);
}

double ribi::Distance(const Coordinat3D& lhs,const Coordinat3D& rhs) noexcept
{
  const double dx = lhs.GetX() - rhs.GetX();
  const double dy = lhs.GetY() - rhs.GetY();
  const double dz = lhs.GetZ() - rhs.GetZ();
  return std::sqrt(
      (dx * dx)
    + (dy * dy)
    + (dz * dz)
  );
}

double ribi::Length(const Coordinat3D& v) noexcept
{
  return std::sqrt(
      (v.GetX() * v.GetX())
    + (v.GetY() * v.GetY())
    + (v.GetZ() * v.GetZ())
  );
}

#ifndef NDEBUG
void Coordinat3D::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //CalcCenter, one Coordinat3D
  {
    assert(CalcCenter( { Coordinat3D() } ) == Coordinat3D());
    assert(CalcCenter( { Coordinat3D(1.1,2.2) } ) == Coordinat3D(1.1,2.2));
  }
  //CalcCenter, three Coordinat3D
  {
    const Coordinat3D center {
      CalcCenter(
        {
          Coordinat3D(0.0,1.0),
          Coordinat3D(1.0,2.0),
          Coordinat3D(2.0,3.0)
        }
      )
    };
    const Coordinat3D expected(1.0,2.0);
    assert(std::abs(center.GetX() - expected.GetX()) < 0.0001);
    assert(std::abs(center.GetY() - expected.GetY()) < 0.0001);
    assert(std::abs(center.GetZ() - expected.GetZ()) < 0.0001);
  }
  //CalcCenter, three Coordinat3D
  {
    const Coordinat3D center {
      CalcCenter(
        {
          Coordinat3D(-0.0,-1.0,2.0),
          Coordinat3D(-1.0,-2.0,4.0),
          Coordinat3D(-2.0,-3.0,6.0)
        }
      )
    };
    const Coordinat3D expected(-1.0,-2.0,4.0);
    assert(std::abs(center.GetX() - expected.GetX()) < 0.0001);
    assert(std::abs(center.GetY() - expected.GetY()) < 0.0001);
    assert(std::abs(center.GetZ() - expected.GetZ()) < 0.0001);
  }
  //CalcCrossProduct, XY plane
  {
    //Follow https://en.wikipedia.org/wiki/Cross_product
    //where
    //- a     = {1.0,0.0, 0.0}
    //-     b = {0.0,1.0, 0.0}
    //- a * b = {0.0,0.0, 1.0}
    //- b * a = {0.0,0.0,-1.0}
    const Coordinat3D a(1.0,0.0,0.0);
    const Coordinat3D b(0.0,1.0,0.0);
    const Coordinat3D p1 { CalcCrossProduct(a,b) };
    const Coordinat3D p1_expected(0.0,0.0,1.0);
    const Coordinat3D p2 { CalcCrossProduct(b,a) };
    const Coordinat3D p2_expected(0.0,0.0,-1.0);

    assert(std::abs(p1.GetX() - p1_expected.GetX()) < 0.0001);
    assert(std::abs(p1.GetY() - p1_expected.GetY()) < 0.0001);
    assert(std::abs(p1.GetZ() - p1_expected.GetZ()) < 0.0001);
    assert(std::abs(p2.GetX() - p2_expected.GetX()) < 0.0001);
    assert(std::abs(p2.GetY() - p2_expected.GetY()) < 0.0001);
    assert(std::abs(p2.GetZ() - p2_expected.GetZ()) < 0.0001);
  }
  //CalcDotProduct, XY plane
  {
    //From https://en.wikipedia.org/wiki/Dotproduct
    const Coordinat3D a(1.0, 3.0,-5.0);
    const Coordinat3D b(4.0,-2.0,-1.0);
    const double p { CalcDotProduct(a,b) };
    const double q { CalcDotProduct(b,a) };
    const double e { 3.0 };

    assert(std::abs(p - e) < 0.0001);
    assert(std::abs(q - e) < 0.0001);
    assert(std::abs(p - q) < 0.0001);
  }
  {
    //From https://en.wikipedia.org/wiki/Dotproduct
    //'In particular, if A and B are orthogonal, then [...] A dot b = 0'
    const Coordinat3D a(1.0,0.0,0.0);
    const Coordinat3D b(0.0,1.0,0.0);
    const double p { CalcDotProduct(a,b) };
    const double q { CalcDotProduct(b,a) };
    const double e { 0.0 };

    assert(std::abs(p - e) < 0.0001);
    assert(std::abs(q - e) < 0.0001);
    assert(std::abs(p - q) < 0.0001);
  }
  //CalcNormal, XY plane
  {
    /*

       0 1 2 3
     0 +------X
       |
     1 | A    (Z = 1)
       | |\
     2 | C-B
       |
     3 |
       Y

    */
    const Coordinat3D normal {
      CalcNormal(
        Coordinat3D(1.0,1.0,-1.0), //A
        Coordinat3D(2.0,2.0,-1.0), //B
        Coordinat3D(1.0,2.0,-1.0)  //C
      )
    };
    const Coordinat3D expected(0.0,0.0,-1.0);
    assert(std::abs(normal.GetX() - expected.GetX()) < 0.0001);
    assert(std::abs(normal.GetY() - expected.GetY()) < 0.0001);
    assert(std::abs(normal.GetZ() - expected.GetZ()) < 0.0001);
  }
  //CalcNormal, XY plane
  {
    /*

       0 1 2 3
     0 +------X
       |
     1 | A    (Z = 1)
       | |\
     2 | B-C
       |
     3 |
       Y

    */
    const Coordinat3D normal {
      CalcNormal(
        Coordinat3D(1.0,1.0,-1.0), //A
        Coordinat3D(1.0,2.0,-1.0), //B
        Coordinat3D(2.0,2.0,-1.0)  //C
      )
    };
    const Coordinat3D expected(0.0,0.0,1.0);
    assert(std::abs(normal.GetX() - expected.GetX()) < 0.0001);
    assert(std::abs(normal.GetY() - expected.GetY()) < 0.0001);
    assert(std::abs(normal.GetZ() - expected.GetZ()) < 0.0001);
  }

}
#endif

Coordinat3D ribi::operator-(
  const Coordinat3D& v1,
  const Coordinat3D& v2) noexcept
{
  return Coordinat3D(
    v1.GetX()-v2.GetX(),
    v1.GetY()-v2.GetY(),
    v1.GetZ()-v2.GetZ()
  );
}

Coordinat3D ribi::operator+(
  const Coordinat3D& v1,
  const Coordinat3D& v2) noexcept
{
  return Coordinat3D(
    v1.GetX()+v2.GetX(),
    v1.GetY()+v2.GetY(),
    v1.GetZ()+v2.GetZ()
  );
}

Coordinat3D ribi::operator/(
  const Coordinat3D& c,
  const double f)
{
  assert(f != 0.0);
  return Coordinat3D(
    c.GetX() / f,
    c.GetY() / f,
    c.GetZ() / f
  );
}

Coordinat3D ribi::operator*(
  const Coordinat3D& c,
  const double f) noexcept
{
  return Coordinat3D(
    c.GetX() * f,
    c.GetY() * f,
    c.GetZ() * f
  );
}


bool ribi::operator==(const Coordinat3D& lhs, const Coordinat3D& rhs) noexcept
{
  return
       lhs.GetX() == rhs.GetX()
    && lhs.GetY() == rhs.GetY()
    && lhs.GetZ() == rhs.GetZ();
}

bool ribi::operator<(const Coordinat3D& lhs, const Coordinat3D& rhs) noexcept
{
  if (lhs.GetX() < rhs.GetX()) return true;
  if (lhs.GetX() > rhs.GetX()) return false;

  if (lhs.GetY() < rhs.GetY()) return true;
  if (lhs.GetY() > rhs.GetY()) return false;

  return lhs.GetZ() < rhs.GetZ();
}

std::ostream& ribi::operator<<(std::ostream& os, const Coordinat3D& n) noexcept
{
  std::stringstream s;
  s
    << ribi::xml::ToXml("x",n.GetX())
    << ribi::xml::ToXml("y",n.GetY())
    << ribi::xml::ToXml("z",n.GetZ());
  os << ribi::xml::ToXml("coordinat3d",s.str());
  return os;
}

#endif
