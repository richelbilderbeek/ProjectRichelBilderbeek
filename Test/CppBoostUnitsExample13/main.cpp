#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#pragma GCC diagnostic pop
int main()
{
  using boost::units::quantity;
  using boost::units::si::length;
  using boost::units::si::meter;
  using boost::units::si::milli;
  typedef quantity<length> Length;

  //This value is read from file
  const double x_in_mm = 1.0;

  //Add units
  const Length x(x_in_mm * milli * meter);

  const double x_again_in_m  = x / meter; //Works
  const double x_again_in_mm = x / (milli * meter); //Why doesn't this?

  assert(x_in_mm == x_again_in_mm);
}
