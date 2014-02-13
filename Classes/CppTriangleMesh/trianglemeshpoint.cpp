#include "trianglemeshpoint.h"
#include <iostream>

#include "trianglemeshface.h"
#include "trace.h"
#include "xml.h"

ribi::trim::Point::Point(
  const boost::shared_ptr<const ribi::ConstCoordinat2D> coordinat,
  const std::string boundary_type
)
  : m_boundary_type(boundary_type),
    m_connected{},
    m_coordinat(coordinat),
    m_index{-1},
    m_z{}
{
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

bool ribi::trim::operator==(const ribi::trim::Point& lhs, const ribi::trim::Point& rhs)
{
  return lhs.GetCoordinat() == rhs.GetCoordinat()
    && lhs.GetBoundaryType() == rhs.GetBoundaryType()
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
    << ribi::xml::ToXml("boundary",boost::lexical_cast<std::string>(n.GetBoundaryType()))
  ;
  return os;
}
