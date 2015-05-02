//Slightly modified example from
// http://www.boost.org/doc/libs/1_37_0/doc/html/boost_units/Examples.html

#include <complex>
#include <iostream>

#include <boost/typeof/std/complex.hpp>

#include <boost/units/systems/si/current.hpp>
#include <boost/units/systems/si/electric_potential.hpp>
#include <boost/units/systems/si/energy.hpp>
#include <boost/units/systems/si/force.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/resistance.hpp>

using namespace boost::units;
using namespace boost::units::si;

const quantity<energy> work(const quantity<force>& F,const quantity<length>& dx)
{
  return F*dx;
}

int main()
{
  //test calculation of work
  const quantity<force>     F(2.0*newton);
  const quantity<length>    dx(2.0*meter);
  const quantity<energy>    E(work(F,dx));

  std::cout
    << "F  = " << F <<  '\n'
    << "dx = " << dx <<  '\n'
    << "E  = " << E <<  '\n';


  //check complex quantities
  typedef std::complex<double>    complex_type;

  const quantity<electric_potential,complex_type> v = complex_type(12.5,0.0)*volts;
  const quantity<current,complex_type>            i = complex_type(3.0,4.0)*amperes;
  const quantity<resistance,complex_type>         z = complex_type(1.5,-2.0)*ohms;

  std::cout
    << "V   = " << v << '\n'
    << "I   = " << i << '\n'
    << "Z   = " << z << '\n'
    << "I*Z = " << i*z << '\n'
    << "I*Z == V? " << std::boolalpha << (i*z == v) <<  '\n';
}
