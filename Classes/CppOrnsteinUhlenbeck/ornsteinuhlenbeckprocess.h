#ifndef ORNSTEINUHLENBECKPROCESS_H
#define ORNSTEINUHLENBECKPROCESS_H

#include <random>
#include "ornsteinuhlenbeckparameters.h"

namespace ribi {
namespace ou {

///Performs an Ornstein-Uhlenbeck process
///Many thanks to Thijs van den Berg from sitmo.com for an awesome article about it
struct Process
{
  Process(const Parameters& parameters);

  ///Calculate the next x+dt. This class will supply the random numbers,
  ///thus these member functions are not const
  double CalcNext(const double x, const double dt = 1.0);

  ///Calculate the next x+dt, supplying the random numbers yourself
  double CalcNext(const double x, const double dt, const double random_normal) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:

  std::normal_distribution<double> m_normal_distribution;
  const Parameters m_parameters;
  std::mt19937 m_rng;

};

} //~namespace ou
} //~namespace ribi

#endif // ORNSTEINUHLENBECKPROCESS_H
