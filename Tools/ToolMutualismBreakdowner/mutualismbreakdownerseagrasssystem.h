#ifndef SEAGRASSSYSTEM_H
#define SEAGRASSSYSTEM_H

#include "mutualismbreakdownerparameters.h"
#include "speciesdensity.h"
#include "concentration.h"
#include "ribi_time.h"

namespace ribi {
namespace mb {

struct SeagrassSystem
{
  using Time = ribi::units::Time;
  using SpeciesDensity = ribi::units::SpeciesDensity;
  using Concentration = ribi::units::Concentration;

  SeagrassSystem(const Parameters& parameters);

  void AddSeagrassDensity(const SpeciesDensity seagrass_density) { m_seagrass_density += seagrass_density; }
  void Change(const Time delta_t);

  const Parameters& GetParameters() const noexcept { return m_parameters; }
  const auto& GetSeagrassDensity() const noexcept { return m_seagrass_density; }
  const auto& GetSulfideConcentration() const noexcept { return m_sulfide_concentration; }
  void SetSeagrassDensity(const SpeciesDensity seagrass_density) { m_seagrass_density = seagrass_density; }
  void SetSulfideConcentration(const Concentration sulfide_concentration) { m_sulfide_concentration = sulfide_concentration; }

  private:
  const Parameters m_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  SpeciesDensity m_seagrass_density;
  Concentration m_sulfide_concentration;
};

} //~namespace mb
} //~namespace ribi

#endif // SEAGRASSSYSTEM_H
