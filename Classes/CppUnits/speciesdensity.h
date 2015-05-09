#ifndef SPECIESDENSITY_H
#define SPECIESDENSITY_H

#include <iosfwd>
#include <boost/units/systems/si.hpp>

namespace boost {
  namespace units {
    using species_density_dimension = derived_dimension<length_base_dimension,-2>::type;
  } // ~namespace units
} // ~namespace boost

namespace boost {
  namespace units {
    namespace si {

      using species_density = unit<species_density_dimension,si::system>;
      BOOST_UNITS_STATIC_CONSTANT(species_per_square_meter,species_density);
      BOOST_UNITS_STATIC_CONSTANT(species_per_square_meters,species_density);

      using SpeciesDensity = boost::units::quantity<boost::units::si::species_density>;
      std::istream& operator>>(std::istream& is,SpeciesDensity& sd);


    } // ~namespace si
  } // ~namespace units
} // ~namespace boost

#ifndef NDEBUG
namespace ribi {
  namespace units {

    ///All I can do on them, is test them
    void TestSpeciesDensity() noexcept;

    using SpeciesDensity = boost::units::quantity<boost::units::si::species_density>;

    //std::string ToStr(const SpeciesDensity& density) noexcept;
    //SpeciesDensity ToSpeciesDensity(const std::string& s) noexcept;

  } //~namespace units
} //~namespace ribi
#endif


#endif // SPECIESDENSITY_H
