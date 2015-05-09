#ifndef NDEBUG
#include "speciesdensity.h"

#include <boost/units/io.hpp>

#include <sstream>

void ribi::units::TestSpeciesDensity() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using SpeciesDensity = boost::units::quantity<boost::units::si::species_density>;
  //Species density is in species per square meter
  {
    const SpeciesDensity d{1.0 * boost::units::si::species_per_square_meter};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 4, 4) == "m^-2");
  }
  //Species density can be multiplied by an area to obtain the number of species
  {
    using Area = boost::units::quantity<boost::units::si::area>;
    const SpeciesDensity d(0.1 * boost::units::si::species_per_square_meter);
    const Area a(123.4 * boost::units::si::square_meter);
    const auto n = d * a;
    std::stringstream s;
    s << n;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 13, 13) == "dimensionless");
  }
}
#endif
