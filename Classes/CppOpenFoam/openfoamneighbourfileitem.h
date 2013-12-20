#ifndef OPENFOAMNEIGHBOURFILEITEM_H
#define OPENFOAMNEIGHBOURFILEITEM_H

#include <vector>
#include <iosfwd>
#include "openfoamcellindex.h"

namespace ribi {
namespace foam {

///An item in an OpenFOAM boundary file
struct NeighbourFileItem
{
  ///A CellIndex of -1 denotes that a Face has no Neighbour
  explicit NeighbourFileItem(const CellIndex face_index = CellIndex(-1));

  ///A CellIndex of -1 denotes that a Face has no Neighbour
  const CellIndex GetCellIndex() const noexcept { return m_cell_index; }

  private:

  CellIndex m_cell_index;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend class OpenFoamNeighbourFile;
  friend std::istream& operator>>(std::istream& is, NeighbourFileItem& f);
};

bool operator==(const NeighbourFileItem& lhs, const NeighbourFileItem& rhs);
bool operator!=(const NeighbourFileItem& lhs, const NeighbourFileItem& rhs);
std::ostream& operator<<(std::ostream& os, const NeighbourFileItem& f);
std::istream& operator>>(std::istream& is, NeighbourFileItem& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMNEIGHBOURFILEITEM_H
