#include "trianglemeshedge.h"

#ifdef USE_TRIANGLEMESHEDGE

#include <algorithm>
#include <fstream>
#include <set>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>

#include "Shiny.h"

#include "geometry.h"
#include "trianglemeshedgefactory.h"
#include "trianglemeshpoint.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshwindings.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::trim::Edge::Edge(
  const std::array<boost::shared_ptr<Point>,2>& any_points,
  const int index,
  const EdgeFactory&
  )
  : m_belongs_to{},
    m_index{index},
    m_points(any_points)
{
  #ifndef NDEBUG
  Test();
  #endif
  PROFILE_FUNC();
  assert(any_points[0] != any_points[1]);
}

void ribi::trim::Edge::AddBelongsTo(boost::weak_ptr<const Face> face) const
{
  assert(face.lock());
  m_belongs_to.push_back(face);
}

void ribi::trim::Edge::Reverse() noexcept
{
  std::swap(m_points[0],m_points[1]);
}

#ifndef NDEBUG
void ribi::trim::Edge::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::Edge::Test");
  {
    for (Winding winding: Windings().GetAll())
    {
      const std::vector<boost::shared_ptr<Edge>> edges {
        EdgeFactory().CreateTestTriangle(winding)
      };
      assert(std::count(edges.begin(),edges.end(),nullptr) == 0);
      const std::vector<boost::shared_ptr<const Edge>> const_edges {
        AddConst(edges)
      };
      TRACE(Windings().ToStr(winding));
      assert(Helper().CalcWindingHorizontal(const_edges) == winding);
    }
  }
  TRACE("Finished ribi::trim::Edge::Test successfully");
}
#endif

std::string ribi::trim::Edge::ToStr() const noexcept
{

  std::stringstream s;
  s
    << Geometry().ToStr(GetFrom()->GetCoordinat3D())
    << " -> "
    << Geometry().ToStr(GetTo()->GetCoordinat3D())
    << " (index: "
    << GetIndex()
    << ")";
  ;
  return s.str();
}

std::string ribi::trim::Edge::ToXml() const noexcept
{
  std::stringstream s;
  s
    << ribi::xml::ToXml("edge_index",GetIndex())
  ;
  {
    std::stringstream t;
    t << ribi::xml::ToXml("from",*GetFrom());
    t << ribi::xml::ToXml("to",*GetTo());
    s << ribi::xml::ToXml("points",t.str());
  }

  return ribi::xml::ToXml("edge",s.str());
}

bool ribi::trim::operator==(const ribi::trim::Edge& lhs, const ribi::trim::Edge& rhs) noexcept
{
  return
       lhs.GetFrom() == rhs.GetFrom()
    && lhs.GetTo()   == rhs.GetTo()
  ;
}

bool ribi::trim::operator!=(const ribi::trim::Edge& lhs, const ribi::trim::Edge& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::trim::operator<<(std::ostream& os, const ribi::trim::Edge& f) noexcept
{
  os << f.ToStr();
  return os;
}

#endif //~USE_TRIANGLEMESHEDGE
