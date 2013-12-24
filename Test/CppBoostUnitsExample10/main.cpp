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

int main()
{
  //Question: what will be the increase in angular velocity
  //if three Newton is applied at a distance of 2 meter
  //for 5 seconds to an object with angular momentum of 7 kg*m*m/rad/sec

  //Increase readability
  using boost::units::quantity;
  using boost::units::si::angular_acceleration;
  using boost::units::si::angular_momentum;
  using boost::units::si::angular_velocity;
  using boost::units::si::force;
  using boost::units::si::joule;
  using boost::units::si::kilogram;
  using boost::units::si::length;
  using boost::units::si::meter;
  using boost::units::si::newton;
  using boost::units::si::newton_meter;
  using boost::units::si::radian;
  using boost::units::si::time;
  using boost::units::si::second;
  using boost::units::si::torque;

  typedef quantity<angular_acceleration> AngularAcceleration;
  typedef quantity<angular_momentum> AngularMomentum;
  typedef quantity<angular_velocity> AngularVelocity;
  typedef quantity<force> Force;
  typedef quantity<length> Length;
  typedef quantity<torque> Torque;
  typedef quantity<time> Time;

  //Calculate the torque (also known as 'moment' or 'moment of force')
  const double r = 2.0;
  const double f = 3.0;

  const Length my_ray(r * meter);
  const Force my_force(f * newton);
  const Torque my_torque(my_ray * my_force * joule / radian / meter / newton);

  std::cout
    << "Torque = distance * force\n"
    << "tau = r * F\n"
    << "tau: " << my_torque << '\n'
    << "r: "   << my_ray    << '\n'
    << "F: "   << my_force  << '\n'
    << '\n';
  //Check if calculating the force from the plain doubles is identical
  const Torque my_torque_expected(r * f * joule / radian);
  assert(my_torque == my_torque_expected);

  //Calculate the angular acceleration
  const AngularMomentum am(7.0 * kilogram * meter * meter / radian / second);
  const AngularAcceleration aa((my_torque / am) * radian * meter * meter * kilogram / second / second / second / joule); //rad/s/s
  std::cout
    << "Angular acceleration = torque / angular momentum\n"
    << "alpha = tau * I\n"
    << "alpha: " << aa << '\n'
    << "tau: "   << my_torque    << '\n'
    << "I: "     << am  << '\n'
    << '\n';

  const Time t(5.0 * second);
  const AngularVelocity av(aa * t);

  std::cout
    << "Angular velocity = angular acceleration * time\n"
    << "omega = alpha * t\n"
    << "omega: " << av << '\n'
    << "alpha: " << aa << '\n'
    << "t: "     << t  << '\n'
    << '\n';
}

/* Screen output:

Torque = distance * force
tau = r * F
tau: 6 m^2 kg s^-2 rad^-1
r: 2 m
F: 3 N

Angular acceleration = torque / angular momentum
alpha = tau * I
alpha: 0.857143 s^-2 rad
tau: 6 m^2 kg s^-2 rad^-1
I: 7 m^2 kg s^-1 rad^-1

Angular velocity = angular acceleration * time
omega = alpha * t
omega: 4.28571 s^-1 rad
alpha: 0.857143 s^-2 rad
t: 5 s
*/
