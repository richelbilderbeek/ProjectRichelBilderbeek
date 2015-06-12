#ifndef COALESCENTTREEMODELPARAMETERS_H
#define COALESCENTTREEMODELPARAMETERS_H

#include "rate.h"
#include "ribi_time.h"

namespace ribi {
namespace ctm {

///Performs a Birth-Death process
struct Parameters
{
  using BirthRate = ribi::units::Rate;
  using DeathRate = ribi::units::Rate;
  using Time = ribi::units::Time;

  Parameters(
    const BirthRate birth_rate,
    const DeathRate death_rate,
    const Time time,
    const int rng_seed = 42
  );

  Parameters(
    const BirthRate birth_rate,
    const DeathRate death_rate,
    const int n_taxa,
    const int rng_seed = 42
  );

  auto GetBirthRate() const noexcept { return m_birth_rate; }
  auto GetDeathRate() const noexcept { return m_death_rate; }
  auto GetNumberOfTaxa() const noexcept { return m_n_taxa; }
  auto GetRngSeed() const noexcept { return m_rng_seed; }
  auto GetTime() const noexcept { return m_time; }

  private:
  const BirthRate m_birth_rate;
  const DeathRate m_death_rate;
  const int m_rng_seed;
  const Time m_time;
  const int m_n_taxa;
};

} //~namespace ctm
} //~namespace ribi

#endif // COALESCENTTREEMODELPARAMETERS_H
