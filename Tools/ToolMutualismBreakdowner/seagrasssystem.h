#ifndef SEAGRASSSYSTEM_H
#define SEAGRASSSYSTEM_H

#include "parameters.h"
#include "speciesdensity.h"
#include "concentration.h"
#include "ribi_time.h"

struct SeagrassSystem
{
  using Time = ribi::units::Time;

  SeagrassSystem(const Parameters& parameters);

  const Parameters& GetParameters() const noexcept { return m_parameters; }
  const auto& GetSeagrassDensity() const noexcept { return m_seagrass_density; }
  const auto& GetSulfideConcentration() const noexcept { return m_sulfide_concentration; }

  void Change(const Time delta_t);

  private:
  const Parameters m_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ribi::units::SpeciesDensity m_seagrass_density;
  ribi::units::Concentration m_sulfide_concentration;
};

#endif // SEAGRASSSYSTEM_H
