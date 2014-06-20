#ifndef RIBI_TRIANGLEMESHWINDINGS_H
#define RIBI_TRIANGLEMESHWINDINGS_H

#include <string>
#include <vector>
#include "trianglemeshwinding.h"

namespace ribi {
namespace trim {

//No state, no Pimpl
class Windings
{
  friend class Face;
  friend class FaceFactory;
  friend class PointFactory;

  Windings() {}
  std::vector<Winding> GetAll() const noexcept;
  std::string ToStr(const Winding winding) const noexcept;
};

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHWINDINGS_H
