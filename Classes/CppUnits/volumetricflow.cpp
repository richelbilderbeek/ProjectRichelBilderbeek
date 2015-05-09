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



  ///Question: what is the mass flow of a liquid with density 5.0 gram per cubic centimeter
  ///that flows with 2.0 liter per 3.0 seconds?

  using boost::units::quantity;
  using boost::units::si::cubic_meter;
  using boost::units::si::deci;
  using boost::units::si::centi;
  using boost::units::si::second;
  using boost::units::si::meter;
  using boost::units::si::cubic_meter_per_second;
  using boost::units::si::volume;
  using boost::units::si::mass_flow;
  using boost::units::si::volumetric_flow;
  using boost::units::si::time;
  using boost::units::si::mass_density;
  using boost::units::si::kilogram;
  using boost::units::si::kilogram_per_second;
  using boost::units::si::kilogrammes_per_cubic_metre;
  using Volume = boost::units::quantity<boost::units::si::volume>;
  typedef quantity<mass_density> Density;
  typedef quantity<time> Time;
  using VolumetricFlow = boost::units::quantity<boost::units::si::volumetric_flow>;
  typedef quantity<mass_flow> MassFlow;


  const Volume v(2.0 * deci * meter * deci * meter * deci * meter); //2.0 liter = 2.0 decimeter^3
  const Time t(3.0 * second);
  const VolumetricFlow phi_v(v / t);

  const Density d(5.0 * 0.001 * kilogram / (1.0 * centi * meter * centi * meter * centi * meter));

  const MassFlow phi_m(
      (phi_v / cubic_meter_per_second)
    * (d / kilogrammes_per_cubic_metre)
    * kilogram_per_second);

  //DOES NOT COMPILE??? If you know how to be able to write this
  //preferred systax, please contact me
  //const MassFlow m(f * d);

  std::cout
    << "Volumetric flow = volume / time\n"
    << "phi_v = V / t\n"
    << "phi_v = " << phi_v << '\n'
    << "V = " << v << '\n'
    << "t = " << t << '\n'
    << '\n'
    << "Mass flow = volume flow * mass density\n"
    << "phi_m = phi_v * d\n"
    << "phi_m = " << phi_m << '\n'
    << "phi_v = " << phi_v << '\n'
    << "d = " << d << '\n';

}
#endif

