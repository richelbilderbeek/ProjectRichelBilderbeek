#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#pragma GCC diagnostic pop

int main()
{
  using boost::units::quantity;
  using boost::units::si::area;
  using boost::units::si::force;
  using boost::units::si::kilo;
  using boost::units::si::micro;
  using boost::units::si::newton;
  using boost::units::si::pascal;
  using boost::units::si::pressure;
  using boost::units::si::square_meter;

  {
    const quantity<pressure> p(2.0 * pascal);
    const quantity<force> f(6.0 * newton);
    const quantity<area> a(3.0 * square_meter);
    assert(p == f/a);
    assert(a == f/p);
    assert(f == p*a);
    assert(f == a*p);
    std::cout
      << "f: " << f << '\n'
      << "p: " << p << '\n'
      << "a: " << a << '\n';
  }
  {
    const quantity<pressure> p(2.0 * micro * newton / (kilo * square_meter));
    const quantity<force> f(6.0 * micro * newton);
    const quantity<area> a(3.0 * kilo * square_meter);
    assert(p == f/a);
    assert(a == f/p);
    assert(f == p*a);
    assert(f == a*p);
    std::cout
      << "f: " << f << '\n'
      << "p: " << p << '\n'
      << "a: " << a << '\n';
  }
}
