#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "polarcoordinat.h"
#pragma GCC diagnostic pop

/*
template<>
double CalculateSqrt<double,double>(const double& x)
{
  static_assert(
    !std::is_same<
      double,boost
      ::units::quantity<boost::units::si::length>>(),"");
  return std::sqrt(x);
}

template<>
boost::units::quantity<boost::units::si::length>
  CalculateSqrt<
    boost::units::quantity<boost::units::si::length>,
    boost::units::quantity<boost::units::si::area>
  >(
  const boost::units::quantity<boost::units::si::area>& x)
{
  return std::sqrt(x.value()) * boost::units::si::meter;
}
*/
