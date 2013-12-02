#ifndef OPENFOAMFACESFILEITEM_H
#define OPENFOAMFACESFILEITEM_H

#include <vector>
#include <iosfwd>

namespace ribi {
namespace foam {

///An item in an OpenFOAM boundary file
struct FacesFileItem
{
  FacesFileItem(
    const std::vector<int>& node_indices = {}
  );

  const std::vector<int>& GetNodeIndices() const noexcept { return m_node_indices; }

  private:

  std::vector<int> m_node_indices;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend class OpenFoamFacesFile;
  friend std::istream& operator>>(std::istream& is, FacesFileItem& f);
};

bool operator==(const FacesFileItem& lhs, const FacesFileItem& rhs);
bool operator!=(const FacesFileItem& lhs, const FacesFileItem& rhs);
std::ostream& operator<<(std::ostream& os, const FacesFileItem& f);
std::istream& operator>>(std::istream& is, FacesFileItem& f);

} //~namespace foam
} //~namespace ribi


#endif // OPENFOAMFACESFILEITEM_H
