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
#include "trianglemeshpoint.h"
#include "trianglemeshfacefactory.h"
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

const boost::shared_ptr<const ribi::trim::Point> ribi::trim::Edge::GetPoint(const int index) const noexcept
{
  PROFILE_FUNC();
  assert(index >= 0);
  assert(index < static_cast<int>(GetPoints().size()));
  return GetPoints()[index];
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
  TRACE("Finished ribi::trim::Edge::Test successfully");
}
#endif

bool ribi::trim::operator==(const ribi::trim::Edge& lhs, const ribi::trim::Edge& rhs)
{
  return
       lhs.GetPoints() == rhs.GetPoints()
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
    const int n_points { static_cast<int>(f.GetPoints().size()) };
    for (int i=0; i!=n_points; ++i)
    {
      s << ribi::xml::ToXml("point" + boost::lexical_cast<std::string>(i),*f.GetPoint(i));
    }
    os << ribi::xml::ToXml("points",s.str());
  }

  return os;
}
