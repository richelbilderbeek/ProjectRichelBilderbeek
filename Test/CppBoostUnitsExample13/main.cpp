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

  //const double x_again_in_m  = x / meter; //Works

  //const double x_again_in_mm {
  //  x / (milli * meter)
  //}; //Why doesn't this?

  //Thanks to Gavin Lambert for this solution
  const double x_again_in_mm {
    x / (meter * conversion_factor(milli * meter, meter))
  };

  assert(x_in_mm == x_again_in_mm);

  OtherApproach();
}


namespace millimeter_system
{
  typedef boost::units::scaled_base_unit<boost::units::si::meter_base_unit, boost::units::scale<10, boost::units::static_rational<-3>>> millimeter_base_unit;

  typedef boost::units::make_system<millimeter_base_unit>::type system;
  typedef boost::units::unit<boost::units::length_dimension, system> length;

  BOOST_UNITS_STATIC_CONSTANT(millimeter, length);
  BOOST_UNITS_STATIC_CONSTANT(millimeters, length);
}

typedef boost::units::quantity<millimeter_system::length> quantity_millimeter;
typedef boost::units::make_system<millimeter_system::millimeter_base_unit>::type mm_system;
typedef boost::units::unit<boost::units::length_dimension,mm_system> millimeter_unit;

BOOST_UNITS_STATIC_CONSTANT(millimeters, millimeter_unit);

void OtherApproach()
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

  typedef quantity<millimeter_unit> LengthInMm;
  using millimeter_system::millimeter;
  using millimeter_system::millimeters;

  //Thanks to Gavin Lambert for this solution
  const double x_again_in_mm = LengthInMm(x) / millimeters;

  assert(x_in_mm == x_again_in_mm);
}
