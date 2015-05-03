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
  const int n_steps_per_time_unit{static_cast<int>(1.0 / m_parameters.delta_t)};

  const double b{m_parameters.organic_matter_to_sulfide_rate};
  const double c{m_parameters.sulfide_consumption_by_loripes_rate};
  const double d{m_parameters.desiccation_stress};
  const double f{m_parameters.organic_matter_to_sulfide_factor};
  const double k{m_parameters.seagrass_carrying_capacity};
  const double l{m_parameters.loripes_density};
  //const double p{m_parameters.oxygen_production};
  const double r{m_parameters.seagrass_growth_rate};
  const double p{m_parameters.sulfide_toxicity};
  const double z{m_parameters.seagrass_to_organic_matter_factor};

  //Initialize sim
  double seagrass_density{m_parameters.initial_seagrass_density};
  double sulfide_concentration{m_parameters.initial_sulfide_concentration};
  double organic_matter_density{m_parameters.initial_organic_matter_density};

  int i=0;
  for (double t=0.0; t<t_end; t+=delta_t)
  {
    const double n{seagrass_density};
    const double s{sulfide_concentration};
    const double m{organic_matter_density};
    {
      const double delta_n{
          (r*n*(1.0-(n/k))) //Growth
        - (t*s*n)
        - (d*n)  //Desiccation stress
      };
      seagrass_density += (delta_n * delta_t);
    }
    {
      const double delta_m{
          (((p*s*n) + (d*n)) * z)
        - b * m
      };
      organic_matter_density += (delta_m * delta_t);
    }
    {
      using std::exp;
      const double g{0.0001}; //Diffusion rate of sulfide in environment
      const double delta_s{
          (f*b*m)   //Conversion from organic matter
        - (c*l*s*n) //Consumption of sulfide by loripes
        - (g*s)     //Diffusion of sulfide into the environment
      };
      sulfide_concentration += (delta_s * delta_t);

    }
    if (i % n_steps_per_time_unit)
    {
      m_timeseries.push_back(static_cast<double>(t));
      m_seagrass_densities.push_back(seagrass_density);
      m_sulfide_concentrations.push_back(sulfide_concentration);
      m_organic_matter_densities.push_back(organic_matter_density);
    }
    ++i;
  }

}
