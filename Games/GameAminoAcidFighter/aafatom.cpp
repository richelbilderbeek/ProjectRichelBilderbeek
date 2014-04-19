#include "aafatom.h"

ribi::aaf::Atom::Atom(
  const AtomType type,
  const PolarCoordinat<Angle,Length> coordinat
) : m_coordinat(coordinat),
    m_type(type)
{

}

/*
ribi::aaf::Atom::Atom(
  const AtomType type,
  const Angle angle,
  const Length length
) : m_coordinat(angle,length),
    m_type(type)
{

}
*/


ribi::PolarCoordinat<ribi::aaf::Atom::Angle,ribi::aaf::Atom::Length> ribi::aaf::Atom::CreateDefaultCoordinat() noexcept
{
  return PolarCoordinat<Angle,Length>(
    0.0 * boost::units::si::radian,
    0.0 * boost::units::si::meter
  );
}
