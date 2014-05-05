#ifndef RIBI_OPENFOAMNEIGHBOURFILE_H
#define RIBI_OPENFOAMNEIGHBOURFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"
#include "openfoamneighbourfileitem.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct NeighbourFile
{
  explicit NeighbourFile(const std::string& filename) : NeighbourFile(Parse(filename)) {}
  explicit NeighbourFile(
    const Header header = GetDefaultHeader(),
    const std::vector<NeighbourFileItem>& items = {});

  ///If the FaceIndex is present
  bool CanGetItem(const FaceIndex& face_index) const noexcept;

  //DON'T: Use OwnerFile::CountNumberOfCells instead
  //WHY: because all cell indices are detected in owner
  ///Find the first CellIndex beyond the cell indices present
  ///Or: find the first CellIndex that does not exist anymore
  //const CellIndex CountNumberOfCells() const noexcept;

  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }
  const std::vector<NeighbourFileItem>& GetItems() const noexcept { return m_items; }

  ///Assumes CanGetItem == true
  const NeighbourFileItem& GetItem(const FaceIndex& face_index) const noexcept;

  int GetNumberOfItems() const noexcept { return static_cast<int>(m_items.size()); }

  void SetItem(const FaceIndex& face_index, const NeighbourFileItem& item) noexcept;

  private:
  explicit NeighbourFile(std::istream& is) : NeighbourFile(Parse(is)) {}

  ///The OpenFOAM header
  Header m_header;
  ///The items 'neighbour' contains
  std::vector<NeighbourFileItem> m_items;

  static NeighbourFile Parse(std::istream& is);
  static NeighbourFile Parse(const std::string& filename);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const NeighbourFile& f) noexcept;
  friend std::istream& operator>>(std::istream& is, NeighbourFile& f);
};

bool operator==(const NeighbourFile& lhs,const NeighbourFile& rhs) noexcept;
bool operator!=(const NeighbourFile& lhs,const NeighbourFile& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const NeighbourFile& f) noexcept;
std::istream& operator>>(std::istream& is, NeighbourFile& f);

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMNEIGHBOURFILE_H
