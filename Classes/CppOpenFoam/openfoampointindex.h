#ifndef OPENFOAMPOINTINDEX_H
#define OPENFOAMPOINTINDEX_H

#include <iosfwd>

namespace ribi {
namespace foam {

///The index in the 'points' file
struct PointIndex
{
  explicit PointIndex(const int index = 0);
  int Get() const noexcept { return m_index; }
  PointIndex& operator++() noexcept;   //Prefix
  PointIndex operator++(int) noexcept; //Postfix
  PointIndex& operator--() noexcept;   //Prefix
  PointIndex operator--(int) noexcept; //Postfix

  PointIndex& operator+=(const PointIndex& rhs) noexcept;
  PointIndex& operator-=(const PointIndex& rhs) noexcept;

  private:
  int m_index;
  friend std::istream& operator>>(std::istream& is, PointIndex& face_index);
};

std::ostream& operator<<(std::ostream& os, const PointIndex& face_index) noexcept;
std::istream& operator>>(std::istream& is, PointIndex& face_index);

const PointIndex operator+(const PointIndex& lhs, const PointIndex& rhs) noexcept;
const PointIndex operator-(const PointIndex& lhs, const PointIndex& rhs) noexcept;

bool operator==(const PointIndex& lhs, const PointIndex& rhs) noexcept;
bool operator!=(const PointIndex& lhs, const PointIndex& rhs) noexcept;
bool operator<(const PointIndex& lhs, const PointIndex& rhs) noexcept;
bool operator>(const PointIndex& lhs, const PointIndex& rhs) noexcept;
bool operator<=(const PointIndex& lhs, const PointIndex& rhs) noexcept;
bool operator>=(const PointIndex& lhs, const PointIndex& rhs) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMPOINTINDEX_H
