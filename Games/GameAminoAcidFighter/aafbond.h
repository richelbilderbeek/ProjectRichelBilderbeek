#ifndef AAFBOND_H
#define AAFBOND_H

#include <string>

namespace ribi {
namespace aaf {

struct Bond
{
  Bond(const int n_bonds = 1) : m_n_bonds(n_bonds) {}

  private:
  int m_n_bonds;
};

} //~namespace aaf
} //~namespace ribi

#endif // AAFBOND_H
