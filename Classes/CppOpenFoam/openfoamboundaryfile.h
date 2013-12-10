#ifndef OPENFOAMBOUNDARYFILE_H
#define OPENFOAMBOUNDARYFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"
#include "openfoamboundaryfileitem.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct BoundaryFile
{
  ///Read an OpenFOAM 'boundary' file.
  ///Throws std::runtime_error if file is incorrectly formed
  explicit BoundaryFile(std::istream& is) : BoundaryFile(Parse(is)) {}

  explicit BoundaryFile(
    const Header header = GetDefaultHeader(),
    const std::vector<BoundaryFileItem>& items = {});

  static const Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }
  const std::vector<BoundaryFileItem> GetItems() const noexcept { return m_items; }

  ///Swap the face indices between
  //void Swap(const FaceIndex& lhs, const FaceIndex& rhs);

  private:

  ///The OpenFOAM header
  Header m_header;
  ///The items boundary contains
  std::vector<BoundaryFileItem> m_items;

  ///Is the FaceIndex present among the current items?
  bool CanGet(const FaceIndex& face_index) const noexcept;

  ///Find out which BoundaryFileItem the face belongs to
  ///Assumes CanGet(face_index) == true
  BoundaryFileItem& Find(const FaceIndex& face_index) noexcept;


  ///Read an OpenFOAM 'boundary' file.
  ///Throws std::runtime_error if file is incorrectly formed
  static const BoundaryFile Parse(std::istream& is);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const BoundaryFile& f);
  friend std::istream& operator>>(std::istream& is, BoundaryFile& f);
};

bool operator==(const BoundaryFile& lhs,const BoundaryFile& rhs);
bool operator!=(const BoundaryFile& lhs,const BoundaryFile& rhs);
std::ostream& operator<<(std::ostream& os, const BoundaryFile& f);

///Read an OpenFOAM 'boundary' file.
///Throws std::runtime_error if file is incorrectly formed
std::istream& operator>>(std::istream& is, BoundaryFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMBOUNDARYFILE_H
