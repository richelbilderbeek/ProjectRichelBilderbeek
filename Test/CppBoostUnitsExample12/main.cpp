#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#pragma GCC diagnostic pop

namespace boost {
namespace units {
typedef derived_dimension<length_base_dimension,3,
                          time_base_dimension,-1>::type volumetric_flow_dimension;

typedef derived_dimension<mass_base_dimension,1,
                          time_base_dimension,-1>::type mass_flow_dimension;
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

typedef unit<mass_flow_dimension,si::system> mass_flow;
BOOST_UNITS_STATIC_CONSTANT(kilogram_per_second,mass_flow);
BOOST_UNITS_STATIC_CONSTANT(kilogramme_meters_per_second,mass_flow);
BOOST_UNITS_STATIC_CONSTANT(kilograms_metre_per_second,mass_flow);
BOOST_UNITS_STATIC_CONSTANT(kilogrammes_metres_per_second,mass_flow);
} // namespace si
} // namespace units
} //namespace boost


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
int main()
{
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
  using Density = boost::units::quantity<boost::units::si::mass_density>;
  using Time = boost::units::quantity<boost::units::si::time>;
  using VolumeFlow = boost::units::quantity<boost::units::si::volumetric_flow>;
  using MassFlow = boost::units::quantity<boost::units::si::mass_flow>;


  const Volume v{2.0 * deci * meter * deci * meter * deci * meter}; //2.0 liter = 2.0 decimeter^3
  const Time t{3.0 * second};
  const VolumeFlow phi_v{v / t};
  const Density d{5.0 * 0.001 * kilogram / (1.0 * centi * meter * centi * meter * centi * meter)};
  const MassFlow phi_m{phi_v * d};

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
#pragma GCC diagnostic pop

/*
Volumetric flow = volume / time
phi_v = V / t
phi_v = 0.000666667 m^3 s^-1
V = 0.002 m^3
t = 3 s

Mass flow = volume flow * mass density
phi_m = phi_v * d
phi_m = 3.33333 kg^3 s^-1
phi_v = 0.000666667 m^3 s^-1
d = 5000 m^-3 kg
*/
