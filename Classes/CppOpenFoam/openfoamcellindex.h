#ifndef OPENFOAMCELLINDEX_H
#define OPENFOAMCELLINDEX_H

#include <iosfwd>

namespace ribi {
namespace foam {

struct CellIndex
{
  explicit CellIndex(const int index = -1);
  int Get() const noexcept { return m_index; }

  CellIndex& operator++() noexcept;   //Prefix
  CellIndex operator++(int) noexcept; //Postfix

  private:
  int m_index;
  friend std::istream& operator>>(std::istream& is, CellIndex& cell_index);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const CellIndex& cell_index);
std::istream& operator>>(std::istream& is, CellIndex& cell_index);

bool operator==(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator!=(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator<(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator>(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator>=(const CellIndex& lhs, const CellIndex& rhs) noexcept;
bool operator<=(const CellIndex& lhs, const CellIndex& rhs) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMCELLINDEX_H
