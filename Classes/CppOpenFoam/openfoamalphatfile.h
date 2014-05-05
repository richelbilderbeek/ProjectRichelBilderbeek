#ifndef RIBI_OPENFOAMALPHATFILE_H
#define RIBI_OPENFOAMALPHATFILE_H

#include <array>
#include <iosfwd>
#include <vector>
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM alphat file
struct AlphatFile
{
  explicit AlphatFile(
    const Header header = GetDefaultHeader()
  ) noexcept;

  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }

  void SetBoundaryField(const std::string& boundary_field) noexcept { m_boundary_field = boundary_field; }
  void SetDimensions(const std::array<int,7>& dimensions) noexcept { m_dimensions = dimensions; }
  void SetInternalField(const std::string& internal_field) noexcept { m_internal_field = internal_field; }

  private:

  std::string m_boundary_field;
  std::array<int,7> m_dimensions;

  ///The OpenFOAM header
  Header m_header;
  std::string m_internal_field;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const AlphatFile& f) noexcept;
};

std::ostream& operator<<(std::ostream& os, const AlphatFile& f) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMALPHATFILE_H
