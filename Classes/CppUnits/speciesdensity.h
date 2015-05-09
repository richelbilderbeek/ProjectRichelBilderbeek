#ifndef SPECIESDENSITY_H
#define SPECIESDENSITY_H

#include <boost/units/systems/si.hpp>
//#include <boost/units/systems/si/prefixes.hpp>

namespace boost {
  namespace units {
    typedef derived_dimension<length_base_dimension,-2>::type species_density_dimension;
  } // namespace units
} // namespace boost

namespace boost {
  namespace units {
    namespace si {
      typedef unit<species_density_dimension,si::system> species_density;
      BOOST_UNITS_STATIC_CONSTANT(species_per_square_meter,species_density);
      BOOST_UNITS_STATIC_CONSTANT(species_per_square_meters,species_density);
    } // namespace si
  } // namespace units
} //namespace boost

#ifndef NDEBUG
namespace ribi {
  namespace units {
    ///All I can do on them, is test them
    void TestSpeciesDensity() noexcept;
  } //~namespace units
} //~namespace ribi
#endif

#endif // SPECIESDENSITY_H
