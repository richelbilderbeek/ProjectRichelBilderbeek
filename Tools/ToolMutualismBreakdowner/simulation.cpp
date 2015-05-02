#include "simulation.h"
#include <cmath>

Simulation::Simulation(const Parameters& parameters)
  : m_parameters{parameters}
{
  #ifndef NDEBUG
  Test();
  #endif
}

void Simulation::Run() noexcept
{
  const int n_timesteps{m_parameters.n_timesteps};
  const double t_end{static_cast<double>(n_timesteps)};
  const double delta_t{m_parameters.delta_t};

  //Initialize sim
  double seagrass_density{m_parameters.initial_seagrass_density};
  double sulfide_concentration{m_parameters.initial_sulfide_concentration};
  for (double t=0.0; t<t_end; t+=delta_t)
  {
    m_timeseries.push_back(static_cast<double>(t));
    //Sim here
    {
      const double d{m_parameters.desiccation_stress};
      const double k{m_parameters.seagrass_carrying_capacity};
      const double n{seagrass_density};
      const double r{m_parameters.seagrass_growth_rate};
      const double s{sulfide_concentration};
      const double t{m_parameters.sulfide_toxicity};
      const double delta_n{
        r*n*(1.0-(n/k)) //Growth
        - (t*s*n)
        - (d*n)  //Desiccation stress
      };
      seagrass_density += (delta_n * delta_t);
    }
    {
      using std::exp;
      //const double a{m_parameters.oxygen_inhibition_strength};
      const double c{m_parameters.sulfide_consumption_by_loripes};
      const double d{m_parameters.desiccation_stress};
      const double f{m_parameters.sulfide_mol_per_seagrass_density};
      const double l{m_parameters.loripes_density};
      const double n{seagrass_density};
      const double p{m_parameters.oxygen_production};
      const double s{sulfide_concentration};
      const double t{m_parameters.sulfide_toxicity};
      const double delta_s{
          f*t*s*n //Degradation of organic matter via toxicity
        + f*d*n   //Degradation of organic matter via desiccation
        - c*l*p*n //Consumption of sulfide by loripes
      };
      sulfide_concentration += (delta_s * delta_t);

    }
    m_seagrass_densities.push_back(seagrass_density);
    m_sulfide_concentrations.push_back(sulfide_concentration);
  }
}
