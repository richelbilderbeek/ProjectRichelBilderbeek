#include <iostream>
#include <boost/math/constants/constants.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/physical_dimensions/area.hpp>

int main()
{
  using namespace boost::units;
  using namespace boost::units::si;
  const double pi = boost::math::constants::pi<double>();
  const quantity<length> my_ray(2.0*micro*meter);
  const quantity<area> my_area(my_ray*my_ray*pi);

    std::cout
      << "ray = " << my_ray <<  '\n'
      << "area = " << my_area <<  '\n';
}
