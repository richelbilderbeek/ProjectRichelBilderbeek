#include "coordinat2d.h"

#include <array>
#include <iostream>

#include "xml.h"

ribi::Coordinat2D::Coordinat2D(const double x, const double y)
  : m_co{ { x,y } }
{
}

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

double ribi::operator*(const Coordinat2D& v1,const Coordinat2D& v2)
{
  return
      ( v1.GetX() * v2.GetX())
    + ( v1.GetY() * v2.GetY())
  ;
}

double ribi::Length(const Coordinat2D& v)
{
  return std::sqrt( (v.GetX() * v.GetX()) + (v.GetY() * v.GetY()));
}

const ribi::Coordinat2D ribi::operator-(
  const Coordinat2D& v1,
  const Coordinat2D& v2)
{
  return {
    v1.GetX()-v2.GetX(),
    v1.GetY()-v2.GetY()
  };

}

const ribi::Coordinat2D ribi::operator+(
  const Coordinat2D& v1,
  const Coordinat2D& v2)
{
  return {
    v1.GetX()+v2.GetX(),
    v1.GetY()+v2.GetY()
  };
}

const ribi::Coordinat2D ribi::operator*(
  const double scalar,
  const Coordinat2D& v)
{
  return Coordinat2D(
    scalar * v.GetX(),
    scalar * v.GetY()
  );
}

bool ribi::operator==(const Coordinat2D& lhs, const Coordinat2D& rhs)
{
  return lhs.GetX() == rhs.GetX()
    && lhs.GetY() == rhs.GetY();
}


std::ostream& ribi::operator<<(std::ostream& os, const Coordinat2D& n)
{
  std::stringstream s;
  s
    << ribi::xml::ToXml("x",n.GetX())
    << ribi::xml::ToXml("y",n.GetY())
  ;
  os << ribi::xml::ToXml("coordinat2d",s.str());
  return os;
}
