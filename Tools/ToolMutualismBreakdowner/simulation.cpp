#include "simulation.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include "poisoningfunction.h"
#include "loripesconsumptionfunction.h"

Simulation::Simulation(const Parameters& parameters)
  : m_parameters{parameters},
    m_seagrass_densities{},
    m_sulfide_concentrations{},
    m_organic_matter_densities{},
    m_timeseries{}

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
  const double g{m_parameters.sulfide_diffusion_rate};
  const double k{m_parameters.seagrass_carrying_capacity};
  const double l{1.0}; //loripes_density
  const double r{m_parameters.seagrass_growth_rate};
  const double z{m_parameters.seagrass_to_organic_matter_factor};

  InvertLogisticPoisoning P;
  InvertedExponentialConsumption L;

  //Initialize sim
  double seagrass_density{m_parameters.initial_seagrass_density};
  double sulfide_concentration{m_parameters.initial_sulfide_concentration};
  double organic_matter_density{m_parameters.initial_organic_matter_density};
  {
    std::ofstream f("tmp.txt");
    f << m_parameters;
  }

  int i=0;
  for (double t=0.0; t<t_end; t+=delta_t)
  {
    const double n{seagrass_density};
    const double s{sulfide_concentration};
    const double m{organic_matter_density};
    {
      const double delta_n{
          (r*n*(1.0-(n/k))) //Growth
        - (P(n)*s*n)
        - (d*n)  //Desiccation stress
      };
      if (std::isnan(delta_n)) return;
      assert(!std::isnan(delta_n));
      seagrass_density += (delta_n * delta_t);
    }
    {
      const double delta_m{
          (((P(n)*s*n) + (d*n)) * z)
        - b * m
      };
      organic_matter_density += (delta_m * delta_t);
    }
    {
      using std::exp;
      const double delta_s{
          (f*b*m)   //Conversion from organic matter
        - (c*l*s*L(n)) //Consumption of sulfide by loripes
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

std::ostream& operator<<(std::ostream& os, const Simulation& simulation) noexcept
{
  os
    << simulation.GetParameters() << '\n'
  ;
  const std::vector<double>& t{simulation.GetTimeSeries()};
  const std::vector<double>& n{simulation.GetSeagrassDensities()};
  const std::vector<double>& s{simulation.GetSulfideConcentrations()};
  const std::vector<double>& m{simulation.GetOrganicMatterDensities()};
  std::stringstream stream;
  assert(t.size() == n.size());
  assert(t.size() == s.size());
  assert(t.size() == m.size());
  const int sz{static_cast<int>(t.size())};
  for (int i = 0; i!=sz; ++i)
  {
    stream << t[i] << " " << n[i] << " " << m[i] << " " << s[i] << '\n';
  }
  std::string str{stream.str()};
  if (!str.empty()) str.pop_back();
  os << str;
  return os;
}
