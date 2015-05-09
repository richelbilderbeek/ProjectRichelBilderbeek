#ifndef NDEBUG
#include "massflow.h"

#include <boost/units/io.hpp>
#include <sstream>

void ribi::units::TestMassFlow() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using MassFlow = boost::units::quantity<boost::units::si::mass_flow>;
  using Mass = boost::units::quantity<boost::units::si::mass>;
  using Time = boost::units::quantity<boost::units::si::time>;
  //MassFlow has unit mass per second, 'kg s^-1'
  {
    const MassFlow phi_m{
        1.0
      * boost::units::si::kilogram / boost::units::si::second
    };
    std::stringstream s;
    s << phi_m;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 7,7) == "kg s^-1");
  }
  //MassFlow can be obtained by dividing a mass by a time unit
  {
    const Mass mass{1.0 * boost::units::si::kilogram};
    const Time time{1.0 * boost::units::si::second};
    const MassFlow phi_m{mass / time};
  }
  /*
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
  typedef quantity<volume> Volume;
  typedef quantity<mass_density> Density;
  typedef quantity<time> Time;
  typedef quantity<mass_flow> MassFlow;


  const Volume v(2.0 * deci * meter * deci * meter * deci * meter); //2.0 liter = 2.0 decimeter^3
  const Time t(3.0 * second);
  const VolumeFlow phi_v(v / t);
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
  */
}
#endif

