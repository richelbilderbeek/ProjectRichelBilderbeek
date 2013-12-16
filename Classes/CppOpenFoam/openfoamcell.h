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
///Every Cell has at least one Face it shares with another Cell. This other
///Cell is called a neighbour
struct Cell
{
  Cell();

  void AssignOwnedFaces(const std::vector<boost::shared_ptr<Face>>& owned_faces);

  const boost::shared_ptr<const Cell> GetNeighbour() const noexcept;
  const std::vector<boost::shared_ptr<const Face> > GetOwnedFaces() const noexcept;

  private:

  std::vector<boost::shared_ptr<Face>> m_owned_faces;

  const boost::shared_ptr<Cell> m_neighbour;

  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
};

std::ostream& operator<<(std::ostream& os, const Cell& cell);

} //namespace foam
} //namespace ribi

#endif // OPENFOAMCELL_H
