#ifndef OPENFOAMNEIGHBOURFILEITEM_H
#define OPENFOAMNEIGHBOURFILEITEM_H

#include <vector>
#include <iosfwd>

namespace ribi {
namespace foam {

///An item in an OpenFOAM boundary file
struct NeighbourFileItem
{
  NeighbourFileItem(const int face_index = 0);

  int GetFaceIndex() const noexcept { return m_face_index; }

  private:

  int m_face_index;

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
