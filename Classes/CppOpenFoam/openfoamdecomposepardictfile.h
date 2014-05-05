#ifndef RIBI_OPENFOAMDECOMPOSEPARDICTFILE_H
#define RIBI_OPENFOAMDECOMPOSEPARDICTFILE_H

#include <iosfwd>
#include <vector>
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM thermophysicalProperties file
struct DecomposeParDictFile
{
  explicit DecomposeParDictFile(
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

  friend std::ostream& operator<<(std::ostream& os, const DecomposeParDictFile& f) noexcept;
};

std::ostream& operator<<(std::ostream& os, const DecomposeParDictFile& f) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMDECOMPOSEPARDICTFILE_H
