#ifndef OPENFOAMOWNERFILE_H
#define OPENFOAMOWNERFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct OwnerFile
{
  OwnerFile(std::istream& is) : OwnerFile(Parse(is)) {}
  OwnerFile(
    const Header header = Header("labelList","constant/polyMesh","owner"),
    const std::vector<OwnerFileItem>& items = {});

  const Header& GetHeader() const noexcept { return m_header; }
  const std::vector<OwnerFileItem> GetItems() const noexcept { return m_items; }

  private:

  ///The OpenFOAM header
  Header m_header;
  ///The items 'neighbour' contains
  std::vector<OwnerFileItem> m_items;

  static const OwnerFile Parse(std::istream& is);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const OwnerFile& f);
  friend std::istream& operator>>(std::istream& is, OwnerFile& f);
};

bool operator==(const OwnerFile& lhs,const OwnerFile& rhs);
bool operator!=(const OwnerFile& lhs,const OwnerFile& rhs);
std::ostream& operator<<(std::ostream& os, const OwnerFile& f);
std::istream& operator>>(std::istream& is, OwnerFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMOWNERFILE_H
