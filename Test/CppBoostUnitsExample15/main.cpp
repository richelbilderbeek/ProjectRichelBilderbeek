#include <iostream>

#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>

namespace boost {
  namespace units {
    typedef derived_dimension<boost::units::amount_base_dimension,1>::type sulfide_molecule_amount_dimension;
  } // namespace units
} // namespace boost


namespace boost {
  namespace units {
    namespace si {
      typedef unit<sulfide_molecule_amount_dimension,si::system> sulfide_molecule_amount;
      BOOST_UNITS_STATIC_CONSTANT(sulfide_molecules_mol,sulfide_molecule_amount);
    } // namespace si
  } // namespace units
} //namespace boost

int main()
{
  using boost::units::quantity;
  using boost::units::si::sulfide_molecule_amount;
  using boost::units::si::sulfide_molecules_mol;
  typedef quantity<sulfide_molecule_amount> SulfideMoleculeAmount;

  const SulfideMoleculeAmount s{1.0 * sulfide_molecules_mol};

  std::cout
    << "Number of sulfide molecules: " << s << '\n';
}

/*

Number of sulfide molecules: 1 mol
Press <RETURN> to close this window...

*/
