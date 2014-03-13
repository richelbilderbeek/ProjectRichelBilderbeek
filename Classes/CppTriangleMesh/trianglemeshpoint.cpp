#include "trianglemeshpoint.h"
#include <iostream>

#include "Shiny.h"

#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trace.h"
#include "xml.h"

ribi::trim::Point::Point(
  const boost::shared_ptr<const ConstCoordinat2D> coordinat,
  const int index,
  const PointFactory&
)
  : m_belongs_to{},
    m_connected{},
    m_coordinat(coordinat),
    m_index{index},
    m_z{}
{
  #ifndef NDEBUG
  Test();
  #endif
  using boost::geometry::get;
  assert(m_coordinat);
  assert(m_coordinat == coordinat
    && "A shallow copy please");
  assert(!std::isnan(get<0>(*m_coordinat)));
  assert(!std::isnan(get<1>(*m_coordinat)));
}

void ribi::trim::Point::AddBelongsTo(const boost::weak_ptr<Edge> edge)
{
  m_belongs_to.insert(edge);
}

void ribi::trim::Point::AddConnected(const boost::weak_ptr<Face> face)
{
  m_connected.insert(face);
}

bool ribi::trim::Point::CanGetZ() const noexcept
{
  return m_z.get();
}



const boost::units::quantity<boost::units::si::length> ribi::trim::Point::GetZ() const noexcept
{
  if (!CanGetZ())
  {
    TRACE("BREAK");
  }
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

  //Let the Point check for themselves for being horizontal or vertical
  #ifndef NDEBUG
  if (GetConnected().empty()) return;
  for (auto face: GetConnected())
  {
    assert(face.lock());
    face.lock()->CheckOrientation();
  }
  #endif
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
    << ribi::xml::ToXml("point_index",n.GetIndex())
    << Helper().ToXml(*n.GetCoordinat())
  ;
  os << ribi::xml::ToXml("z", n.CanGetZ()
    ?  boost::lexical_cast<std::string>(n.GetZ().value())
    : ""
  );
  return os;
}
