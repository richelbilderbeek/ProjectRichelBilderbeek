#ifndef ORNSTEINUHLENBECK_H
#define ORNSTEINUHLENBECK_H

#include <random>

namespace ribi {

///Performs an Ornstein-Uhlenbeck process
///Many thanks to Thijs van den Berg from sitmo.com for an awesome article about it
struct OrnsteinUhlenbeck
{
  ///mean reversion rate: theta on Wikipedia, lambda by van den Berg
  ///target mean: mu
  ///noise: sigma
  OrnsteinUhlenbeck(
    const double mean_reversion_rate,
    const double target_mean,
    const double volatility,
    const int rng_seed = 42
  );

  ///Calculate the likelihood of the candidate parameters in generating the dataset
  static double CalcLogLikelihood(
    const std::vector<double>& v,
    const double dt,
    const double cand_mean_reversion_rate,
    const double cand_target_mean,
    const double cand_volatility
  );

  ///Calculate the parameters that have a maximum likelihood in generating the values v
  static void CalcMaxLikelihood(
    const std::vector<double>& v,
    const double dt,
    double& mean_reversion_rate_hat,
    double& target_mean_hat,
    double& volatility_hat
  );

  ///Calculate the next x+dt. This class will supply the random numbers,
  ///thus these member functions are not const
  double CalcNext(const double x, const double dt = 1.0);

  ///Calculate the next x+dt, supplying the random numbers yourself
  double CalcNext(const double x, const double dt, const double random_normal) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:

  const double m_mean_reversion_rate;
  std::normal_distribution<double> m_normal_distribution;
  std::mt19937 m_rng;
  const int m_rng_seed;
  const double m_target_mean;
  const double m_volatility;

};

} //~namespace ribi

#endif // ORNSTEINUHLENBECK_H
