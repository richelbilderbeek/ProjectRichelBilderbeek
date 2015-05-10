#ifndef NDEBUG
#include "units.h"

#include <boost/units/io.hpp>
#include <sstream>

#include "concentration.h"
#include "speciesdensity.h"
#include "moleculeamount.h"
#include "hydrogenmoleculeamount.h"
#include "sulfidemoleculeamount.h"
#include "massflow.h"
#include "volumetricflow.h"
#include "testtimer.h"

void ribi::units::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    TestConcentration();
    TestHydrogenMoleculeAmount();
    TestMassFlow();
    TestMoleculeAmount();
    TestSpeciesDensity();
    TestSulfideMoleculeAmount();
    TestVolumetricFlow();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);

  #ifdef MUST_NOT_COMPILE_CREATE_HYDROGEN_FROM_SULFIDE
  //Cannot create hydrogen from sulfide
  {
    using HydrogenMoleculeAmount = boost::units::quantity<boost::units::si::hydrogen_molecule_amount>;
    const HydrogenMoleculeAmount h{1.0 * boost::units::si::sulfide_molecules_mol}; //Must fail
  }
  #endif
  #ifdef MUST_NOT_COMPILE_CREATE_SULFIDE_FROM_HYDROGEN
  //Cannot create sulfide from hydrogen
  {
    using SulfideMoleculeAmount = boost::units::quantity<boost::units::si::sulfide_molecule_amount>;
    const SulfideMoleculeAmount s{1.0 * boost::units::si::hydrogen_molecules_mol};
  }
  #endif
  #ifdef MUST_NOT_COMPILE_ADD_HYDROGEN_AND_SULFIDE
  //Cannot add hydrogen and sulfide molecule amounts
  {
    using HydrogenMoleculeAmount = boost::units::quantity<boost::units::si::hydrogen_molecule_amount>;
    using SulfideMoleculeAmount = boost::units::quantity<boost::units::si::sulfide_molecule_amount>;
    const HydrogenMoleculeAmount h{1.0 * boost::units::si::hydrogen_molecules_mol};
    const SulfideMoleculeAmount s{1.0 * boost::units::si::sulfide_molecules_mol};
    h + s; //Must fail
  }
  #endif
}
#endif

