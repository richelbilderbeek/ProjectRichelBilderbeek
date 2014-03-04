#ifndef AAFATOM_H
#define AAFATOM_H

#include "polarcoordinat.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/systems/si/plane_angle.hpp>

#pragma GCC diagnostic pop

namespace ribi {
namespace aaf {

struct Atom
{
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::length> Length;
  PolarCoordinat<Angle,Length> m_coordinat;
};

} //~namespace aaf
} //~namespace ribi

#endif // AAFATOM_H
