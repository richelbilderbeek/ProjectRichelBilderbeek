#ifndef OPENFOAMRASPROPERTIESFILE_H
#define OPENFOAMRASPROPERTIESFILE_H

#include <iosfwd>
#include <vector>
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM thermophysicalProperties file
struct RasPropertiesFile
{
  explicit RasPropertiesFile(
    const Header& header = GetDefaultHeader()
  );

  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }

  private:

  ///The OpenFOAM header
  Header m_header;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const RasPropertiesFile& f);
};

std::ostream& operator<<(std::ostream& os, const RasPropertiesFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMRASPROPERTIESFILE_H
