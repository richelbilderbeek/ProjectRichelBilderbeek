#ifndef OPENFOAMNEIGHBOURFILEITEM_H
#define OPENFOAMNEIGHBOURFILEITEM_H

#include <vector>
#include <iosfwd>
#include "openfoamcellindex.h"

namespace ribi {
namespace foam {

///An item in an OpenFOAM 'neighbour' file
///A neighbour files contains, for every face, the cell index of which the face is a neighbour of
///
///For example, from /Classes/CppOpenFoam/neighbour_1x2x2:
///
///4(1 2 3 3)
///
///Equivalent to, as faces_1x2x2 contains twenty faces:
///
///20(1 2 3 3 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1)
///
///This means that:
/// - Face 0 has Cell 1 as its neighbour, and is thus an internal face
/// - Face 1 has Cell 2 as its neighbour, and is thus an internal face
/// - Face 2 has Cell 3 as its neighbour, and is thus an internal face
/// - Face 3 has Cell 3 as its neighbour, and is thus an internal face
/// - All other Faces have no neighbours, and are thus boundary faces
///
///The file 'neighbour' has path '[case_folder]/constant/polyMesh/neighbour'
struct NeighbourFileItem
{
  ///A CellIndex of -1 denotes that a Face has no Neighbour
  explicit NeighbourFileItem(const CellIndex cell_index = CellIndex(-1));

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
