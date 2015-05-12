#ifndef CONCENTRATIONCHANGE_H
#define CONCENTRATIONCHANGE_H

//Species growth:
// The change in species density per time

#include "concentration.h"
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
      amount_base_dimension,1,
      length_base_dimension,-3,
      time_base_dimension,-1
    >::type concentration_change_dimension;
  } // namespace units
} // namespace boost

namespace boost {
  namespace units {
    namespace si {
      typedef unit<concentration_change_dimension,si::system> concentration_change;
      BOOST_UNITS_STATIC_CONSTANT(mole_per_cubic_meter_per_second,concentration_change);

      using ConcentrationChange = boost::units::quantity<boost::units::si::concentration_change>;
      std::istream& operator>>(std::istream& is,ConcentrationChange& sd);

    } // namespace si
  } // namespace units
} //namespace boost

#ifndef NDEBUG
namespace ribi {
  namespace units {

    using ConcentrationChange = boost::units::quantity<boost::units::si::concentration_change>;

    ///All I can do on them, is test them
    void TestConcentrationChange() noexcept;
  } //~namespace units
} //~namespace ribi
#endif


#endif // CONCENTRATIONCHANGE_H
