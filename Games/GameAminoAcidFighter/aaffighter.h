#ifndef AAFFIGHTER_H
#define AAFFIGHTER_H

#include "aafmolecule.h"

namespace ribi {

struct TextCanvas;

namespace aaf {

///A fighter; a player; an amino acid controlled by player or computer
struct Fighter
{
  Fighter(const boost::shared_ptr<Molecule>& molecule);

  boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  boost::shared_ptr<Molecule> m_molecule;
};

} //~namespace aaf
} //~namespace ribi

#endif // AAFFIGHTER_H
