#ifndef OPENFOAMNEIGHBOURFILE_H
#define OPENFOAMNEIGHBOURFILE_H

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
  explicit NeighbourFile(std::istream& is) : NeighbourFile(Parse(is)) {}
  explicit NeighbourFile(const std::string& filename) : NeighbourFile(Parse(filename)) {}
  explicit NeighbourFile(
    const Header header = GetDefaultHeader(),
    const std::vector<NeighbourFileItem>& items = {});

  ///If the FaceIndex is present
  bool CanGetItem(const FaceIndex& face_index) const noexcept;

  ///Find the first CellIndex beyond the cell indices present
  ///Or: find the first CellIndex that does not exist anymore
  const CellIndex FindMaxCellIndex() const noexcept;

  static const Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }
  const std::vector<NeighbourFileItem> GetItems() const noexcept { return m_items; }

  ///Assumes CanGetItem == true
  const NeighbourFileItem& GetItem(const FaceIndex& face_index) const noexcept;

  void SetItem(const FaceIndex& face_index, const NeighbourFileItem& item) noexcept;

  private:

  ///The OpenFOAM header
  Header m_header;
  ///The items 'neighbour' contains
  std::vector<NeighbourFileItem> m_items;

  static const NeighbourFile Parse(std::istream& is);
  static const NeighbourFile Parse(const std::string& filename);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const NeighbourFile& f);
  friend std::istream& operator>>(std::istream& is, NeighbourFile& f);
};

bool operator==(const NeighbourFile& lhs,const NeighbourFile& rhs);
bool operator!=(const NeighbourFile& lhs,const NeighbourFile& rhs);
std::ostream& operator<<(std::ostream& os, const NeighbourFile& f);
std::istream& operator>>(std::istream& is, NeighbourFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMNEIGHBOURFILE_H
