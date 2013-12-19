#include "openfoamboundary.h"

#include <cassert>
#include <ostream>

#include "trace.h"
#include "openfoamface.h"

ribi::foam::Boundary::Boundary(
  const std::vector<boost::shared_ptr<Face> >& faces,
  const std::string& name,
  const std::string& type
  )
  : m_faces(faces),
    m_name(name),
    m_type(type)
{

}

const std::vector<boost::shared_ptr<const ribi::foam::Face> > ribi::foam::Boundary::GetFaces() const noexcept
{
  std::vector<boost::shared_ptr<const ribi::foam::Face>> v;
  std::transform(
    m_faces.begin(),
    m_faces.end(),
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
  assert(v.size() == m_faces.size());
  //Only check first and last
  assert(v.empty() || v[0] == m_faces[0]);
  assert(v.empty() || v[ v.size() - 1 ] == m_faces[ v.size() - 1 ]);
  return v;
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const ribi::foam::Boundary& boundary)
{
  os
    << boundary.m_name << '\n'
    << boundary.m_type << '\n';
  for (const boost::shared_ptr<Face> face: boundary.m_faces)
  {
    os << *face << '\n';
  }
  return os;
}
