#ifndef OPENFOAMNEIGHBOURFILE_H
#define OPENFOAMNEIGHBOURFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct NeighbourFile
{
  NeighbourFile(std::istream& is) : NeighbourFile(Parse(is)) {}
  NeighbourFile(
    const Header header = Header("labelList","constant/polyMesh","neighbour"),
    const std::vector<NeighbourFileItem>& items = {});

  const Header& GetHeader() const noexcept { return m_header; }
  const std::vector<NeighbourFileItem> GetItems() const noexcept { return m_items; }

  private:

  ///The OpenFOAM header
  Header m_header;
  ///The items 'neighbour' contains
  std::vector<NeighbourFileItem> m_items;

  static const NeighbourFile Parse(std::istream& is);

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
