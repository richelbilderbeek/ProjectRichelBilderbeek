#ifndef NDEBUG
#include "volumetricflow.h"

#include <boost/units/io.hpp>
#include <sstream>
#include "massflow.h"

void ribi::units::TestVolumetricFlow() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using VolumetricFlow = boost::units::quantity<boost::units::si::volumetric_flow>;
  using Volume = boost::units::quantity<boost::units::si::volume>;
  using Time = boost::units::quantity<boost::units::si::time>;
  //VolumetricFlow has unit cubic metre per second, 'm^3 s^-1'
  {
    const VolumetricFlow phi_v{
        1.0
      * boost::units::si::cubic_meter / boost::units::si::second
    };
    std::stringstream s;
    s << phi_v;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 8,8) == "m^3 s^-1");
  }
  //VolumetricFlow can be obtained by dividing a volume by a time unit
  {
    const Volume volume{1.0 * boost::units::si::cubic_meter};
    const Time time{1.0 * boost::units::si::second};
    const VolumetricFlow phi_v{volume / time};
  }

  //VolumetricFlow can be converted to MassFlow
  {
    using Volume = boost::units::quantity<boost::units::si::volume>;
    using MassFlow = boost::units::quantity<boost::units::si::mass_flow>;
    using Density = boost::units::quantity<boost::units::si::mass_density>;

    const Volume v{1.0 * boost::units::si::cubic_meter};
    const Time t{1.0 * boost::units::si::second};
    const VolumetricFlow phi_v{v / t};
    const Density d{
      1.0
       * boost::units::si::kilogram / boost::units::si::cubic_meter
    };
    const MassFlow phi_m{phi_v * d};
  }

}
#endif

