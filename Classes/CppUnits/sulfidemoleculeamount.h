#ifndef SULFIDEMOLECULEAMOUNT_H
#define SULFIDEMOLECULEAMOUNT_H

#include <iostream>

#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>

namespace boost {
  namespace units {
    struct sulfide_molecule_amount_dimension_tag : base_dimension<boost::units::amount_base_dimension,1>{};
    typedef derived_dimension<sulfide_molecule_amount_dimension_tag,1>::type sulfide_molecule_amount_dimension;
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

#endif // SULFIDEMOLECULEAMOUNT_H
