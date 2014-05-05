#ifndef RIBI_OPENFOAMBOUNDARYFILE_H
#define RIBI_OPENFOAMBOUNDARYFILE_H

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
  explicit BoundaryFile(const std::string& filename) : BoundaryFile(Parse(filename)) {}
  explicit BoundaryFile(
    const Header header = GetDefaultHeader(),
    const std::vector<BoundaryFileItem>& items = {});


  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }

  std::vector<BoundaryFileItem> GetItems() const noexcept { return m_items; }

  BoundaryFileItem GetItem(const BoundaryIndex& boundary_index) const noexcept;

  ///Obtain the number of boundaries, the size of m_items, or the first boundary index not available
  BoundaryIndex GetMaxBoundaryIndex() const noexcept;

  ///Is the Face belonging to a Boundary?
  ///(if not, it belongs to a Cell)
  bool IsBoundary(const FaceIndex& face_index) const noexcept { return CanGet(face_index); }

  ///Swap the face indices between
  //void Swap(const FaceIndex& lhs, const FaceIndex& rhs);

  private:
  ///Read an OpenFOAM 'boundary' file.
  ///Throws std::runtime_error if file is incorrectly formed
  explicit BoundaryFile(std::istream& is) : BoundaryFile(Parse(is)) {}

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
  static BoundaryFile Parse(std::istream& is);

  static BoundaryFile Parse(const std::string& filename);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const BoundaryFile& f) noexcept;
  friend std::istream& operator>>(std::istream& is, BoundaryFile& f);
};

bool operator==(const BoundaryFile& lhs,const BoundaryFile& rhs) noexcept;
bool operator!=(const BoundaryFile& lhs,const BoundaryFile& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const BoundaryFile& f) noexcept;

///Read an OpenFOAM 'boundary' file.
///Throws std::runtime_error if file is incorrectly formed
std::istream& operator>>(std::istream& is, BoundaryFile& f);

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMBOUNDARYFILE_H
