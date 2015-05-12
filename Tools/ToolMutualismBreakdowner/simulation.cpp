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
#include "seagrassgrowthfunction.h"
Simulation::Simulation(const Parameters& parameters)
  : m_parameters{parameters},
    m_loripes_densities{},
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

  const auto loripes_consumption_function = m_parameters.GetLoripesConsumptionFunction();
  const auto poisoning_function = m_parameters.GetPoisoningFunction();

  assert(loripes_consumption_function);
  assert(loripes_consumption_function.get());
  assert(poisoning_function);
  assert(poisoning_function.get());


  //Initialize sim
  auto seagrass_density = m_parameters.GetInitialSeagrassDensity();
  auto sulfide_concentration = m_parameters.GetInitialSulfideConcentration();
  auto organic_matter_density = m_parameters.GetInitialOrganicMatterDensity();
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
    const auto l = loripes_density;
    const auto s = sulfide_concentration;
    const double m{organic_matter_density};
    //Seagrass
    try
    {
      assert(m_parameters.GetSeagrassGrowthFunction());

      const auto growth = m_parameters.GetSeagrassGrowthFunction()->CalculateGrowth(n);
      const auto death_by_sulfide
        = poisoning_function->CalculateSurvivalFraction(s) * n.value()
      ;
      const auto delta_n = growth.value() - death_by_sulfide;
      seagrass_density += (delta_n * boost::units::si::species_per_square_meter * delta_t);
    }
    catch (std::logic_error& e)
    {
      std::stringstream s;
      s << "Simulation::Run(), calculating seagrass density: " << e.what();
      std::clog << s.str() << std::endl;
      return;
    }
    //Organic matter
    try
    {
      const auto capture = n.value() * m_parameters.GetOrganicMatterCapture();
      const auto addition = m_parameters.GetOrganicMatterAddition();
      const auto breakdown = m * m_parameters.GetOrganicMatterBreakdown();
      const double delta_m = capture + addition - breakdown;
      organic_matter_density += (delta_m * delta_t);
    }
    catch (std::logic_error& e)
    {
      std::stringstream s;
      s << "Simulation::Run(), calculating organic matter density: " << e.what();
      std::clog << s.str() << std::endl;
      return;
    }
    //Sulfide
    try
    {
      const auto organic_matter_breakdown
        = m_parameters.GetOrganicMatterToSulfideFactor()
        * m_parameters.GetOrganicMatterToSulfideRate()
        * m
      ;
      const auto diffusion
        = m_parameters.GetSulfdeDiffusionRate()
        * s
      ;
      const auto d0 = m_parameters.GetDetoxicationMinimum();
      const auto r = m_parameters.GetDetoxicationRate();
      const auto max = m_parameters.GetDetoxicationMaxRate();
      const auto detoxification
        = max
        * (d0 * std::exp(r * n.value())) / (1.0 + (d0 * std::exp(r * n.value())))
        * s.value()
      ;
      const auto consumption
        = m_parameters.GetLoripesConsumptionFunction()->CalculateConsumptionRate(n)
        * l.value()
        * s.value()
      ;
      const double delta_s
        = organic_matter_breakdown
        - diffusion.value()
        - detoxification
        - consumption
      ;

      sulfide_concentration += (
          delta_s * (boost::units::si::mole / boost::units::si::cubic_meter)
        * delta_t
      );

    }
    catch (std::logic_error& e)
    {
      std::stringstream s;
      s << "Simulation::Run(), calculating sulfide concentration: " << e.what();
      std::clog << s.str() << std::endl;
      return;
    }
    //Loripes density
    try
    {
      const auto r = m_parameters.GetRecruitmentRate();
      const auto K = m_parameters.GetRecruitmentMax();
      const auto mr = m_parameters.GetMutualismBreakdownRate();
      const auto mmax = m_parameters.GetMutualismBreakdownMax();
      const auto mr0 = m_parameters.GetMutualismBreakdownR0();
      //GF:
      //r * (1-(n/K))*)*(N-K) + k
      //const auto growth
      //  = l
      //  * (
      //    rmax + ((rr * (1.0-(l.value()/rmax))) * (l.value()-rmax))
      //  )

      //RF:
      //const auto growth = l * (rmax - ((rr * l.value()) / rmax))
      if (K == 0.0)
      {
        std::clog << "STUB" << std::endl;
        return;
      }
      //Logistic growth
      const auto growth = r*l*(1.0-(l.value()/K));
      /*
      const auto growth
        = 1.0 - (l.value() * rmax / (1.0 + (rmax * rr * l.value())))
      */
      /*
        * rr * (1.0 - (rmax / l.value()))
      */
        //* rmax
        //* (std::exp(-rr * l.value()))
        //* (1.0 - std::exp(-rr * l.value()))
      ;
      const auto mutualism_breakdown = l * mmax * (1.0 - ((mr0 * std::exp(mr * n.value())) / (1.0 + std::exp(mr * n.value()))));
      const auto delta_l
        = growth.value()
        - mutualism_breakdown.value()
      ;
      loripes_density += (delta_l * boost::units::si::species_per_square_meter * delta_t);
    }
    catch (std::logic_error& e)
    {
      std::stringstream s;
      s << "Simulation::Run(), calculating loripes density: " << e.what();
      std::clog << s.str() << std::endl;
      return;
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
  const auto& s = simulation.GetSulfideConcentrations();
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
