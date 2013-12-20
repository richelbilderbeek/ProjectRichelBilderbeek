#include "coordinat3d.h"

#include <cmath>
#include "xml.h"

ribi::Coordinat3D::Coordinat3D(const double x, const double y, const double z)
  : m_co( { x,y,z } )
{

}

ribi::Coordinat3D& ribi::Coordinat3D::operator+=(const Coordinat3D& rhs) noexcept
{
  m_co[0] += rhs.GetX();
  m_co[1] += rhs.GetY();
  m_co[2] += rhs.GetZ();
  return *this;
}

ribi::Coordinat3D& ribi::Coordinat3D::operator-=(const Coordinat3D& rhs) noexcept
{
  m_co[0] -= rhs.GetX();
  m_co[1] -= rhs.GetY();
  m_co[2] -= rhs.GetZ();
  return *this;
}

ribi::Coordinat3D& ribi::Coordinat3D::operator/=(const double f)
{
  assert(f != 0.0);
  m_co[0] /= f;
  m_co[1] /= f;
  m_co[2] /= f;
  return *this;
}

ribi::Coordinat3D& ribi::Coordinat3D::operator*=(const double f) noexcept
{
  m_co[0] *= f;
  m_co[1] *= f;
  m_co[2] *= f;
  return *this;
}

double ribi::Distance(const Coordinat3D& lhs,const Coordinat3D& rhs)
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

double ribi::Length(const Coordinat3D& v)
{
  return std::sqrt(
      (v.GetX() * v.GetX())
    + (v.GetY() * v.GetY())
    + (v.GetZ() * v.GetZ())
  );
}

const ribi::Coordinat3D ribi::operator-(
  const Coordinat3D& v1,
  const Coordinat3D& v2)
{
  return Coordinat3D(
    v1.GetX()-v2.GetX(),
    v1.GetY()-v2.GetY(),
    v1.GetZ()-v2.GetZ()
  );
}

const ribi::Coordinat3D ribi::operator+(
  const Coordinat3D& v1,
  const Coordinat3D& v2)
{
  return Coordinat3D(
    v1.GetX()+v2.GetX(),
    v1.GetY()+v2.GetY(),
    v1.GetZ()+v2.GetZ()
  );
}

const ribi::Coordinat3D ribi::operator/(
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

const ribi::Coordinat3D ribi::operator*(
  const Coordinat3D& c,
  const double f) noexcept
{
  return Coordinat3D(
    c.GetX() * f,
    c.GetY() * f,
    c.GetZ() * f
  );
}


bool ribi::operator==(const Coordinat3D& lhs, const Coordinat3D& rhs)
{
  return
       lhs.GetX() == rhs.GetX()
    && lhs.GetY() == rhs.GetY()
    && lhs.GetZ() == rhs.GetZ();
}


std::ostream& ribi::operator<<(std::ostream& os, const Coordinat3D& n)
{
  std::stringstream s;
  s
    << ribi::xml::ToXml("x",n.GetX())
    << ribi::xml::ToXml("y",n.GetY())
    << ribi::xml::ToXml("z",n.GetZ());
  os << ribi::xml::ToXml("coordinat3d",s.str());
  return os;
}
