#ifndef MASSDENSITY_H
#define MASSDENSITY_H

// Mass per square meter
//#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/mass_density.hpp>

/*
#include <iosfwd>
#include <boost/units/systems/si.hpp>


namespace boost {
  namespace units {
    typedef derived_dimension<
      mass_base_dimension,1,
      length_base_dimension,-2
    >::type mass_density_dimension;
  } // ~namespace units
} // ~namespace boost

namespace boost {
  namespace units {
    namespace si {

      using mass_density = unit<mass_density_dimension,si::system>;
      BOOST_UNITS_STATIC_CONSTANT(mass_per_square_meter,mass_density);
      BOOST_UNITS_STATIC_CONSTANT(mass_per_square_meters,mass_density);

      using MassDensity = boost::units::quantity<boost::units::si::mass_density>;
      std::istream& operator>>(std::istream& is,SpeciesDensity& sd);


    } // ~namespace si
  } // ~namespace units
} // ~namespace boost

*/

namespace ribi {
  namespace units {

    #ifndef NDEBUG
    void TestMassDensity() noexcept;
    #endif

    //using MassDensity = boost::units::quantity<boost::units::si::mass_density>;

    //std::string ToStr(const SpeciesDensity& density) noexcept;
    //SpeciesDensity ToSpeciesDensity(const std::string& s) noexcept;

  } //~namespace units
} //~namespace ribi

#endif // MASSDENSITY_H
