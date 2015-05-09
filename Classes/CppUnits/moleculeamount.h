#ifndef MOLECULEAMOUNT_H
#define MOLECULEAMOUNT_H

#include <boost/units/systems/si.hpp>

namespace boost {
  namespace units {
    //1 states that the amount is in moles (of molecules, in this context)
    typedef derived_dimension<boost::units::amount_base_dimension,1>::type molecule_amount_dimension;
  } // namespace units
} // namespace boost


namespace boost {
  namespace units {
    namespace si {
      typedef unit<molecule_amount_dimension,si::system> molecule_amount;
      BOOST_UNITS_STATIC_CONSTANT(molecules_mol,molecule_amount);
    } // namespace si
  } // namespace units
} //namespace boost

#ifndef NDEBUG
namespace ribi {
  namespace units {
    ///All I can do on them, is test them
    void TestMoleculeAmount() noexcept;
  } //~namespace units
} //~namespace ribi
#endif

#endif // MOLECULEAMOUNT_H
