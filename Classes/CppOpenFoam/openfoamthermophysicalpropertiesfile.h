#ifndef OPENFOAMTHERMOPHYSICALPROPERTIESFILE_H
#define OPENFOAMTHERMOPHYSICALPROPERTIESFILE_H

#include <iosfwd>
#include <vector>
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM thermophysicalProperties file
struct ThermophysicalPropertiesFile
{
  explicit ThermophysicalPropertiesFile(
    const Header header = GetDefaultHeader()
  );

  static const Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }

  void SetMixture(const std::string& mixture) noexcept { m_mixture = mixture; }
  void SetThermoType(const std::string& thermo_type) noexcept { m_thermo_type = thermo_type; }

  private:

  ///The OpenFOAM header
  Header m_header;

  std::string m_mixture;
  std::string m_thermo_type;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const ThermophysicalPropertiesFile& f);
};

std::ostream& operator<<(std::ostream& os, const ThermophysicalPropertiesFile& f);

} //~namespace foam
} //~namespace ribi




#endif // OPENFOAMTHERMOPHYSICALPROPERTIESFILE_H
