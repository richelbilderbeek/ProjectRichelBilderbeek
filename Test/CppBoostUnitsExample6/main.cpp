#include <iostream>
#include <iomanip>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>
#include <boost/units/base_units/angle/radian.hpp>
#include <boost/units/systems/si/io.hpp>
#pragma GCC diagnostic pop

int main()
{
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  using boost::units::si::radians;
  const double pi = boost::math::constants::pi<double>();
  const Angle delta(2.0 * pi * radians / 16.0);
  const Angle j(2.0 * pi * radians);
  std::cout << std::setprecision(20);
  for (Angle i(0.0 * pi * radians); i<j; i+=delta)
  {
    std::cout << "sin(" << i << ") = " << std::sin(i.value()) << '\n';
  }
}
