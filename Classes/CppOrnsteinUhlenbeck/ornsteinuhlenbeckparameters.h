#ifndef ORNSTEINUHLENBECKPARAMETERS_H
#define ORNSTEINUHLENBECKPARAMETERS_H

namespace ribi {
namespace ou {

///Parameters for an Ornstein-Uhlenbeck process
struct Parameters
{
  ///mean reversion rate: theta on Wikipedia, lambda by van den Berg
  ///target mean: mu
  ///noise: sigma
  Parameters(
    const double mean_reversion_rate,
    const double target_mean,
    const double volatility,
    const int rng_seed = 42
  );

  double GetMeanReversionRate() const noexcept { return m_mean_reversion_rate; }
  int GetRngSeed() const noexcept { return m_rng_seed; }
  double GetTargetMean() const noexcept { return m_target_mean; }
  double GetVolatility() const noexcept { return m_volatility; }

  private:
  const double m_mean_reversion_rate;
  const int m_rng_seed;
  const double m_target_mean;
  const double m_volatility;
};

} //~namespace ou
} //~namespace ribi

#endif // ORNSTEINUHLENBECKPARAMETERS_H
