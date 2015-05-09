#include "moleculeamount.h"

#ifndef NDEBUG
#include "units.h"

#include <boost/units/io.hpp>
#include <sstream>

#include "moleculeamount.h"

void ribi::units::TestMoleculeAmount() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using MoleculeAmount = boost::units::quantity<boost::units::si::molecule_amount>;
  //Can add molecule amounts
  {
    const MoleculeAmount a{1.0 * boost::units::si::molecules_mol};
    const MoleculeAmount b{1.0 * boost::units::si::molecules_mol};
    a + b;
  }
  //Molecule amounts are in mole
  {
    using MoleculeAmount = boost::units::quantity<boost::units::si::molecule_amount>;
    const MoleculeAmount a{1.0 * boost::units::si::molecules_mol};
    std::stringstream s;
    s << a;
    const std::string t{s.str()};
    assert(!t.empty());
    assert(t.substr(t.size()-3,3) == "mol");
  }
}
#endif
