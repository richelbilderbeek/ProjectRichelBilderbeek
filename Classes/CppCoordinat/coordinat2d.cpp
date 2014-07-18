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

#include "coordinat2d.h"

#include <array>
#include <iostream>

#include "trace.h"
#include "xml.h"

ribi::Coordinat2D::Coordinat2D(const double x, const double y) noexcept
  : m_co{ { x,y } }
{
  #ifndef NDEBUG
  Test();
  #endif
}

//ribi::Coordinat2D::Coordinat2D(const Coordinat2D& rhs)
//  : m_co{ { rhs.GetX(), rhs.GetY() } }
//{
//  assert(*this == rhs);
//}

//ribi::Coordinat2D& ribi::Coordinat2D::operator=(const Coordinat2D& rhs)
//{
//  m_co = { rhs.GetX(), rhs.GetY() };
//  assert(*this == rhs);
//  return *this;
//}

ribi::Coordinat2D& ribi::Coordinat2D::operator+=(const Coordinat2D& rhs) noexcept
{
  m_co[0] += rhs.GetX();
  m_co[1] += rhs.GetY();
  return *this;
}

ribi::Coordinat2D& ribi::Coordinat2D::operator-=(const Coordinat2D& rhs) noexcept
{
  m_co[0] -= rhs.GetX();
  m_co[1] -= rhs.GetY();
  return *this;
}

double ribi::operator*(const Coordinat2D& v1,const Coordinat2D& v2) noexcept
{
  return
      ( v1.GetX() * v2.GetX())
    + ( v1.GetY() * v2.GetY())
  ;
}

ribi::Coordinat2D ribi::CalcCenter(const std::vector<ribi::Coordinat2D>& points) noexcept
{
  Coordinat2D sum;
  for (const auto& point: points)
  {
    sum += point;
  }
  const double n { static_cast<double>(points.size()) };
  const Coordinat2D center(
    sum.GetX() / n,
    sum.GetY() / n
  );
  return center;
}

double ribi::Distance(const Coordinat2D& lhs,const Coordinat2D& rhs) noexcept
{
  const double dx = lhs.GetX() - rhs.GetX();
  const double dy = lhs.GetY() - rhs.GetY();
  return std::sqrt(
      (dx * dx)
    + (dy * dy)
  );
}

double ribi::Length(const Coordinat2D& v) noexcept
{
  return std::sqrt( (v.GetX() * v.GetX()) + (v.GetY() * v.GetY()));
}

ribi::Coordinat2D ribi::Scale(
  const double scalar,
  const ribi::Coordinat2D& v
) noexcept
{
  assert(scalar != 0.0);
  const ribi::Coordinat2D c(
    v.GetX() / scalar,
    v.GetY() / scalar
  );
  return c;
}

#ifndef NDEBUG
void ribi::Coordinat2D::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Coordinat2D::Test");
  TRACE("Finished ribi::Coordinat2D::Test successfully");
}
#endif

ribi::Coordinat2D ribi::operator-(
  const Coordinat2D& v1,
  const Coordinat2D& v2) noexcept
{
  return {
    v1.GetX()-v2.GetX(),
    v1.GetY()-v2.GetY()
  };

}

ribi::Coordinat2D ribi::operator+(
  const Coordinat2D& v1,
  const Coordinat2D& v2) noexcept
{
  return {
    v1.GetX()+v2.GetX(),
    v1.GetY()+v2.GetY()
  };
}

ribi::Coordinat2D ribi::operator*(
  const double scalar,
  const Coordinat2D& v) noexcept
{
  return Coordinat2D(
    scalar * v.GetX(),
    scalar * v.GetY()
  );
}

bool ribi::operator==(const Coordinat2D& lhs, const Coordinat2D& rhs) noexcept
{
  return lhs.GetX() == rhs.GetX()
    && lhs.GetY() == rhs.GetY();
}

bool ribi::operator<(const Coordinat2D& lhs, const Coordinat2D& rhs) noexcept
{
  if (lhs.GetX() < rhs.GetX()) return true;
  if (lhs.GetX() > rhs.GetX()) return false;
  if (lhs.GetY() < rhs.GetY()) return true;
  if (lhs.GetY() > rhs.GetY()) return false;
  return false;
}


std::ostream& ribi::operator<<(std::ostream& os, const Coordinat2D& n) noexcept
{
  std::stringstream s;
  s
    << ribi::xml::ToXml("x",n.GetX())
    << ribi::xml::ToXml("y",n.GetY())
  ;
  os << ribi::xml::ToXml("coordinat2d",s.str());
  return os;
}

#endif
