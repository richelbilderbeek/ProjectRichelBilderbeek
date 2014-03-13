#include "aafmolecule.h"

#include "aafbond.h"

boost::shared_ptr<ribi::TextCanvas> ribi::aaf::Molecule::ToTextCanvas() const noexcept
{
  boost::shared_ptr<TextCanvas> canvas;

  const auto l(GetAverageBondLength());
  //Map atoms to integer positions

  return canvas;
}
