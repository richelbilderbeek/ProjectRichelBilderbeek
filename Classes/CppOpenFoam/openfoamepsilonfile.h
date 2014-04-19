#ifndef OPENFOAMEPSILONFILE_H
#define OPENFOAMEPSILONFILE_H

#include <iosfwd>
#include <vector>
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM epsilon file
struct EpsilonFile
{
  explicit EpsilonFile(
    const Header header = GetDefaultHeader()
  );

  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }

  private:

  ///The OpenFOAM header
  Header m_header;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const EpsilonFile& f) noexcept;
};

std::ostream& operator<<(std::ostream& os, const EpsilonFile& f) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMEPSILONFILE_H
