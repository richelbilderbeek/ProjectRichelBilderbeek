#include "simulation.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/units/systems/si.hpp>
#include <boost/units/io.hpp>

#include "poisoningfunction.h"
#include "speciesdensity.h"
#include "seagrassgrowthfunction.h"
#include "sulfideconsumptionfunction.h"
#include "sulfidedetoxificationfunction.h"
#include "sulfidediffusionfunction.h"
#include "sulfideproductionfunction.h"

Simulation::Simulation(const Parameters& parameters)
  : m_parameters{parameters},
    m_seagrass_densities{},
    m_sulfide_concentrations{},
    m_timeseries{}

{
  #ifndef NDEBUG
  Test();
  #endif
}

void Simulation::Run()
{
  const int n_timesteps{m_parameters.GetNumberOfTimesteps()};
  assert(n_timesteps >= 0);
  const double t_end{static_cast<double>(n_timesteps)};
  assert(t_end > 0.0);
  const double delta_t{m_parameters.GetDeltaT()};
  assert(delta_t > 0.0);
  const int sz{static_cast<int>(t_end / delta_t)};
  assert(sz > 0);
  const int track_after{std::max(1,sz / 1000)};
  assert(track_after > 0);

  const auto sulfide_consumption_function = m_parameters.GetSulfideConsumptionFunction();
  const auto poisoning_function = m_parameters.GetPoisoningFunction();

  assert(sulfide_consumption_function);
  assert(sulfide_consumption_function.get());
  assert(poisoning_function);
  assert(poisoning_function.get());


  //Initialize sim
  auto seagrass_density = m_parameters.GetInitialSeagrassDensity();
  auto sulfide_concentration = m_parameters.GetInitialSulfideConcentration();
  auto loripes_density = m_parameters.GetInitialLoripesDensity();
  {
    std::ofstream f("tmp.txt");
    f << m_parameters;
  }

  int i=0;
  for (double t=0.0; t<t_end; t+=delta_t)
  {
    assert(i >= 0);
    const auto n = seagrass_density;
    const auto s = sulfide_concentration;
    const auto l = loripes_density;
    //Seagrass
    try
    {
      assert(m_parameters.GetSeagrassGrowthFunction());
      const auto growth = m_parameters.GetSeagrassGrowthFunction()->CalculateGrowth(n);
      const auto poisoning = poisoning_function->CalculateDecline(n,s);
      const auto delta_n = growth - poisoning;
      seagrass_density += (delta_n * delta_t * boost::units::si::second);
    }
    catch (std::logic_error& e)
    {
      std::stringstream s;
      s << "Simulation::Run(), calculating seagrass density: " << e.what();
      std::clog << s.str() << std::endl;
      return;
    }
    //Sulfide
    try
    {
      const auto production = m_parameters.GetSulfideProductionFunction()->CalculateProduction(n);
      const auto detoxification = m_parameters.GetSulfideDetoxificationFunction()->CalculateDetoxification(n,s);
      const auto diffusion = m_parameters.GetSulfideDiffusionFunction()->CalculateDiffusion(s);
      const auto consumption = m_parameters.GetSulfideConsumptionFunction()->CalculateConsumption(s,l);
      const auto delta_s
        = production
        - diffusion
        - detoxification
        - consumption
      ;

      sulfide_concentration += (
          delta_s * delta_t * boost::units::si::second
      );

    }
    catch (std::logic_error& e)
    {
      std::stringstream s;
      s << "Simulation::Run(), calculating sulfide concentration: " << e.what();
      std::clog << s.str() << std::endl;
      return;
    }
    if (i % track_after == 0)
    {
      m_timeseries.push_back(static_cast<double>(t));
      m_seagrass_densities.push_back(seagrass_density);
      m_sulfide_concentrations.push_back(sulfide_concentration);
    }
    ++i;
  }

}

std::ostream& operator<<(std::ostream& os, const Simulation& simulation) noexcept
{
  const std::vector<double>& t{simulation.GetTimeSeries()};
  const auto& n = simulation.GetSeagrassDensities();
  const auto& s = simulation.GetSulfideConcentrations();
  std::stringstream stream;
  assert(t.size() == n.size());
  assert(t.size() == s.size());
  const int sz{static_cast<int>(t.size())};
  for (int i = 0; i!=sz; ++i)
  {
    stream << t[i] << " " << n[i] << " " << s[i] <<  '\n';
  }
  std::string str{stream.str()};
  if (!str.empty()) str.pop_back();
  os << str;
  return os;
}
