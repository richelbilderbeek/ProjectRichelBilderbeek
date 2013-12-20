#include "openfoamcell.h"

#include <cassert>
#include <ostream>

#include "openfoamface.h"
#include "trace.h"

ribi::foam::Cell::Cell()
  : m_owned_faces{}
    //,m_neighbour{}
{

}

/*
void ribi::foam::Cell::AssignNeighbour(const boost::shared_ptr<ribi::foam::Cell> neighbour) noexcept
{
  assert(!m_neighbour && "neighbour can only be assigned once");
  assert(neighbour);
  m_neighbour = neighbour;
}
*/

void ribi::foam::Cell::AssignOwnedFaces(const std::vector<boost::shared_ptr<Face>>& owned_faces)
{
  assert(m_owned_faces.empty() && "owned faces can only be assigned once");
  assert(!owned_faces.empty());
  m_owned_faces = owned_faces;
}

/*
const boost::shared_ptr<const ribi::foam::Cell> ribi::foam::Cell::GetNeighbour() const noexcept
{
  return m_neighbour;
}
*/

const std::vector<boost::shared_ptr<const ribi::foam::Face> > ribi::foam::Cell::GetOwnedFaces() const noexcept
{
  std::vector<boost::shared_ptr<const ribi::foam::Face>> v;
  std::transform(
    m_owned_faces.begin(),
    m_owned_faces.end(),
    std::back_inserter(v),
    [](const boost::shared_ptr<Face> face)
    {
      assert(face);
      const boost::shared_ptr<const ribi::foam::Face> const_face {
        face
      };
      assert(face == const_face);
      return const_face;
    }
  );
  assert(v.size() == m_owned_faces.size());
  //Only check first and last
  assert(v.empty() || v[0] == m_owned_faces[0]);
  assert(v.empty() || v[ v.size() - 1 ] == m_owned_faces[ v.size() - 1 ]);
  return v;
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const ribi::foam::Cell& cell)
{
  for (boost::shared_ptr<Face> face: cell.m_owned_faces)
  {
    assert(face);
    os << *face << '\n';
  }
  //os << *cell.m_neighbour;
  return os;
}
