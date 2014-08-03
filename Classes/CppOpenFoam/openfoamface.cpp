#include "openfoamface.h"

#include <cassert>
#include <ostream>

#include "openfoamcell.h"
#include "openfoamhelper.h"
#include "trace.h"

ribi::foam::Face::Face(
  const boost::shared_ptr<Cell>& neighbour,
  const boost::shared_ptr<Cell>& owner,
  const std::vector<boost::shared_ptr<Coordinat3D>>& points
) noexcept
  : m_neighbour(neighbour),
    m_owner(owner),
    m_points(points)
{
  #ifndef NDEBUG
  assert(!m_neighbour);
  assert(!m_owner);
  for (const auto& p: m_points) { assert(p); }
  #endif
}

void ribi::foam::Face::AssignNeighbour(const boost::shared_ptr<ribi::foam::Cell> neighbour) noexcept
{
  assert(!m_neighbour && "neighbour can only be assigned once");
  assert(neighbour);
  m_neighbour = neighbour;
}

void ribi::foam::Face::AssignOwner(const boost::shared_ptr<ribi::foam::Cell> owner) noexcept
{
  assert(!m_owner && "Can only assign owner once");
  assert(owner);

  m_owner = owner;
}

boost::shared_ptr<ribi::foam::Cell> ribi::foam::Face::GetOwner() noexcept
{
  assert( (m_owner || !m_owner) && "Allow Face to have no owner");
  return m_owner;
}

std::vector<boost::shared_ptr<const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>>
  ribi::foam::Face::GetPoints() const noexcept
{
  std::vector<boost::shared_ptr<const Coordinat3D>> v;
  std::transform(
    m_points.begin(),
    m_points.end(),
    std::back_inserter(v),
    [](const boost::shared_ptr<Coordinat3D> point)
    {
      assert(point);
      const boost::shared_ptr<const Coordinat3D> const_point {
        point
      };
      assert(point == const_point);
      return const_point;
    }
  );
  assert(v.size() == m_points.size());
  //Only check first and last
  assert(v.empty() || v[0] == m_points[0]);
  assert(v.empty() || v[ v.size() - 1 ] == m_points[ v.size() - 1 ]);
  return v;
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::foam::CalcCenter(const Face& face) noexcept
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  Coordinat3D d(0.0,0.0,0.0);
  for (boost::shared_ptr<const Coordinat3D> c: face.GetPoints())
  {
    assert(c);
    d.set<0>(d.get<0>() + c->get<0>());
    d.set<1>(d.get<1>() + c->get<1>());
    d.set<2>(d.get<2>() + c->get<2>());
    //d += (*c);
  }
  //d /= static_cast<double>(face.GetPoints().size());
  d.set<0>(d.get<0>() / static_cast<double>(face.GetPoints().size()));
  d.set<1>(d.get<1>() / static_cast<double>(face.GetPoints().size()));
  d.set<2>(d.get<2>() / static_cast<double>(face.GetPoints().size()));
  return d;
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const ribi::foam::Face& face) noexcept
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  if (face.m_neighbour)
  {
    //Only display the address of a neighbour to prevent recursion
    assert(face.m_neighbour);
    os << face.m_neighbour;
  }
  os << '\n';
  assert(face.m_owner && "Every Face has an owner");
  //if (face.m_owner)
  {
    //Only display the address of a owner to prevent recursion
    assert(face.m_owner);
    os << face.m_owner;
  }
  os << '\n';
  for (const boost::shared_ptr<Coordinat3D> coordinat: face.m_points)
  {
    assert(coordinat);
    os << ToStr(*coordinat) << '\n';
  }
  return os;

}
