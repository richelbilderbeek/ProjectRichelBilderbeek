#ifndef OPENFOAMBOUNDARYINDEX_H
#define OPENFOAMBOUNDARYINDEX_H

#include <iosfwd>

namespace ribi {
namespace foam {

struct BoundaryIndex
{
  ///Throws std::invalid_argument if the index is invalid
  explicit BoundaryIndex(const int index);
  int Get() const noexcept { return m_index; }

  ///Throws std::invalid_argument if the new index is invalid
  BoundaryIndex& operator-=(const BoundaryIndex& rhs);
  BoundaryIndex& operator++() noexcept;   //Prefix
  BoundaryIndex operator++(int) noexcept; //Postfix
  private:
  int m_index;
  friend std::istream& operator>>(std::istream& is, BoundaryIndex& face_index) noexcept;
};

std::ostream& operator<<(std::ostream& os, const BoundaryIndex& face_index) noexcept;
std::istream& operator>>(std::istream& is, BoundaryIndex& face_index) noexcept;

const BoundaryIndex operator+(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept;
const BoundaryIndex operator-(const BoundaryIndex& lhs, const BoundaryIndex& rhs);

bool operator==(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept;
bool operator!=(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept;
bool operator<(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept;
bool operator>(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept;
bool operator>=(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept;
bool operator<=(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMBOUNDARYINDEX_H
