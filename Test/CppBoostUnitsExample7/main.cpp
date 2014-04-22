#include <cassert>
#include <iostream>
#include <iomanip>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/systems/si/force.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <boost/units/systems/si/acceleration.hpp>
#include <boost/units/systems/si/io.hpp>
#pragma GCC diagnostic pop

int main()
{
  //Increase readability
  typedef boost::units::quantity<boost::units::si::acceleration> Acceleration;
  typedef boost::units::quantity<boost::units::si::force> Force;
  typedef boost::units::quantity<boost::units::si::mass> Mass;
  using boost::units::si::kilogram;
  using boost::units::si::meters_per_second_squared;
  using boost::units::si::newton;

  //Plain doubles
  const double m = 5.0;
  const double a = 2.0;

  //Convert doubles to their unit-bearing equivalents
  const Mass mass(m * kilogram);
  const Acceleration acceleration(a * meters_per_second_squared);

  //Newton's second law of motion
  const Force force(mass * acceleration);

  //Display Newton's second law of motion
  std::cout
    << "F = m * a" << "\n"
    << "F: " << force << "\n"
    << "m: " << mass << "\n"
    << "a: " << acceleration << "\n";


  //Check if calculating the force from the plain doubles is identical
  const Force force_expected(m * a * newton);
  assert(force == force_expected);
}
