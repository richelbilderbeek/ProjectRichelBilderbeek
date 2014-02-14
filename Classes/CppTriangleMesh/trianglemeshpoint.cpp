#include "trianglemeshpoint.h"
#include <iostream>

#include "Shiny.h"

#include "trianglemeshface.h"
#include "trace.h"
#include "xml.h"

ribi::trim::Point::Point(
  const boost::shared_ptr<const ribi::ConstCoordinat2D> coordinat
)
  : m_connected{},
    m_coordinat(coordinat),
    m_index{-1},
    m_z{}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_coordinat == coordinat
    && "A shallow copy please");
}

void ribi::trim::Point::AddConnected(const boost::weak_ptr<Face> face)
{
  m_connected.insert(face);
}

bool ribi::trim::Point::CanGetZ() const noexcept
{
  return m_z.get();
}

const std::vector<boost::shared_ptr<ribi::trim::Point>> ribi::trim::Point::CreateTestPrism() noexcept
{
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_a {
    new ribi::ConstCoordinat2D(0.0,0.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_b {
    new ribi::ConstCoordinat2D(1.0,0.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_c {
    new ribi::ConstCoordinat2D(0.0,1.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_d {
    new ribi::ConstCoordinat2D(0.0,0.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_e {
    new ribi::ConstCoordinat2D(1.0,0.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_f {
    new ribi::ConstCoordinat2D(0.0,1.0)
  };

  const boost::shared_ptr<Point> a {
    new Point(co_a)
  };
  const boost::shared_ptr<Point> b {
    new Point(co_b)
  };
  const boost::shared_ptr<Point> c {
    new Point(co_c)
  };
  const boost::shared_ptr<Point> d {
    new Point(co_d)
  };
  const boost::shared_ptr<Point> e {
    new Point(co_e)
  };
  const boost::shared_ptr<Point> f {
    new Point(co_f)
  };
  a->SetZ(0.0 * boost::units::si::meter);
  b->SetZ(0.0 * boost::units::si::meter);
  c->SetZ(0.0 * boost::units::si::meter);
  d->SetZ(1.0 * boost::units::si::meter);
  e->SetZ(1.0 * boost::units::si::meter);
  f->SetZ(1.0 * boost::units::si::meter);

  const std::vector<boost::shared_ptr<Point>> prism {
    a,b,c,d,e,f
  };
  return prism;
}

const boost::units::quantity<boost::units::si::length> ribi::trim::Point::GetZ() const noexcept
{
  assert(CanGetZ());
  return *m_z;
}

void ribi::trim::Point::SetZ(const boost::units::quantity<boost::units::si::length> z) const noexcept
{
  assert(!m_z&& "m_z can be set exactly once");
  boost::shared_ptr<boost::units::quantity<boost::units::si::length>> p {
    new boost::units::quantity<boost::units::si::length>(z)
  };
  m_z = p;
  assert(m_z);
}

#ifndef NDEBUG
void ribi::trim::Point::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::Point::Test");
  TRACE("Finished ribi::trim::Point::Test successfully");
}
#endif







const std::set<ribi::Coordinat3D> ribi::trim::ExtractCoordinats(
  const std::vector<boost::shared_ptr<Point>>& points
)
{
  PROFILE_FUNC();
  std::set<ribi::Coordinat3D> s;
  for (const auto point: points)
  {
    if (!point->CanGetZ())
    {
      TRACE("Extract these coordinats later: the Face must be assigned to a Layer first");
    }
    assert(point->CanGetZ());
    const ribi::Coordinat3D c(
      point->GetCoordinat()->GetX(),
      point->GetCoordinat()->GetY(),
      point->GetZ().value()
    );
    s.insert(s.begin(),c);
  }

  return s;
}


bool ribi::trim::operator==(const ribi::trim::Point& lhs, const ribi::trim::Point& rhs)
{
  return lhs.GetCoordinat() == rhs.GetCoordinat()
  ;
}

bool ribi::trim::operator!=(const ribi::trim::Point& lhs, const ribi::trim::Point& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::trim::operator<<(std::ostream& os, const Point& n)
{
  os
    << n.GetCoordinat()
  ;
  return os;
}
