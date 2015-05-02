#ifndef NDEBUG
#include "simulation.h"

#include <cassert>

void Simulation::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  //Seagrass must grow logistically to carrying capacity
  {
    const Parameters p(
      0.1, //const double any_delta_t,
      0.0, //const double any_desiccation_stress,
      0.1, //const double any_initial_seagrass_density,
      0.0, //const double any_initial_sulfide_density,
      0.0, //const double any_loripes_density,
      0.0, //const double any_oxygen_production,
      1.0, //const double any_seagrass_carrying_capacity,
      1.0, //const double any_seagrass_growth_rate,
      0.0, //const double any_sulfide_consumption_by_loripes,
      0.0, //const double any_sulfide_mol_per_seagrass_density,
      0.0, //const double any_sulfide_toxicity,
      10 //const int any_n_timesteps
    );
    Simulation simulation(p);
    simulation.Run();
    assert(
      simulation.GetSeagrassDensities().back() > 0.9
      && "Seagrass must grow logistically to carrying capacity"
    );
  }
  //Seagrass must die from sulfide when constant
  {
    const Parameters p(
      0.1, //const double any_delta_t,
      0.0, //const double any_desiccation_stress,
      1.0, //const double any_initial_seagrass_density,
      1.0, //const double any_initial_sulfide_density,
      0.0, //const double any_loripes_density,
      0.0, //const double any_oxygen_production,
      1.0, //const double any_seagrass_carrying_capacity,
      1.0, //const double any_seagrass_growth_rate,
      0.0, //const double any_sulfide_consumption_by_loripes,
      0.0, //const double any_sulfide_mol_per_seagrass_density,
      1.0, //const double any_sulfide_toxicity,
      10 //const int any_n_timesteps
    );
    Simulation simulation(p);
    simulation.Run();
    assert(
      simulation.GetSeagrassDensities().back() < 0.1
      && "Seagrass must die by toxicity"
    );
  }

  //If there is no water, the seagrass must die
  {
    const Parameters p(
      0.1, //const double any_delta_t,
      1.0, //const double any_desiccation_stress,
      1.0, //const double any_initial_seagrass_density,
      0.0, //const double any_initial_sulfide_density,
      0.0, //const double any_loripes_density,
      0.0, //const double any_oxygen_production,
      1.0, //const double any_seagrass_carrying_capacity,
      0.1, //const double any_seagrass_growth_rate,
      0.0, //const double any_sulfide_consumption_by_loripes,
      0.0, //const double any_sulfide_mol_per_seagrass_density,
      0.0, //const double any_sulfide_toxicity,
      10 //const int any_n_timesteps
    );
    Simulation simulation(p);
    simulation.Run();
    assert(
      simulation.GetSeagrassDensities().back() < 0.0001
      && "Seagrass must die if there is no water"
    );
  }
}

#endif
