#ifndef NDEBUG
#include "units.h"
#include "hydrogenmoleculeamount.h"
#include "sulfidemoleculeamount.h"

void ribi::units::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  //Can add molecule amounts

  //Sulfide molecule amounts
  {
    using SulfideMoleculeAmount = boost::units::quantity<boost::units::si::sulfide_molecule_amount>;
    //Sulfide molecule amounts can be displayed
    {
      const SulfideMoleculeAmount sa{1.0 * boost::units::si::sulfide_molecules_mol};
      std::stringstream s;
      s << sa;
      const std::string t{s.str()};
      assert(!t.empty());
    }
    //#define FIX_ISSUE_999
    #ifdef FIX_ISSUE_999
    //Sulfide molecule amounts are in mole
    {
      const SulfideMoleculeAmount sa{1.0 * boost::units::si::sulfide_molecules_mol};
      std::stringstream s;
      s << sa;
      const std::string t{s.str()};
      assert(!t.empty());
      std::cout << t << std::endl;
      assert(t.substr(t.size()-3,3) == "mol");
    }
    #endif
    //Can add sulfide molecule amounts
    {
      const double a{1.0};
      const double b{2.0};
      const double c{a + b};
      const SulfideMoleculeAmount sa{a * boost::units::si::sulfide_molecules_mol};
      const SulfideMoleculeAmount sb{b * boost::units::si::sulfide_molecules_mol};
      const SulfideMoleculeAmount sc{sa + sb};
      assert(sc == SulfideMoleculeAmount{c * boost::units::si::sulfide_molecules_mol});
    }
  }
  //Hydrogen molecule amounts
  {
    using HydrogenMoleculeAmount = boost::units::quantity<boost::units::si::hydrogen_molecule_amount>;
    //Sulfide molecule amounts can be displayed
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
  //Cannot add hydrogen and sulfide molecule amounts
  assert(!"DON");
}
#endif
