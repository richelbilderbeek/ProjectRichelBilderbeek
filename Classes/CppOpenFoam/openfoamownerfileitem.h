#ifndef OPENFOAMOWNERFILEITEM_H
#define OPENFOAMOWNERFILEITEM_H

#include <vector>
#include <iosfwd>

namespace ribi {
namespace foam {

///An item in an OpenFOAM boundary file
struct OwnerFileItem
{
  OwnerFileItem(const int face_index = 0);

  int GetFaceIndex() const noexcept { return m_face_index; }

  private:

  int m_face_index;

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
