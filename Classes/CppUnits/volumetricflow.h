#ifndef VOLUMETRICFLOW_H
#define VOLUMETRICFLOW_H

#include <boost/units/systems/si.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#pragma GCC diagnostic pop

namespace boost {
  namespace units {
    typedef derived_dimension<
      length_base_dimension,3,
      time_base_dimension,-1
    >::type volumetric_flow_dimension;
  } // namespace units
} // namespace boost

namespace boost {
  namespace units {
    namespace si {
      typedef unit<volumetric_flow_dimension,si::system> volumetric_flow;
      BOOST_UNITS_STATIC_CONSTANT(cubic_meter_per_second,volumetric_flow);
      BOOST_UNITS_STATIC_CONSTANT(cubic_meters_per_second,volumetric_flow);
      BOOST_UNITS_STATIC_CONSTANT(cubic_metre_per_second,volumetric_flow);
      BOOST_UNITS_STATIC_CONSTANT(cubic_metres_per_second,volumetric_flow);
    } // namespace si
  } // namespace units
} //namespace boost

namespace ribi {
  namespace units {
    #ifndef NDEBUG
    void TestVolumetricFlow() noexcept;
    #endif
  } //~namespace units
} //~namespace ribi

#endif // VOLUMETRICFLOW_H
