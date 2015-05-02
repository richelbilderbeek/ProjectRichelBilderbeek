#include <iostream>
#include <iomanip>

#include <boost/math/constants/constants.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/si/io.hpp>

int main()
{
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  using boost::units::si::radians;

  const double pi = boost::math::constants::pi<double>();
  const Angle delta(2.0 * pi * radians / 16.0);
  const Angle j(2.0 * pi * radians);
  std::cout << std::setprecision(20);
  for (Angle i(0.0 * pi * radians); i<j; i+=delta)
  {
    std::cout << "sin(" << i << ") = " << std::sin(i.value()) << '\n';
  }


  //Converting between radians and degrees
  /*
  using boost::units::degree::degree;
  {
    const Angle r(2.0 * boost::units::si::radians);
    std::cout
      << "r is " << r << ", and "
      << (r * degree / radians).value() << " degrees" //Gives incorrect answer
    ;
  }
  */
}

/* Screen output

sin(0 rad) = 0
sin(0.3926990816987241395 rad) = 0.38268343236508978178
sin(0.785398163397448279 rad) = 0.70710678118654746172
sin(1.1780972450961724185 rad) = 0.92387953251128673848
sin(1.570796326794896558 rad) = 1
sin(1.9634954084936206975 rad) = 0.92387953251128673848
sin(2.356194490192344837 rad) = 0.70710678118654757274
sin(2.7488935718910689765 rad) = 0.3826834323650898928
sin(3.141592653589793116 rad) = 1.2246063538223772582e-016
sin(3.5342917352885172555 rad) = -0.38268343236508967076
sin(3.926990816987241395 rad) = -0.70710678118654746172
sin(4.3196898986859650904 rad) = -0.92387953251128651644
sin(4.712388980384689674 rad) = -1
sin(5.1050880620834142576 rad) = -0.92387953251128662746
sin(5.4977871437821388412 rad) = -0.70710678118654701763
sin(5.8904862254808634248 rad) = -0.38268343236508872707
Press <RETURN> to close this window...

*/
