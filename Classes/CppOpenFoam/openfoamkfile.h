#ifndef OPENFOAMKFILE_H
#define OPENFOAMKFILE_H

#include <iosfwd>
#include <vector>
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM thermophysicalProperties file
struct KFile
{
  explicit KFile(
    const Header header = GetDefaultHeader()
  );

  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }

  private:
  Header m_header;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const KFile& f) noexcept;
};

std::ostream& operator<<(std::ostream& os, const KFile& f) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMKFILE_H
