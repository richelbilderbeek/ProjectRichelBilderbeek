#ifndef RIBI_TRIANGLEMESHWINDINGS_H
#define RIBI_TRIANGLEMESHWINDINGS_H

#include <string>
#include <vector>
#include "trianglemeshwinding.h"

namespace ribi {
namespace trim {

struct Windings
{
  Windings() {}
  const std::vector<Winding> GetAll() const noexcept;
  const std::string ToStr(const Winding winding) const noexcept;
};

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHWINDINGS_H
