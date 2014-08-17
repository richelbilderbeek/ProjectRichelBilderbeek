#ifndef AAFBOND_H
#define AAFBOND_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
//#include <boost/units/unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>
#pragma GCC diagnostic pop


namespace ribi {
namespace aaf {

struct Bond
{
  typedef boost::units::quantity<boost::units::si::length,double> Length;


  Bond(const int n_bonds = 1) : m_n_bonds(n_bonds) {}

  private:
  int m_n_bonds;
};

boost::units::quantity<boost::units::si::length,double> GetAverageBondLength() noexcept;

} //~namespace aaf
} //~namespace ribi

#endif // AAFBOND_H
