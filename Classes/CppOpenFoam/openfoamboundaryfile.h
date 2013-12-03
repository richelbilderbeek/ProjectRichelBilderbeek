#ifndef OPENFOAMBOUNDARYFILE_H
#define OPENFOAMBOUNDARYFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct BoundaryFile
{
  BoundaryFile(std::istream& is) : BoundaryFile(Parse(is)) {}
  BoundaryFile(
    const Header header = GetDefaultHeader(),
    const std::vector<BoundaryFileItem>& items = {});

  static const Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }
  const std::vector<BoundaryFileItem> GetItems() const noexcept { return m_items; }

  private:

  ///The OpenFOAM header
  Header m_header;
  ///The items boundary contains
  std::vector<BoundaryFileItem> m_items;

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
std::istream& operator>>(std::istream& is, BoundaryFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMBOUNDARYFILE_H
