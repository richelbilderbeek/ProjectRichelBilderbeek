#ifndef OPENFOAMCELLINDEX_H
#define OPENFOAMCELLINDEX_H

#include <iosfwd>

namespace ribi {
namespace foam {

struct CellIndex
{
  explicit CellIndex(const int index = 0);
  int Get() const noexcept { return m_index; }

  private:
  int m_index;
  friend std::istream& operator>>(std::istream& is, CellIndex& face_index);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const CellIndex& face_index);
std::istream& operator>>(std::istream& is, CellIndex& face_index);

bool operator==(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator!=(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator<(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator>(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator>=(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator<=(const CellIndex& lhs, const CellIndex& rhs) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMCELLINDEX_H
