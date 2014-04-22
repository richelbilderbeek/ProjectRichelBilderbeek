#ifndef OPENFOAMPOINTSFILE_H
#define OPENFOAMPOINTSFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"
#include "openfoampointsfileitem.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct PointsFile
{
  explicit PointsFile(const std::string& filename) : PointsFile(Parse(filename)) {}
  explicit PointsFile(
    const Header header = GetDefaultHeader(),
    const std::vector<PointsFileItem>& items = {});

  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }
  const std::vector<PointsFileItem>& GetItems() const noexcept { return m_items; }

  private:
  explicit PointsFile(std::istream& is) : PointsFile(Parse(is)) {}

  ///The OpenFOAM header
  Header m_header;
  ///The items faces contains
  std::vector<PointsFileItem> m_items;

  static PointsFile Parse(std::istream& is);
  static PointsFile Parse(const std::string& filename);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const PointsFile& f) noexcept;
  friend std::istream& operator>>(std::istream& is, PointsFile& f);
};

bool operator==(const PointsFile& lhs,const PointsFile& rhs) noexcept;
bool operator!=(const PointsFile& lhs,const PointsFile& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const PointsFile& f) noexcept;
std::istream& operator>>(std::istream& is, PointsFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMPOINTSFILE_H
