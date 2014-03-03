#include "constcoordinat2d.h"

#include <array>
#include <iostream>

#include "trace.h"
#include "xml.h"

ribi::ConstCoordinat2D::ConstCoordinat2D(const double x, const double y) noexcept
  : m_co{ { x,y } }
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::DotProduct(
  const boost::shared_ptr<const ConstCoordinat2D> v1,
  const boost::shared_ptr<const ConstCoordinat2D> v2
) noexcept
{
  return
      ( v1->GetX() * v2->GetX())
    + ( v1->GetY() * v2->GetY())
  ;
}

double ribi::Distance(const ConstCoordinat2D& lhs,const ConstCoordinat2D& rhs) noexcept
{
  const double dx = lhs.GetX() - rhs.GetX();
  const double dy = lhs.GetY() - rhs.GetY();
  return std::sqrt(
      (dx * dx)
    + (dy * dy)
  );
}

double ribi::Length(const boost::shared_ptr<const ConstCoordinat2D> v) noexcept
{
  const double dx = v->GetX();
  const double dy = v->GetY();
  return std::sqrt((dx*dx)+(dy*dy));
}

boost::shared_ptr<const ribi::ConstCoordinat2D> ribi::Scale(
  const double scalar,
  const boost::shared_ptr<const ConstCoordinat2D> v) noexcept
{
  const boost::shared_ptr<const ConstCoordinat2D> p(
    new ConstCoordinat2D(
      scalar * v->GetX(),
      scalar * v->GetY()
    )
  );
  assert(p);
  return p;
}

#ifndef NDEBUG
void ribi::ConstCoordinat2D::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ConstCoordinat2D::Test");
  TRACE("Finished ribi::ConstCoordinat2D::Test successfully");
}
#endif

boost::shared_ptr<const ribi::ConstCoordinat2D> ribi::operator-(
  const boost::shared_ptr<const ConstCoordinat2D> v1,
  const boost::shared_ptr<const ConstCoordinat2D> v2) noexcept
{
  const boost::shared_ptr<const ConstCoordinat2D> p(
    new ConstCoordinat2D(
      v1->GetX() - v2->GetX(),
      v1->GetY() - v2->GetY()
    )
  );
  assert(p);
  return p;
}

boost::shared_ptr<const ribi::ConstCoordinat2D> ribi::operator+(
  const boost::shared_ptr<const ConstCoordinat2D> v1,
  const boost::shared_ptr<const ConstCoordinat2D> v2) noexcept
{
  const boost::shared_ptr<const ConstCoordinat2D> p(
    new ConstCoordinat2D(
      v1->GetX() + v2->GetX(),
      v1->GetY() + v2->GetY()
    )
  );
  assert(p);
  return p;
}


bool ribi::operator==(const ConstCoordinat2D& lhs, const ConstCoordinat2D& rhs) noexcept
{
  return lhs.GetX() == rhs.GetX()
      && lhs.GetY() == rhs.GetY();
}

bool ribi::operator<(const ConstCoordinat2D& lhs, const ConstCoordinat2D& rhs) noexcept
{
  if (lhs.GetX() < rhs.GetX()) return true;
  if (lhs.GetX() > rhs.GetX()) return false;
  if (lhs.GetY() < rhs.GetY()) return true;
  if (lhs.GetY() > rhs.GetY()) return false;
  return false;
}


std::ostream& ribi::operator<<(std::ostream& os, const ConstCoordinat2D& n) noexcept
{
  std::stringstream s;
  s
    << ribi::xml::ToXml("x",n.GetX())
    << ribi::xml::ToXml("y",n.GetY())
  ;
  os << ribi::xml::ToXml("coordinat2d",s.str());
  return os;
}
