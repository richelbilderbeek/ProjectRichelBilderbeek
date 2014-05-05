#ifndef RIBI_OPENFOAMFACEINDEX_H
#define RIBI_OPENFOAMFACEINDEX_H

#include <iosfwd>

namespace ribi {
namespace foam {

struct FaceIndex
{
  ///Throws std::invalid_argument if the index is invalid
  explicit FaceIndex(const int index);
  int Get() const noexcept { return m_index; }

  ///Throws std::invalid_argument if the new index is invalid
  FaceIndex& operator+=(const FaceIndex& rhs);
  FaceIndex& operator-=(const FaceIndex& rhs);
  FaceIndex& operator++() noexcept;   //Prefix
  FaceIndex operator++(int) noexcept; //Postfix
  FaceIndex& operator--() noexcept;   //Prefix
  FaceIndex operator--(int) noexcept; //Postfix
  private:
  int m_index;
  friend std::istream& operator>>(std::istream& is, FaceIndex& face_index) noexcept;
};

std::ostream& operator<<(std::ostream& os, const FaceIndex& face_index) noexcept;
std::istream& operator>>(std::istream& is, FaceIndex& face_index) noexcept;

const FaceIndex operator+(const FaceIndex& lhs, const FaceIndex& rhs) noexcept;
const FaceIndex operator-(const FaceIndex& lhs, const FaceIndex& rhs);

bool operator==(const FaceIndex& lhs, const FaceIndex& rhs) noexcept;
bool operator!=(const FaceIndex& lhs, const FaceIndex& rhs) noexcept;
bool operator<(const FaceIndex& lhs, const FaceIndex& rhs) noexcept;
bool operator>(const FaceIndex& lhs, const FaceIndex& rhs) noexcept;
bool operator>=(const FaceIndex& lhs, const FaceIndex& rhs) noexcept;
bool operator<=(const FaceIndex& lhs, const FaceIndex& rhs) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMFACEINDEX_H
