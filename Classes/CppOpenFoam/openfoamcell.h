#ifndef OPENFOAMCELL_H
#define OPENFOAMCELL_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "openfoamfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace foam {

///A Cell contains Faces that enclose a volume
///These Faces are
///- owned/managed by this Cell: m_owned_faces
///- owned/managed by a neighbouring Cell: m_faces
///Faces know
///- the Cell that owns them
///- optionally, the Cell they are also a member of, called 'neighbour'.
///  If this is nullptr, the Face is a boundary face
///If a Cell contains a boundary Face, it is a boundary cell
struct Cell
{
  ///owned_faces is a subset of all_faces
  Cell(
    const std::vector<boost::shared_ptr<Face>> owned_faces = {},
    const std::vector<boost::shared_ptr<Face>> all_faces = {}
  );

  ///Can only assign once
  void AssignOwnedFaces(const std::vector<boost::shared_ptr<Face>>& owned_faces);

  //const boost::shared_ptr<const Cell> GetNeighbour() const noexcept;
  const std::vector<boost::shared_ptr<const Face> > GetOwnedFaces() const noexcept;

  bool HasFace(const boost::shared_ptr<const Face> face) const noexcept;
  bool OwnsFace(const boost::shared_ptr<const Face> face) const noexcept;

  private:

  ///m_owned_faces is a subset of m_all_faces
  std::vector<boost::shared_ptr<Face>> m_all_faces;

  ///m_owned_faces is a subset of m_all_faces
  std::vector<boost::shared_ptr<Face>> m_owned_faces;

  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
};

std::ostream& operator<<(std::ostream& os, const Cell& cell);

} //namespace foam
} //namespace ribi

#endif // OPENFOAMCELL_H
