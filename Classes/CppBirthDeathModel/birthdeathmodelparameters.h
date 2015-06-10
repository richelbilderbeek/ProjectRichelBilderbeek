#ifndef BIRTHDEATHMODELPARAMETERS_H
#define BIRTHDEATHMODELPARAMETERS_H

#include "rate.h"
#include "ribi_time.h"

namespace ribi {
namespace bdm {

///Performs a Birth-Death process
struct Parameters
{
  using BirthRate = ribi::units::Rate;
  using DeathRate = ribi::units::Rate;
  using Time = ribi::units::Time;

  ///volatility: the standard deviation of the noise
  Parameters(
    const BirthRate birth_rate,
    const DeathRate death_rate,
    const Time time,
    const int rng_seed = 42
  );

  auto GetBirthRate() const noexcept { return m_birth_rate; }
  auto GetDeathRate() const noexcept { return m_death_rate; }
  auto GetRngSeed() const noexcept { return m_rng_seed; }
  auto GetTime() const noexcept { return m_time; }

  private:
  const BirthRate m_birth_rate;
  const DeathRate m_death_rate;
  const int m_rng_seed;
  const Time m_time;
};

} //~namespace bm
} //~namespace ribi

#endif // BIRTHDEATHMODELPARAMETERS_H
