#include "aafbond.h"

#include <cassert>

#include <boost/units/systems/si/prefixes.hpp>

boost::units::quantity<boost::units::si::length,double> ribi::aaf::GetAverageBondLength() noexcept
{
  return boost::units::quantity<boost::units::si::length,double>(
    109.0
    * boost::units::si::pico
    * boost::units::si::meter
  );
}
