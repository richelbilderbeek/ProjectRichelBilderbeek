#ifndef NDEBUG
#include "hydrogenmoleculeamount.h"

#include <boost/units/io.hpp>
#include <sstream>


void ribi::units::TestHydrogenMoleculeAmount() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using HydrogenMoleculeAmount = boost::units::quantity<boost::units::si::hydrogen_molecule_amount>;
  //Hydrogen molecule amounts can be displayed
  {
    const HydrogenMoleculeAmount sa{1.0 * boost::units::si::hydrogen_molecules_mol};
    std::stringstream s;
    s << sa;
    const std::string t{s.str()};
    assert(!t.empty());
  }
  //#define FIX_ISSUE_999
  #ifdef FIX_ISSUE_999
  //Hydrogen molecule amounts are in mole
  {
    const HydrogenMoleculeAmount sa{1.0 * boost::units::si::hydrogen_molecules_mol};
    std::stringstream s;
    s << sa;
    const std::string t{s.str()};
    assert(!t.empty());
    std::cout << t << std::endl;
    assert(t.substr(t.size()-3,3) == "mol");
  }
  #endif
  //Can add hydrogen molecule amounts
  {
    const double a{1.0};
    const double b{2.0};
    const double c{a + b};
    const HydrogenMoleculeAmount sa{a * boost::units::si::hydrogen_molecules_mol};
    const HydrogenMoleculeAmount sb{b * boost::units::si::hydrogen_molecules_mol};
    const HydrogenMoleculeAmount sc{sa + sb};
    assert(sc == HydrogenMoleculeAmount{c * boost::units::si::hydrogen_molecules_mol});
  }
}
#endif
