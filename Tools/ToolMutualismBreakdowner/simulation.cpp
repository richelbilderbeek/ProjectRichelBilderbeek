#include "simulation.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/units/systems/si.hpp>
#include <boost/units/io.hpp>

#include "poisoningfunction.h"
#include "loripesconsumptionfunction.h"
#include "speciesdensity.h"

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

void Simulation::Run()
{
  const int n_timesteps{m_parameters.n_timesteps};
  assert(n_timesteps >= 0);
  const double t_end{static_cast<double>(n_timesteps)};
  assert(t_end > 0.0);
  const double delta_t{m_parameters.GetDeltaT()};
  assert(delta_t > 0.0);
  const int sz{static_cast<int>(t_end / delta_t)};
  assert(sz > 0);
  const int track_after{std::max(1,sz / 1000)};
  assert(track_after > 0);

  const double b{m_parameters.organic_matter_to_sulfide_rate};
  const double c{m_parameters.sulfide_consumption_by_loripes_rate};
  const double d{m_parameters.desiccation_stress};
  const double f{m_parameters.organic_matter_to_sulfide_factor};
  const double g{m_parameters.sulfide_diffusion_rate};
  const auto k = m_parameters.seagrass_carrying_capacity;
  //const double l{1.0}; //loripes_density
  const double r{m_parameters.seagrass_growth_rate};
  const double z{m_parameters.seagrass_to_organic_matter_factor};
  const auto loripes_consumption_function = m_parameters.loripes_consumption_function;
  const auto poisoning_function = m_parameters.poisoning_function;

  assert(loripes_consumption_function);
  assert(loripes_consumption_function.get());
  assert(poisoning_function);
  assert(poisoning_function.get());


  //Initialize sim
  auto seagrass_density = m_parameters.initial_seagrass_density;
  double sulfide_concentration{m_parameters.initial_sulfide_concentration};
  double organic_matter_density{m_parameters.initial_organic_matter_density};
  auto loripes_density = m_parameters.initial_loripes_density;
  {
    std::ofstream f("tmp.txt");
    f << m_parameters;
  }

  int i=0;
  for (double t=0.0; t<t_end; t+=delta_t)
  {
    assert(i >= 0);
    //std::cerr << i << std::endl;
    const auto n = seagrass_density;
    const auto l = loripes_density;
    const double s{sulfide_concentration};
    const double m{organic_matter_density};
    {
      try
      {
        const auto delta_n
          = (r*n.value()*(1.0-(n/k))) //Growth
          - (poisoning_function->CalculateSurvivalFraction(n.value() /* STILL INCORRECT */)*n.value())
        ;
        seagrass_density += (delta_n * boost::units::si::species_per_square_meter * delta_t);
      }
      catch (std::logic_error& e)
      {
        std::stringstream s;
        s << "Simulation::Run(), calculating seagrass density: " << e.what();
        std::clog << s.str() << std::endl;
        return;
      }
    }
    {
      const double delta_m{
          (((poisoning_function->CalculateSurvivalFraction(n.value() /* STILL INCORRECT */ )*s*n.value()) + (d*n.value())) * z)
        - b * m
      };
      organic_matter_density += (delta_m * delta_t);
    }
    {
      using std::exp;
      const double delta_s{
          (f*b*m)   //Conversion from organic matter
        - (c*s*loripes_consumption_function->CalculateConsumptionRate(n)) //Consumption of sulfide by loripes
        - (g*s)     //Diffusion of sulfide into the environment
      };
      sulfide_concentration += (delta_s * delta_t);

    }
    {
      const auto delta_l
        = l
      ;
      loripes_density += (delta_l * delta_t);
    }
    if (i % track_after == 0)
    {
      m_timeseries.push_back(static_cast<double>(t));
      m_loripes_densities.push_back(loripes_density);
      m_seagrass_densities.push_back(seagrass_density);
      m_sulfide_concentrations.push_back(sulfide_concentration);
      m_organic_matter_densities.push_back(organic_matter_density);
    }
    ++i;
  }

}

std::ostream& operator<<(std::ostream& os, const Simulation& simulation) noexcept
{
  const std::vector<double>& t{simulation.GetTimeSeries()};
  const auto& n = simulation.GetSeagrassDensities();
  const auto& l = simulation.GetLoripesDensities();
  const std::vector<double>& s{simulation.GetSulfideConcentrations()};
  const std::vector<double>& m{simulation.GetOrganicMatterDensities()};
  std::stringstream stream;
  assert(t.size() == n.size());
  assert(t.size() == s.size());
  assert(t.size() == m.size());
  assert(l.size() == m.size());
  const int sz{static_cast<int>(t.size())};
  for (int i = 0; i!=sz; ++i)
  {
    stream << t[i] << " " << n[i] << " " << m[i] << " " << s[i] << " " << l[i] <<  '\n';
  }
  std::string str{stream.str()};
  if (!str.empty()) str.pop_back();
  os << str;
  return os;
}
