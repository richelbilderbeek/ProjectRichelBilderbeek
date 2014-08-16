#ifndef RIBI_OPENFOAMFACESFILEITEM_H
#define RIBI_OPENFOAMFACESFILEITEM_H

#include <vector>
#include <iosfwd>
#include "openfoampointindex.h"

namespace ribi {
namespace foam {

///An item in an OpenFOAM 'faces' file
struct FacesFileItem
{
  explicit FacesFileItem(
    const std::vector<PointIndex>& point_indices = {}
  );

  const std::vector<PointIndex>& GetPointIndices() const noexcept { return m_point_indices; }

  private:

  std::vector<PointIndex> m_point_indices;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend class OpenFoamFacesFile;
  friend std::istream& operator>>(std::istream& is, FacesFileItem& f);
};

bool operator==(const FacesFileItem& lhs, const FacesFileItem& rhs) noexcept;
bool operator!=(const FacesFileItem& lhs, const FacesFileItem& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const FacesFileItem& f) noexcept;
std::istream& operator>>(std::istream& is, FacesFileItem& f);

} //~namespace foam
} //~namespace ribi


#endif // RIBI_OPENFOAMFACESFILEITEM_H
