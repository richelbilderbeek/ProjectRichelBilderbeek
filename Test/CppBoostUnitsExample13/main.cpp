#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#pragma GCC diagnostic pop

void OtherApproach();

int main()
{
  using boost::units::conversion_factor;
  using boost::units::quantity;
  using boost::units::si::length;
  using boost::units::si::meter;
  using boost::units::si::milli;
  typedef quantity<length> Length;

  //This value is read from file
  const double x_in_mm = 1.0;

  //Add units
  const Length x(x_in_mm * milli * meter);

  //const double x_again_in_m  = x / meter; //Works (in Boost 1.54)

  //const double x_again_in_mm {
  //  x / (milli * meter)
  //}; //Why doesn't this compile (in Boost 1.54)?

  //Thanks to Gavin Lambert for this solution
  const double x_again_in_mm {
    (x / meter) * conversion_factor(meter, milli * meter)
  };

  assert(x_in_mm == x_again_in_mm);

  OtherApproach();
}

typedef boost::units::scaled_base_unit<
  boost::units::si::meter_base_unit,
  boost::units::scale<10, boost::units::static_rational<-3>>
> millimeter_base_unit;

typedef boost::units::make_system<millimeter_base_unit>::type mm_system;
typedef boost::units::unit<boost::units::length_dimension,mm_system> millimeter_unit;
BOOST_UNITS_STATIC_CONSTANT(millimeters, millimeter_unit);
typedef boost::units::quantity<millimeter_unit> LengthInMm;

void OtherApproach()
{
  using boost::units::si::meter;
  using boost::units::si::milli;
  typedef boost::units::quantity<boost::units::si::length> Length;

  //This value is read from file
  const double x_in_mm = 1.0;

  //Add units
  const Length x(x_in_mm * milli * meter);

  //Thanks to Gavin Lambert for this solution
  const double x_again_in_mm = LengthInMm(x) / millimeters;

  assert(x_in_mm == x_again_in_mm);
}
