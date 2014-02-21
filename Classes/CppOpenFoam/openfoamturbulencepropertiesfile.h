#ifndef OPENFOAMTURBULENCEPROPERTIESFILE_H
#define OPENFOAMTURBULENCEPROPERTIESFILE_H

#include <iosfwd>
#include <vector>
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM turbulenceProperties file
struct TurbulencePropertiesFile
{
  explicit TurbulencePropertiesFile(
    const Header header = GetDefaultHeader()
  );

  static const Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }

  void SetSimulationType(const std::string& simulation_type) noexcept { m_simulation_type = simulation_type; }

  private:

  ///The OpenFOAM header
  Header m_header;

  std::string m_simulation_type;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const TurbulencePropertiesFile& f);
};

std::ostream& operator<<(std::ostream& os, const TurbulencePropertiesFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMTURBULENCEPROPERTIESFILE_H
