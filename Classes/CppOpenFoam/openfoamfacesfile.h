#ifndef OPENFOAMFACESFILE_H
#define OPENFOAMFACESFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct FacesFile
{
  FacesFile(std::istream& is) : FacesFile(Parse(is)) {}
  FacesFile(
    const Header header = GetDefaultHeader(),
    const std::vector<FacesFileItem>& items = {});

  static const Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }
  const std::vector<FacesFileItem> GetItems() const noexcept { return m_items; }

  private:

  ///The OpenFOAM header
  Header m_header;
  ///The items faces contains
  std::vector<FacesFileItem> m_items;

  static const FacesFile Parse(std::istream& is);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const FacesFile& f);
  friend std::istream& operator>>(std::istream& is, FacesFile& f);
};

bool operator==(const FacesFile& lhs,const FacesFile& rhs);
bool operator!=(const FacesFile& lhs,const FacesFile& rhs);
std::ostream& operator<<(std::ostream& os, const FacesFile& f);
std::istream& operator>>(std::istream& is, FacesFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFACESFILE_H
