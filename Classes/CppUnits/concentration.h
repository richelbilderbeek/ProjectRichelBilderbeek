#ifndef CONCENTRATION_H
#define CONCENTRATION_H

///Mole per cubic meter
#include <boost/units/systems/si.hpp>

namespace boost {
  namespace units {
    using concentration_dimension
      = derived_dimension<
        amount_base_dimension,1,
        length_base_dimension,-3
      >::type;
  } // ~namespace units
} // ~namespace boost

namespace boost {
  namespace units {
    namespace si {

      using concentration = unit<concentration_dimension,si::system>;
      BOOST_UNITS_STATIC_CONSTANT(mol_per_cubic_meter,concentration);
      BOOST_UNITS_STATIC_CONSTANT(mole_per_cubic_meter,concentration);

      using Concentration = boost::units::quantity<boost::units::si::concentration>;
      std::istream& operator>>(std::istream& is,Concentration& sd);


    } // ~namespace si
  } // ~namespace units
} // ~namespace boost


namespace ribi {
  namespace units {
    using Concentration = boost::units::si::Concentration;
    #ifndef NDEBUG
    void TestConcentration() noexcept;
    #endif
  } //~namespace units
} //~namespace ribi


#endif // CONCENTRATION_H
