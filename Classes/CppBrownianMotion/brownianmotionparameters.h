#ifndef BROWNIANMOTIONPARAMETERS_H
#define BROWNIANMOTIONPARAMETERS_H

#include "rate.h"

namespace ribi {
namespace bm {

///Performs a Brownian motion

struct Parameters
{
  using Volatility = ribi::units::Rate;

  ///volatility: the standard deviation of the noise
  Parameters(
    const Volatility volatility,
    const int rng_seed = 42
  );

  int GetRngSeed() const noexcept { return m_rng_seed; }
  auto GetVolatility() const noexcept { return m_volatility; }

  private:
  const int m_rng_seed;
  const Volatility m_volatility;
};

} //~namespace bm
} //~namespace ribi

#endif // BROWNIANMOTIONPARAMETERS_H
