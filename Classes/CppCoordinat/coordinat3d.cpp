#include "coordinat3d.h"

#include <array>
#include <cmath>

#include "trace.h"
#include "xml.h"

ribi::Coordinat3D::Coordinat3D(const double x, const double y, const double z) noexcept
  : m_co{ { x,y,z } }
{
  #ifndef NDEBUG
  Test();
  #endif
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

ribi::Coordinat3D ribi::CalcCenter(const std::vector<ribi::Coordinat3D>& points) noexcept
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

ribi::Coordinat3D ribi::CalcCrossProduct(
  const ribi::Coordinat3D& a,
  const ribi::Coordinat3D& b
) noexcept
{
  return ribi::Coordinat3D(
    (a.GetY() * b.GetZ()) - (a.GetZ() * b.GetY()),
    (a.GetZ() * b.GetX()) - (a.GetX() * b.GetZ()),
    (a.GetX() * b.GetY()) - (a.GetY() * b.GetX())
  );
}

double ribi::CalcDotProduct(
  const ribi::Coordinat3D& a,
  const ribi::Coordinat3D& b
) noexcept
{
  return
      (a.GetX() * b.GetX())
    + (a.GetY() * b.GetY())
    + (a.GetZ() * b.GetZ());
}

ribi::Coordinat3D ribi::CalcNormal(
  const ribi::Coordinat3D& a,
  const ribi::Coordinat3D& b,
  const ribi::Coordinat3D& c
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
void ribi::Coordinat3D::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Coordinat3D::Test");
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
    TRACE(normal);
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
    TRACE(normal);
    const Coordinat3D expected(0.0,0.0,1.0);
    assert(std::abs(normal.GetX() - expected.GetX()) < 0.0001);
    assert(std::abs(normal.GetY() - expected.GetY()) < 0.0001);
    assert(std::abs(normal.GetZ() - expected.GetZ()) < 0.0001);
  }

  TRACE("Finished ribi::Coordinat3D::Test successfully");
}
#endif

ribi::Coordinat3D ribi::operator-(
  const Coordinat3D& v1,
  const Coordinat3D& v2) noexcept
{
  return Coordinat3D(
    v1.GetX()-v2.GetX(),
    v1.GetY()-v2.GetY(),
    v1.GetZ()-v2.GetZ()
  );
}

ribi::Coordinat3D ribi::operator+(
  const Coordinat3D& v1,
  const Coordinat3D& v2) noexcept
{
  return Coordinat3D(
    v1.GetX()+v2.GetX(),
    v1.GetY()+v2.GetY(),
    v1.GetZ()+v2.GetZ()
  );
}

ribi::Coordinat3D ribi::operator/(
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

ribi::Coordinat3D ribi::operator*(
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
