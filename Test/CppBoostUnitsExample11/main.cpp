#include <iostream>

#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>

namespace boost {
namespace units {
//RJCB note: cannot use volume_dimension, like this:
//  typedef derived_dimension<volume_dimension,1,
//                            time_base_dimension,-1>::type volumetric_flow_dimension;
//because one is not allowed to mix base_dimensions and non-base_dimensions
//
//From Steven Watanabe at http://comments.gmane.org/gmane.comp.lib.boost.user/70216:
//
//  Use either:
//
//  derived_dimension<length_base_dimension,3,time_base_dimension,-1>::type
//
//  or
//
//  mpl::divides<volume_dimension, time_dimension>::type
/// derived dimension for volumetric_flow : L^3 T^-1
//
typedef derived_dimension<length_base_dimension,3,
                          time_base_dimension,-1>::type volumetric_flow_dimension;
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
} // namespace si
} // namespace units
} //namespace boost

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
int main()
{
  using boost::units::quantity;
  using boost::units::si::cubic_meter;
  using boost::units::si::cubic_meter_per_second;
  using boost::units::si::deci;
  using boost::units::si::meter;
  using boost::units::si::milli;
  using boost::units::si::second;
  using boost::units::si::time;
  using boost::units::si::volume;
  using boost::units::si::volumetric_flow;
  typedef quantity<time> Time;
  typedef quantity<volumetric_flow> Flow;
  typedef quantity<volume> Volume;

  const Volume v(2.0 * cubic_meter);
  const Time t(3.0 * second);
  const Flow f(v / t);

  std::cout
    << "Volumetric flow = volume / time\n"
    << "rho = V / t\n"
    << "rho = " << f << '\n'
    << "V = " << v << '\n'
    << "t = " << t << '\n';
  std::cout
    << '\n'
    << "1 cubic decimeter per minute equals: "
    << Flow(1.0 * deci * meter * deci * meter * deci
  * meter / (60.0 * second))
    << '\n';
}
#pragma GCC diagnostic pop

/*
Volumetric flow = volume / time
rho = V / t
rho = 0.666667 m^3 s^-1
V = 2 m^3
t = 3 s
1 cubic decimeter per minute equals: 1.66667e-005 m^3 s^-1
*/
