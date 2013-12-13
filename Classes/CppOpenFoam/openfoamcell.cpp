#include "openfoamcell.h"

ribi::foam::Cell::Cell()
  : m_owned_faces{},
    m_neighbour{}
{

}

void ribi::foam::Cell::AssignOwnedFaces(const std::vector<boost::shared_ptr<Face>>& owned_faces)
{
  assert(m_owned_faces.empty() && "owned faces can only be assigned once");
  assert(!owned_faces.empty());
  m_owned_faces = owned_faces;
}
