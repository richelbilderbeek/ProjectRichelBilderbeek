#ifndef AAFMOLECULEFACTORY_H
#define AAFMOLECULEFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/graph/adjacency_list.hpp>

#include "aafatom.h"
#include "aafbond.h"
#include "aafmolecule.h"
#include "aafaminoacid.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace aaf {

struct MoleculeFactory
{
  MoleculeFactory() {}
  boost::shared_ptr<Molecule> Create(const AminoAcid a) const noexcept;

  private:
  boost::shared_ptr<Molecule> CreateGlycine() const noexcept;
};

} //~namespace aaf
} //~namespace ribi

#endif // AAFMOLECULEFACTORY_H
