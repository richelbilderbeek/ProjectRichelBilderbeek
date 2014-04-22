#include "trianglemeshpoint.h"

#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "geometry.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::trim::Point::Point(
  const boost::shared_ptr<const Coordinat2D> coordinat,
  const int index,
  const PointFactory&
) :
    #ifdef TRIANGLEMESH_USE_SIGNALS2
    m_signal_destroyed{},
    #endif
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
  assert(m_coordinat == coordinat && "A shallow copy please");
  assert(!std::isnan(get<0>(*m_coordinat)));
  assert(!std::isnan(get<1>(*m_coordinat)));
}

ribi::trim::Point::~Point() noexcept
{
  #ifdef TRIANGLEMESH_USE_SIGNALS2
  m_signal_destroyed(this);
  #endif
}

#ifdef TRIANGLEMESH_USE_SIGNALS2
void ribi::trim::Point::AddConnected(const boost::shared_ptr<Face>& face)
{
  //assert(face.lock().get() != nullptr);
  assert(face);
  m_connected.push_back(face);

  face->m_signal_destroyed.connect(
    boost::bind(&ribi::trim::Point::OnFaceDestroyed,this,boost::lambda::_1)
  );
}
#else
void ribi::trim::Point::AddConnected(const boost::weak_ptr<Face>& face)
{
  assert(face.lock().get() != nullptr);
  m_connected.push_back(face);
}
#endif //~#ifdef TRIANGLEMESH_USE_SIGNALS2

ribi::trim::Point::Coordinat3D ribi::trim::Point::GetCoordinat3D() const noexcept
{
  assert(!std::isnan(boost::geometry::get<0>(*GetCoordinat())));
  assert(!std::isnan(boost::geometry::get<1>(*GetCoordinat())));
  assert(!CanGetZ() || !std::isnan(GetZ().value()));
  
  return Geometry().CreatePoint(
    boost::geometry::get<0>(*GetCoordinat()),
    boost::geometry::get<1>(*GetCoordinat()),
    CanGetZ() ? GetZ().value() : 0.0
  );
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

void ribi::trim::Point::OnFaceDestroyed(const ribi::trim::Face * const face) noexcept
{
  assert(1==2);
  #ifdef TRIANGLEMESH_USE_SIGNALS2
  const auto new_end = std::remove_if(m_connected.begin(),m_connected.end(),
    [face](const boost::shared_ptr<Face>& connected) { return connected.get() == face; }
  );
  #else
  const auto new_end = std::remove_if(m_connected.begin(),m_connected.end(),
    [face](const boost::weak_ptr<Face>& connected) { return connected.lock().get() == face; }
  );
  #endif //~#ifdef TRIANGLEMESH_USE_SIGNALS2
  m_connected.erase(new_end,m_connected.end());
}

std::function<
    bool(
      const boost::shared_ptr<const ribi::trim::Face>& lhs,
      const boost::shared_ptr<const ribi::trim::Face>& rhs
    )
  >
  ribi::trim::Point::OrderByIndex() const noexcept
{
  return [](const boost::shared_ptr<const Face>& lhs, const boost::shared_ptr<const Face>& rhs)
  {
    assert(lhs);
    assert(rhs);
    assert(lhs->GetIndex() != rhs->GetIndex());
    return lhs->GetIndex() < rhs->GetIndex();
  };
}

void ribi::trim::Point::SetZ(const boost::units::quantity<boost::units::si::length> z) const noexcept
{
  if (m_z)
  {
    assert(*m_z == z);
    return;
  }
  //assert(!m_z&& "m_z can be set exactly once");
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
    #ifdef TRIANGLEMESH_USE_SIGNALS2
    assert(face);
    face->CheckOrientation();
    #else
    assert(face.lock());
    face.lock()->CheckOrientation();
    #endif //~#ifdef TRIANGLEMESH_USE_SIGNALS2
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

std::string ribi::trim::Point::ToStr() const noexcept
{
  
  std::stringstream s;
  s
    << Geometry().ToStr(GetCoordinat3D())
    << " (index: "
    << GetIndex()
    << ")";
  ;
  return s.str();
}

std::string ribi::trim::Point::ToXml() const noexcept
{
  
  std::stringstream s;
  s
    << ribi::xml::ToXml("point_index",GetIndex())
    << Helper().ToXml(*GetCoordinat())
    << ribi::xml::ToXml("z", CanGetZ()
      ?  boost::lexical_cast<std::string>(GetZ().value())
      : ""
      )
  ;
  return s.str();
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
  os << n.ToStr();
  return os;
}
