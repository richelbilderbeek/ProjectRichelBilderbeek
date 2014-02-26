#include "trianglemeshedge.h"

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
}

void ribi::trim::Edge::AddBelongsTo(boost::weak_ptr<const Face> face) const
{
  assert(face.lock());
  m_belongs_to.push_back(face);
}

/*
const boost::shared_ptr<const ribi::trim::Point> ribi::trim::Edge::GetPoint(const int index) const noexcept
{
  PROFILE_FUNC();
  assert(index >= 0);
  assert(index < static_cast<int>(GetPoints().size()));
  return GetPoints()[index];
}
*/

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
      assert(CalcWindingHorizontal(const_edges) == winding);
    }
  }
  TRACE("Finished ribi::trim::Edge::Test successfully");
}
#endif

bool ribi::trim::operator==(const ribi::trim::Edge& lhs, const ribi::trim::Edge& rhs)
{
  return
       lhs.GetFrom() == rhs.GetFrom()
    && lhs.GetTo()   == rhs.GetTo()
  ;
}

bool ribi::trim::operator!=(const ribi::trim::Edge& lhs, const ribi::trim::Edge& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::trim::operator<<(std::ostream& os, const ribi::trim::Edge& f)
{
  os
    << ribi::xml::ToXml("edge_index",f.GetIndex())
  ;
  {
    std::stringstream s;
    s << ribi::xml::ToXml("from",*f.GetFrom());
    s << ribi::xml::ToXml("to",*f.GetTo());
    os << ribi::xml::ToXml("points",s.str());
  }

  return os;
}
