#ifndef RIBI_OPENFOAMOWNERFILE_H
#define RIBI_OPENFOAMOWNERFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"
#include "openfoamownerfileitem.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct OwnerFile
{
  explicit OwnerFile(const std::string& filename) : OwnerFile(Parse(filename)) {}
  explicit OwnerFile(
    const Header header = GetDefaultHeader(),
    const std::vector<OwnerFileItem>& items = {});

  ///Find the first CellIndex beyond the cell indices present
  ///Or: find the first CellIndex that does not exist anymore
  CellIndex CountNumberOfCells() const noexcept;

  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }
  std::vector<OwnerFileItem> GetItems() const noexcept { return m_items; }
  const OwnerFileItem& GetItem(const FaceIndex& face_index) const noexcept;


  void SetItem(const FaceIndex& face_index, const OwnerFileItem& item) noexcept;

  private:

  ///The OpenFOAM header
  Header m_header;
  ///The items 'neighbour' contains
  std::vector<OwnerFileItem> m_items;

  explicit OwnerFile(std::istream& is) : OwnerFile(Parse(is)) {}
  static OwnerFile Parse(std::istream& is);
  static OwnerFile Parse(const std::string& filename);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const OwnerFile& f) noexcept;
  friend std::istream& operator>>(std::istream& is, OwnerFile& f);
};

bool operator==(const OwnerFile& lhs,const OwnerFile& rhs) noexcept;
bool operator!=(const OwnerFile& lhs,const OwnerFile& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const OwnerFile& f) noexcept;
std::istream& operator>>(std::istream& is, OwnerFile& f);

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMOWNERFILE_H
