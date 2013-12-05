#ifndef OPENFOAMOWNERFILEITEM_H
#define OPENFOAMOWNERFILEITEM_H

#include <vector>
#include <iosfwd>
#include "openfoamcellindex.h"

namespace ribi {
namespace foam {

///An item in an OpenFOAM boundary file
struct OwnerFileItem
{
  OwnerFileItem(const CellIndex& cell_index = 0);

  CellIndex GetCellIndex() const noexcept { return m_cell_index; }

  private:

  CellIndex m_cell_index;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend class OpenFoamOwnerFile;
  friend std::istream& operator>>(std::istream& is, OwnerFileItem& f);
};

bool operator==(const OwnerFileItem& lhs, const OwnerFileItem& rhs);
bool operator!=(const OwnerFileItem& lhs, const OwnerFileItem& rhs);
std::ostream& operator<<(std::ostream& os, const OwnerFileItem& f);
std::istream& operator>>(std::istream& is, OwnerFileItem& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMOWNERFILEITEM_H
