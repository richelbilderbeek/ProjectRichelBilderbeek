#ifndef BROWNIANMOTIONPARAMETERS_H
#define BROWNIANMOTIONPARAMETERS_H

namespace ribi {
namespace bm {

///Performs a Brownian motion

struct Parameters
{
  ///volatility: the standard deviation of the noise
  Parameters(
    const double volatility,
    const int rng_seed = 42
  );

  int GetRngSeed() const noexcept { return m_rng_seed; }
  double GetVolatility() const noexcept { return m_volatility; }

  private:
  const int m_rng_seed;
  const double m_volatility;
};

} //~namespace bm
} //~namespace ribi

#endif // BROWNIANMOTIONPARAMETERS_H
