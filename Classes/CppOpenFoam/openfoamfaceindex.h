#ifndef OPENFOAMFACEINDEX_H
#define OPENFOAMFACEINDEX_H

#include <iosfwd>

namespace ribi {
namespace foam {

struct FaceIndex
{
  FaceIndex(const int index);
  int Get() const noexcept { return m_index; }

  private:
  int m_index;
  friend std::istream& operator>>(std::istream& is, FaceIndex& face_index);
};

std::ostream& operator<<(std::ostream& os, const FaceIndex& face_index);
std::istream& operator>>(std::istream& is, FaceIndex& face_index);

bool operator==(const FaceIndex& lhs, const FaceIndex& rhs) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFACEINDEX_H
