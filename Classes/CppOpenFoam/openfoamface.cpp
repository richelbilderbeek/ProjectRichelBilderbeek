#include "openfoamface.h"

ribi::foam::Face::Face(
  const boost::shared_ptr<Cell> neighbour,
  const boost::shared_ptr<Cell> owner,
  const std::vector<boost::shared_ptr<ribi::Coordinat3D> >& points
)
  : m_neighbour(neighbour),
    m_owner(owner),
    m_points(points)
{

}

void ribi::foam::Face::AssignOwner(const boost::shared_ptr<ribi::foam::Cell> owner) noexcept
{
  assert(!m_owner && "Can only assign owner once");
  assert(owner);

  m_owner = owner;
}

const boost::shared_ptr<ribi::foam::Cell> ribi::foam::Face::GetOwner() noexcept
{
  assert( (m_owner || !m_owner) && "Allow Face to have no owner");
  return m_owner;
}
