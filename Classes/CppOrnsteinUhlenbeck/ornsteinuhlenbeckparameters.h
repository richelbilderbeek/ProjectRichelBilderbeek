#ifndef ORNSTEINUHLENBECKPARAMETERS_H
#define ORNSTEINUHLENBECKPARAMETERS_H

#include "rate.h"

namespace ribi {
namespace ou {

///Parameters for an Ornstein-Uhlenbeck process
struct Parameters
{
  using Rate = ribi::units::Rate;

  ///mean reversion rate: theta on Wikipedia, lambda by van den Berg
  ///target mean: mu
  ///noise: sigma
  Parameters(
    const Rate mean_reversion_rate,
    const double target_mean,
    const Rate volatility,
    const int rng_seed = 42
  );

  auto GetMeanReversionRate() const noexcept { return m_mean_reversion_rate; }
  int GetRngSeed() const noexcept { return m_rng_seed; }
  double GetTargetMean() const noexcept { return m_target_mean; }
  auto GetVolatility() const noexcept { return m_volatility; }

  private:
  const Rate m_mean_reversion_rate;
  const int m_rng_seed;
  const double m_target_mean;
  const Rate m_volatility;
};

} //~namespace ou
} //~namespace ribi

#endif // ORNSTEINUHLENBECKPARAMETERS_H
