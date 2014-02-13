#include "trianglemeshface.h"

#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>

#include "Shiny.h"

#include "coordinat3d.h"
#include "trianglemeshpoint.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::trim::Face::Face(
  const std::vector<boost::shared_ptr<Point>>& any_points,
  const FaceOrientation any_orientation,
  const boost::weak_ptr<const Face> face_below
  )
  : m_belongs_to{},
    m_coordinats{},
    m_face_below(face_below),
    m_index{-1},
    m_orientation(any_orientation),
    m_points(any_points),
    m_type("internalMesh")
{
  PROFILE_FUNC();
  #ifndef NDEBUG
  if (m_orientation == FaceOrientation::vertical) { assert(m_face_below.expired()); }
  //Must have a Face below if not a base Face
  if (m_orientation == FaceOrientation::horizontal)
  {
    const int n_points = static_cast<int>(m_points.size());
    assert(n_points > 2);
    for (int i=0; i!=n_points; ++i)
    {
      assert(m_points[i]);
    }
    if (m_points[0]->CanGetZ())
    {
      const auto z = m_points[0]->GetZ();
      for (const auto p: m_points)
      {
        assert(p->CanGetZ());
        assert(z == p->GetZ());
      }
    }
  }
  #endif
}

bool ribi::trim::Face::CanExtractCoordinats() const noexcept
{
  for (const auto point: m_points)
  {
    if (!point->CanGetZ()) return false;
  }
  return true;
}

void ribi::trim::Face::DoExtractCoordinats() const
{
  PROFILE_FUNC();
  assert(CanExtractCoordinats());
  assert(m_coordinats.empty());
  m_coordinats = ExtractCoordinats(m_points);
}

const std::set<ribi::Coordinat3D> ribi::trim::Face::ExtractCoordinats(
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

const boost::shared_ptr<const ribi::trim::Cell> ribi::trim::Face::GetNeighbour() const noexcept
{
  PROFILE_FUNC();
  boost::shared_ptr<const Cell> p;
  if (m_belongs_to.size() < 2) return p;
  p = m_belongs_to[1].lock();
  return p;
}

const boost::shared_ptr<const ribi::trim::Cell> ribi::trim::Face::GetOwner() const noexcept
{
  PROFILE_FUNC();
  boost::shared_ptr<const Cell> p;
  if (m_belongs_to.empty()) return p;
  p = m_belongs_to[0].lock();
  if (!p && m_belongs_to.size() == 2)
  {
    std::swap(m_belongs_to[0],m_belongs_to[1]);
    m_belongs_to.pop_back();
  }
  p = m_belongs_to[0].lock();
  return p;
}


const boost::shared_ptr<const ribi::trim::Point> ribi::trim::Face::GetPoint(const int index) const noexcept
{
  PROFILE_FUNC();
  assert(index >= 0);
  assert(index < static_cast<int>(GetPoints().size()));
  return GetPoints()[index];
}

void ribi::trim::Face::ReversePoints() noexcept
{
  PROFILE_FUNC();
  std::reverse(m_points.begin(),m_points.end());
}

bool ribi::trim::operator==(const ribi::trim::Face& lhs, const ribi::trim::Face& rhs)
{
  return
       lhs.GetPoints() == rhs.GetPoints()
    && lhs.GetOrientation() == rhs.GetOrientation()
    //&& lhs.GetOwner() == rhs.GetOwner()
    //&& lhs.GetNeighbour() == rhs.GetNeighbour()
  ;
}

bool ribi::trim::operator!=(const ribi::trim::Face& lhs, const ribi::trim::Face& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::trim::operator<<(std::ostream& os, const ribi::trim::Face& f)
{
  os
    << ribi::xml::ToXml("points",std::begin(f.GetPoints()),std::end(f.GetPoints()))
    << ribi::xml::ToXml("orientation",static_cast<int>(f.GetOrientation()))
  ;
  return os;
}
