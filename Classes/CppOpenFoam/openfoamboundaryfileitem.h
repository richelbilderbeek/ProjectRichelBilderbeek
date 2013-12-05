#ifndef OPENFOAMBOUNDARYFILEITEM_H
#define OPENFOAMBOUNDARYFILEITEM_H

#include <string>
#include <iosfwd>

#include "openfoamfaceindex.h"

namespace ribi {
namespace foam {

///An item in an OpenFOAM boundary file
struct BoundaryFileItem
{
  BoundaryFileItem(
    const std::string& name = "",
    const std::string& type = "",
    const int n_faces = 0,
    const FaceIndex n_start_face = 0
  );

  const std::string& GetName() const noexcept { return m_name; }
  int GetNfaces() const noexcept { return m_n_faces; }
  const FaceIndex GetStartFace() const noexcept { return m_start_face; }
  const std::string GetType() const noexcept { return m_type; }

  private:

  int m_n_faces;
  std::string m_name;
  FaceIndex m_start_face;
  std::string m_type;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend class OpenFoamBoundaryFile;
  friend std::istream& operator>>(std::istream& is, BoundaryFileItem& f);
};

bool operator==(const BoundaryFileItem& lhs, const BoundaryFileItem& rhs);
bool operator!=(const BoundaryFileItem& lhs, const BoundaryFileItem& rhs);
std::ostream& operator<<(std::ostream& os, const BoundaryFileItem& f);
std::istream& operator>>(std::istream& is, BoundaryFileItem& f);

} //~namespace foam
} //~namespace ribi


#endif // OPENFOAMBOUNDARYFILEITEM_H
