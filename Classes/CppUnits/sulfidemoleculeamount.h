#ifndef SULFIDEMOLECULEAMOUNT_H
#define SULFIDEMOLECULEAMOUNT_H

#include <boost/units/systems/si.hpp>

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

#ifndef NDEBUG
namespace ribi {
  namespace units {
    ///All I can do on them, is test them
    void TestSulfideMoleculeAmount() noexcept;
  } //~namespace units
} //~namespace ribi
#endif

#endif // SULFIDEMOLECULEAMOUNT_H
