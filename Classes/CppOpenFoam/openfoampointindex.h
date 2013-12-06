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

  private:
  int m_index;
  friend std::istream& operator>>(std::istream& is, PointIndex& face_index);
};

std::ostream& operator<<(std::ostream& os, const PointIndex& face_index);
std::istream& operator>>(std::istream& is, PointIndex& face_index);

bool operator==(const PointIndex& lhs, const PointIndex& rhs) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMPOINTINDEX_H
