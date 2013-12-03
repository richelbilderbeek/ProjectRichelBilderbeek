#ifndef OPENFOAMPOINTSFILE_H
#define OPENFOAMPOINTSFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct PointsFile
{
  PointsFile(std::istream& is) : PointsFile(Parse(is)) {}
  PointsFile(
    const Header header = Header("vectorField","constant/polyMesh","points"),
    const std::vector<PointsFileItem>& items = {});

  const Header& GetHeader() const noexcept { return m_header; }
  const std::vector<PointsFileItem>& GetItems() const noexcept { return m_items; }

  private:

  ///The OpenFOAM header
  Header m_header;
  ///The items faces contains
  std::vector<PointsFileItem> m_items;

  static const PointsFile Parse(std::istream& is);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const PointsFile& f);
  friend std::istream& operator>>(std::istream& is, PointsFile& f);
};

bool operator==(const PointsFile& lhs,const PointsFile& rhs);
bool operator!=(const PointsFile& lhs,const PointsFile& rhs);
std::ostream& operator<<(std::ostream& os, const PointsFile& f);
std::istream& operator>>(std::istream& is, PointsFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMPOINTSFILE_H
