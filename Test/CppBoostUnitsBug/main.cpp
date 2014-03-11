#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/systems/si/prefixes.hpp>      //nano,milli,kilo
#include <boost/units/systems/si/length.hpp>        //meter
#include <boost/units/systems/si/io.hpp>            // <<
#pragma GCC diagnostic pop

int main()
{
  //Works as expected
  {
    const boost::units::quantity<boost::units::si::length> a(
      1.23 * boost::units::si::meter);
    const boost::units::quantity<boost::units::si::length> b(
      1.23 * boost::units::si::milli * boost::units::si::meter);

    const double x = a / boost::units::si::meter;
    const double y = b / boost::units::si::meter;
    assert(x != y && "A meter is not a millimeter");

  }
  //Works as expected
  {
    const boost::units::quantity<boost::units::si::length> a(
      1.23 * boost::units::si::meter);
    const boost::units::quantity<boost::units::si::length> b(
      1.23 * boost::units::si::milli * boost::units::si::meter);

    const double x = a.value();
    const double y = b.value();
    assert(x != y && "A meter is not a millimeter");

  }
  //FAILS
  {
    assert( (1.23 * boost::units::si::meter).value()
      != (1.23 * boost::units::si::milli * boost::units::si::meter).value()
      && "A meter is not a millimeter");
  }
  //FAILS
  {
    const double x = (1.23 * boost::units::si::meter).value();
    const double y = (1.23 * boost::units::si::milli * boost::units::si::meter).value();
    assert(x != y && "A meter is not a millimeter");
  }
}
