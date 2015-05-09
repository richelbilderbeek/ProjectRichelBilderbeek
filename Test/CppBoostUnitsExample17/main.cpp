#include <iostream>

#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>

namespace boost {
  namespace units {
    //These tags enable to recognize that sulfide molecules are not hydrogen molecules
    struct sulfide_molecule_amount_dimension_tag : base_dimension<boost::units::amount_base_dimension,1>{};
    struct hydrogen_molecule_amount_dimension_tag : base_dimension<boost::units::amount_base_dimension,1>{};


    typedef derived_dimension<sulfide_molecule_amount_dimension_tag,1>::type sulfide_molecule_amount_dimension;
    typedef derived_dimension<hydrogen_molecule_amount_dimension_tag,1>::type hydrogen_molecule_amount_dimension;
  } // namespace units
} // namespace boost


namespace boost {
  namespace units {
    namespace si {
      typedef unit<sulfide_molecule_amount_dimension,si::system> sulfide_molecule_amount;
      typedef unit<hydrogen_molecule_amount_dimension,si::system> hydrogen_molecule_amount;
      BOOST_UNITS_STATIC_CONSTANT(sulfide_molecules_mol,sulfide_molecule_amount);
      BOOST_UNITS_STATIC_CONSTANT(hydrogen_molecules_mol,hydrogen_molecule_amount);
    } // namespace si
  } // namespace units
} //namespace boost

int main()
{
  using boost::units::quantity;
  using boost::units::si::hydrogen_molecule_amount;
  using boost::units::si::sulfide_molecule_amount;
  using boost::units::si::hydrogen_molecules_mol;
  using boost::units::si::sulfide_molecules_mol;
  using SulfideMoleculeAmount = quantity<sulfide_molecule_amount>;
  using HydrogenMoleculeAmount = quantity<hydrogen_molecule_amount>;

  const SulfideMoleculeAmount s{1.0 * sulfide_molecules_mol};
  const HydrogenMoleculeAmount h{1.0 * hydrogen_molecules_mol};

  std::cout
    << "Number of hydrogen molecules: " << h << '\n'
    << "Number of sulfide molecules: " << s << '\n'
    //<< "Number of molecules: " << (s + h) << '\n' //Won't compile
  ;

}

/*

Number of hydrogen molecules: 1 mol
Number of sulfide molecules: 1 mol
Number of molecules: 2 mol
Press <RETURN> to close this window...

*/
