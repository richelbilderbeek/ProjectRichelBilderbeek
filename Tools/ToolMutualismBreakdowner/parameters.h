#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iosfwd>
#include <memory>
#include "speciesdensity.h"
struct LoripesConsumptionFunction;
struct PoisoningFunction;

struct Parameters
{
  Parameters();
  Parameters(
    const double any_delta_t,
    const double any_desiccation_stress,
    const ribi::units::SpeciesDensity initial_loripes_density,
    const double any_initial_organic_matter_density,
    const ribi::units::SpeciesDensity initial_seagrass_density,
    const double any_initial_sulfide_density,
    const std::shared_ptr<LoripesConsumptionFunction>& any_loripes_consumption_function,
    const double any_organic_matter_to_sulfide_factor,
    const double any_organic_matter_to_sulfide_rate,
    const std::shared_ptr<PoisoningFunction>& any_poisoning_function,
    const ribi::units::SpeciesDensity any_seagrass_carrying_capacity,
    const double any_seagrass_growth_rate,
    const double any_seagrass_to_organic_matter_factor,
    const double any_sulfide_consumption_by_loripes,
    const double any_sulfide_diffusion_rate,
    const int any_n_timesteps
  );

  double GetDeltaT() const noexcept { return delta_t; }
  void SetDeltaT(const double any_delta_t);

  private:
  double delta_t;
  public:
  double desiccation_stress;
  ribi::units::SpeciesDensity initial_loripes_density;
  double initial_organic_matter_density;
  ribi::units::SpeciesDensity initial_seagrass_density;
  double initial_sulfide_concentration;
  std::shared_ptr<LoripesConsumptionFunction> loripes_consumption_function;
  double organic_matter_to_sulfide_factor;
  double organic_matter_to_sulfide_rate;
  std::shared_ptr<PoisoningFunction> poisoning_function;
  ribi::units::SpeciesDensity seagrass_carrying_capacity;
  double seagrass_growth_rate;
  double seagrass_to_organic_matter_factor;
  double sulfide_consumption_by_loripes_rate;
  double sulfide_diffusion_rate;
  int n_timesteps;

  #ifndef NDEBUG
  static void Test() noexcept;

  ///Create a testing parameter set
  static Parameters GetTest(const int i);
  #endif
};

bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept;
bool operator!=(const Parameters& lhs, const Parameters& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept;
std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept;

#endif // PARAMETERS_H
