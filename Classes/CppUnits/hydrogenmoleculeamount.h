#ifndef HYDROGENMOLECULEAMOUNT_H
#define HYDROGENMOLECULEAMOUNT_H

#include <boost/units/systems/si.hpp>

namespace boost {
  namespace units {
    struct hydrogen_molecule_amount_dimension_tag : base_dimension<boost::units::amount_base_dimension,1>{};
    typedef derived_dimension<hydrogen_molecule_amount_dimension_tag,1>::type hydrogen_molecule_amount_dimension;
  } // namespace units
} // namespace boost


namespace boost {
  namespace units {
    namespace si {
      typedef unit<hydrogen_molecule_amount_dimension,si::system> hydrogen_molecule_amount;
      BOOST_UNITS_STATIC_CONSTANT(hydrogen_molecules_mol,hydrogen_molecule_amount);
    } // namespace si
  } // namespace units
} //namespace boost

#ifndef NDEBUG
namespace ribi {
  namespace units {
    ///All I can do on them, is test them
    void TestHydrogenMoleculeAmount() noexcept;
  } //~namespace units
} //~namespace ribi
#endif

#endif // HYDROGENMOLECULEAMOUNT_H
