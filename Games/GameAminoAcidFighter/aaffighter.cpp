#include "aaffighter.h"

ribi::aaf::Fighter::Fighter(const boost::shared_ptr<Molecule>& molecule)
  : m_molecule{molecule}
{
  assert(m_molecule);
}

boost::shared_ptr<ribi::TextCanvas> ribi::aaf::Fighter::ToTextCanvas() const noexcept
{
  assert(m_molecule);
  return m_molecule->ToTextCanvas();
}

