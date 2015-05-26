#ifndef ORNSTEINUHLENBECK_H
#define ORNSTEINUHLENBECK_H

#include <random>
#include "positivenonzerodouble.h"

namespace ribi {

///Performs an Ornstein-Uhlenbeck process
///Many thanks to Thijs van den Berg from sitmo.com for an awesome article about it
struct OrnsteinUhlenbeck
{
  ///lambda: mean reversion rate
  ///mu: long-term mean
  ///noise: sigma
  OrnsteinUhlenbeck(
    const PositiveNonZeroDouble lambda,
    const double mu,
    const double sigma,
    const int rng_seed = 42
  );

  ///lambda: mean reversion rate
  ///mu: long-term mean
  ///noise: sigma
  OrnsteinUhlenbeck(
    const double lambda,
    const double mu,
    const double sigma,
    const int rng_seed = 42
  ) : OrnsteinUhlenbeck(PositiveNonZeroDouble(lambda),mu,sigma,rng_seed) {}


  ///Calculate the next x+dt. This class will supply the random numbers,
  ///thus these member functions are not const
  double CalcNext(const double x, const double dt = 1.0);
  double CalcNext(const double x, const PositiveNonZeroDouble dt = PositiveNonZeroDouble(1.0)) noexcept;

  ///Calculate the next x+dt, supplying the random numbers yourself
  double CalcNext(const double x, const double dt, const double random_normal) const;
  double CalcNext(const double x, const PositiveNonZeroDouble dt, const double random_normal) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:

  const PositiveNonZeroDouble m_lambda;
  const double m_mu;
  const double m_sigma;
  std::mt19937 m_rng;
  const int m_rng_seed;
  std::normal_distribution<double> m_normal_distribution;

};

} //~namespace ribi

#endif // ORNSTEINUHLENBECK_H
