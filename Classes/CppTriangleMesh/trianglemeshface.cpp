#include "trianglemeshface.h"

#include <algorithm>
#include <fstream>
#include <set>

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
    m_type{}
{
  #ifndef NDEBUG
  Test();
  #endif
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

void ribi::trim::Face::AddBelongsTo(boost::weak_ptr<const Cell> cell) const
{
  assert(cell.lock());
  m_belongs_to.push_back(cell);
  assert(m_belongs_to.size() <= 2);
  assert(
       (m_belongs_to.size() == 1)
    || (m_belongs_to.size() == 2 && m_belongs_to[0].lock() != m_belongs_to[1].lock())
  );
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
  //assert(m_coordinats.empty()); //This is done multiple times in debugging
  m_coordinats = ExtractCoordinats(m_points);
}

const boost::shared_ptr<const ribi::trim::Cell> ribi::trim::Face::GetNeighbour() const noexcept
{
  PROFILE_FUNC();
  assert(m_belongs_to.size() <= 2);
  m_belongs_to.erase(
    std::remove_if(
      m_belongs_to.begin(),m_belongs_to.end(),
      [](const boost::weak_ptr<const Cell> cell)
      {
        return !cell.lock();
      }
    ),
    m_belongs_to.end()
  );
  boost::shared_ptr<const Cell> p;
  if (m_belongs_to.size() < 2) return p;

  assert(m_belongs_to[0].lock() != m_belongs_to[1].lock());

  p = m_belongs_to[1].lock();
  assert(p);
  return p;
}

const boost::shared_ptr<const ribi::trim::Cell> ribi::trim::Face::GetOwner() const noexcept
{
  PROFILE_FUNC();
  assert(m_belongs_to.size() <= 2);
  m_belongs_to.erase(
    std::remove_if(
      m_belongs_to.begin(),m_belongs_to.end(),
      [](const boost::weak_ptr<const Cell> cell)
      {
        return !cell.lock();
      }
    ),
    m_belongs_to.end()
  );
  boost::shared_ptr<const Cell> p {
    m_belongs_to[0].lock()
  };
  assert(p);
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

#ifndef NDEBUG
void ribi::trim::Face::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::Face::Test");
  TRACE("Finished ribi::trim::Face::Test successfully");
}
#endif










const std::set<ribi::Coordinat3D> ribi::trim::ExtractCoordinats(const ribi::trim::Face& face)
{
  face.DoExtractCoordinats();
  return face.GetCoordinats();
}

bool ribi::trim::IsHorizontal(const ribi::trim::Face& face) noexcept
{
  const bool answer_1 = face.GetOrientation() == FaceOrientation::horizontal;

  const std::set<ribi::Coordinat3D> coordinats { ExtractCoordinats(face) };

  typedef std::set<ribi::Coordinat3D>::iterator Iterator;
  typedef std::pair<Iterator,Iterator> Pair;
  const Pair xs {
    std::minmax_element(coordinats.begin(),coordinats.end(),
      [](const ribi::Coordinat3D& lhs,const ribi::Coordinat3D& rhs)
      {
        return lhs.GetX() < rhs.GetX();
      }
    )
  };

  const double dx { std::abs((*xs.first).GetX() - (*xs.second).GetX()) };

  const Pair ys {
    std::minmax_element(coordinats.begin(),coordinats.end(),
      [](const ribi::Coordinat3D& lhs,const ribi::Coordinat3D& rhs)
      {
        return lhs.GetY() < rhs.GetY();
      }
    )
  };

  const double dy { std::abs((*ys.first).GetY() - (*ys.second).GetY()) };

  const Pair zs {
    std::minmax_element(coordinats.begin(),coordinats.end(),
      [](const ribi::Coordinat3D& lhs,const ribi::Coordinat3D& rhs)
      {
        return lhs.GetZ() < rhs.GetZ();
      }
    )
  };
  const double dz { std::abs((*zs.first).GetZ() - (*zs.second).GetZ()) };

  const bool answer_2 { dz * 1000.0 < dx && dz * 1000.0 < dy };

  assert(answer_1 == answer_2);
  return answer_1;
}

bool ribi::trim::IsVertical(const ribi::trim::Face& face) noexcept
{
  const bool answer_1 = face.GetOrientation() == FaceOrientation::vertical;
  const bool answer_2 = !IsHorizontal(face);
  assert(answer_1 == answer_2);
  return answer_1;
}

bool ribi::trim::operator==(const ribi::trim::Face& lhs, const ribi::trim::Face& rhs)
{
  return
       lhs.GetPoints() == rhs.GetPoints()
    && lhs.GetOrientation() == rhs.GetOrientation()
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
