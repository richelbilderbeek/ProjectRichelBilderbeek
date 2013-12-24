#include <cassert>
#include <iostream>
#include <iomanip>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/systems/si/mass.hpp>
#include <boost/units/systems/si/mass_density.hpp>
#include <boost/units/systems/si/volume.hpp>
#include <boost/units/systems/si/io.hpp>
#pragma GCC diagnostic pop

struct SteelBar
{
  static const boost::units::quantity<boost::units::si::mass_density> m_density;
};

const boost::units::quantity<boost::units::si::mass_density> SteelBar::m_density(
  8000.0 * boost::units::si::kilogrammes_per_cubic_metre);

int main()
{
  //Increase readability
  typedef boost::units::quantity<boost::units::si::mass_density> MassDensity;
  typedef boost::units::quantity<boost::units::si::mass> Mass;
  typedef boost::units::quantity<boost::units::si::volume> Volume;
  using boost::units::si::kilogram;
  using boost::units::si::kilogrammes_per_cubic_metre;
  using boost::units::si::cubic_meter;

  const double d = 8000.0; //Density of stainless steel in kg/m^2
  const double v = 0.01;   //One litre = 0.01 m^2

  const MassDensity mass_density(d * boost::units::si::kilogrammes_per_cubic_metre);
  const Volume volume(v * boost::units::si::cubic_meter);
  const Mass mass(volume * mass_density);

  //Display law
  std::cout
    << "m = V * d" << "\n"
    << "m: " << mass << "\n"
    << "V: " << volume << "\n"
    << "d: " << mass_density << "\n";

  //Check if calculating the force from the plain doubles is identical
  const Mass mass_expected(d * v * kilogram);
  assert(mass == mass_expected);
}
