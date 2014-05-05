#ifndef RIBI_OPENFOAMFACESFILE_H
#define RIBI_OPENFOAMFACESFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"
#include "openfoamfwd.h"
#include "openfoamheader.h"
#include "openfoamfacesfileitem.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct FacesFile
{
  explicit FacesFile(const std::string& filename) : FacesFile(Parse(filename)) {}
  explicit FacesFile(
    const Header header = GetDefaultHeader(),
    const std::vector<FacesFileItem>& items = {});

  bool CanGetItem(const FaceIndex& face_index) const noexcept;

  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }
  std::vector<FacesFileItem> GetItems() const noexcept { return m_items; }

  ///Assumes CanGetItem is true
  const FacesFileItem& GetItem(const FaceIndex& face_index) const noexcept;

  ///Obtain the number of faces, the size of m_items, or the first face index not available
  FaceIndex GetMaxFaceIndex() const noexcept;

  private:
  explicit FacesFile(std::istream& is) : FacesFile(Parse(is)) {}

  ///The OpenFOAM header
  Header m_header;
  ///The items faces contains
  std::vector<FacesFileItem> m_items;

  static FacesFile Parse(std::istream& is);
  static FacesFile Parse(const std::string& filename);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const FacesFile& f) noexcept;
  friend std::istream& operator>>(std::istream& is, FacesFile& f);
};

bool operator==(const FacesFile& lhs,const FacesFile& rhs) noexcept;
bool operator!=(const FacesFile& lhs,const FacesFile& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const FacesFile& f) noexcept;
std::istream& operator>>(std::istream& is, FacesFile& f);

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMFACESFILE_H
