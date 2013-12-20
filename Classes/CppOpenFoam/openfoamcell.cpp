#include "openfoamcell.h"

#include <cassert>
#include <ostream>

#include "openfoamface.h"
#include "trace.h"

ribi::foam::Cell::Cell(
  const std::vector<boost::shared_ptr<Face>> owned_faces,
  const std::vector<boost::shared_ptr<Face>> all_faces
  )
  : m_all_faces{all_faces},
    m_owned_faces{owned_faces}
{
  #ifndef NDEBUG
  for (const std::vector<boost::shared_ptr<Face>> face: m_owned_faces)
  {
    assert(face);
    assert(std::count(m_all_faces.begin(),m_all_faces.end(),face) == 1
      && "m_owned_faces must be a subset of m_all_faces");
  }
  #endif
}

void ribi::foam::Cell::AssignOwnedFaces(const std::vector<boost::shared_ptr<Face>>& owned_faces)
{
  assert(m_owned_faces.empty() && "owned faces can only be assigned once");
  assert(!owned_faces.empty());
  m_owned_faces = owned_faces;
}

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

bool ribi::foam::Cell::HasFace(const boost::shared_ptr<const ribi::foam::Face> face) const noexcept
{
  #ifndef NDEBUG
  assert(m_all_faces.size() >= m_owned_faces
    && "m_owned_faces must be a subset of m_all_faces: there should be more m_all_faces"
  );
  for (const std::vector<boost::shared_ptr<Face>> face: m_owned_faces)
  {
    assert(face);
    assert(std::count(m_all_faces.begin(),m_all_faces.end(),face) == 1
      && "m_owned_faces must be a subset of m_all_faces: every owned Face must be in m_all_faces"
    );
  }
  #endif

  return std::count(m_all_faces.begin(),m_all_faces.end(),face);
}

bool ribi::foam::Cell::OwnsFace(const boost::shared_ptr<const ribi::foam::Face> face) const noexcept
{
  return std::count(m_owned_faces.begin(),m_owned_faces.end(),face);

}

std::ostream& ribi::foam::operator<<(std::ostream& os, const ribi::foam::Cell& cell)
{
  for (boost::shared_ptr<Face> face: cell.m_owned_faces)
  {
    assert(face);
    os << *face << '\n';
  }
  return os;
}
