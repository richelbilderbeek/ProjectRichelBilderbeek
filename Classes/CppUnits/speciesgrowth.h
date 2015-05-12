#ifndef SPECIESGROWTH_H
#define SPECIESGROWTH_H

//Species growth:
// The change in species density per time

#include "speciesdensity.h"
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
      length_base_dimension,-2,
      time_base_dimension,-1
    >::type species_growth_dimension;
  } // namespace units
} // namespace boost

namespace boost {
  namespace units {
    namespace si {
      typedef unit<species_growth_dimension,si::system> species_growth;
      BOOST_UNITS_STATIC_CONSTANT(species_per_square_meter_per_second,species_growth);

      using SpeciesGrowth = boost::units::quantity<boost::units::si::species_growth>;
      std::istream& operator>>(std::istream& is,SpeciesGrowth& sd);

    } // namespace si
  } // namespace units
} //namespace boost

namespace ribi {
  namespace units {

    using SpeciesGrowth = boost::units::quantity<boost::units::si::species_growth>;

    #ifndef NDEBUG
    void TestSpeciesGrowth() noexcept;
    #endif
  } //~namespace units
} //~namespace ribi



#endif // SPECIESGROWTH_H
