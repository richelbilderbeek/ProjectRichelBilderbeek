#ifndef MASSFLOW_H
#define MASSFLOW_H

#include <boost/units/systems/si.hpp>

namespace boost {
  namespace units {
    typedef derived_dimension<
        mass_base_dimension,1,
        time_base_dimension,-1
      >::type mass_flow_dimension
    ;
  } // namespace units
} // namespace boost

namespace boost {
  namespace units {
    namespace si {
      typedef unit<mass_flow_dimension,si::system> mass_flow;
      BOOST_UNITS_STATIC_CONSTANT(kilogram_per_second,mass_flow);
      BOOST_UNITS_STATIC_CONSTANT(kilogramme_meters_per_second,mass_flow);
      BOOST_UNITS_STATIC_CONSTANT(kilograms_metre_per_second,mass_flow);
      BOOST_UNITS_STATIC_CONSTANT(kilogrammes_metres_per_second,mass_flow);
    } // namespace si
  } // namespace units
} //namespace boost

#ifndef NDEBUG
namespace ribi {
  namespace units {
    ///All I can do on them, is test them
    void TestMassFlow() noexcept;
  } //~namespace units
} //~namespace ribi
#endif

#endif // MASSFLOW_H
