#ifndef ORNSTEINUHLENBECK_H
#define ORNSTEINUHLENBECK_H

#include <random>

///Performs an Ornstein-Uhlenbeck process
///Many thanks to Thijs van den Berg from sitmo.com for an awesome article about it
struct OrnsteinUhlenbeck
{
  ///lambda: mean reversion rate
  ///mu: long-term mean
  ///noise: sigma
  OrnsteinUhlenbeck(
    const double lambda,
    const double mu,
    const double sigma,
    const int rng_seed = 42
  );

  ///The stochastic differential equation (SDE)
  /// dS_t = lambda(mu-S_t)*dt + sigma*dWt
  //double CalcSdeRate(const double S_t) const noexcept;

  double CalcNext(const double x, const double dt = 1.0) noexcept;

  ///Calculate the next
  /// S_i+1 = S_i * e^(-lambda*sigma) + mu(1-e^(-lambda*sigma)) +
  double CalcNext(const double x, const double dt, const double random_normal) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:

  const double m_lambda;
  const double m_mu;
  const double m_sigma;
  std::mt19937 m_rng;
  const int m_rng_seed;

};

#endif // ORNSTEINUHLENBECK_H
