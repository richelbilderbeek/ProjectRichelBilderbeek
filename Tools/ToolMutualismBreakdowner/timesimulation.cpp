#include "timesimulation.h"

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
#include "seagrasssystem.h"

TimeSimulation::TimeSimulation(const Parameters& parameters)
  : m_parameters{parameters},
    m_seagrass_densities{},
    m_sulfide_concentrations{},
    m_timeseries{}

{
  #ifndef NDEBUG
  Test();
  #endif
}

void TimeSimulation::Run()
{
  using Time = boost::units::quantity<boost::units::si::time>;
  using boost::units::si::seconds;
  const int n_timesteps{m_parameters.GetNumberOfTimesteps()};
  assert(n_timesteps >= 0);
  const auto t_end = static_cast<double>(n_timesteps) * seconds;

  const auto delta_t = m_parameters.GetDeltaT();

  const int sz{static_cast<int>(t_end / delta_t)};
  assert(sz > 0);
  const int track_after{std::max(1,sz / 1000)};
  assert(track_after > 0);

  SeagrassSystem seagrass_system(m_parameters);

  int i=0;
  for (Time t=0.0 * seconds; t<t_end; t+=delta_t)
  {
    assert(i >= 0);
    try
    {
      seagrass_system.Change(delta_t);
    }
    catch (std::logic_error& e)
    {
      std::stringstream s;
      s << __func__ << ": Change: " << e.what();
      std::clog << s.str() << std::endl;
      return;
    }
    if (i % track_after == 0)
    {    
      m_timeseries.push_back(t.value());
      m_seagrass_densities.push_back(seagrass_system.GetSeagrassDensity());
      m_sulfide_concentrations.push_back(seagrass_system.GetSulfideConcentration());
    }
    ++i;
  }

}

std::ostream& operator<<(std::ostream& os, const TimeSimulation& simulation) noexcept
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
