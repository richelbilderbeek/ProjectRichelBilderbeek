#include "mutualismbreakdownerseagrasssystem.h"

#include <iostream>

#include "mutualismbreakdownerseagrassgrowthfunction.h"
#include "mutualismbreakdownerpoisoningfunction.h"
#include "mutualismbreakdownersulfideconsumptionfunction.h"
#include "mutualismbreakdownersulfidedetoxificationfunction.h"
#include "mutualismbreakdownersulfidediffusionfunction.h"
#include "mutualismbreakdownersulfideproductionfunction.h"

ribi::mb::SeagrassSystem::SeagrassSystem(const Parameters& parameters)
  : m_parameters{parameters},
    m_seagrass_density{parameters.GetInitialSeagrassDensity()},
    m_sulfide_concentration{parameters.GetInitialSulfideConcentration()}
{

}

void ribi::mb::SeagrassSystem::Change(const Time delta_t)
{
  const auto n = m_seagrass_density;
  const auto s = m_sulfide_concentration;

  //Seagrass
  try
  {
    const auto growth = m_parameters.GetSeagrassGrowthFunction()->CalculateGrowth(n);
    const auto poisoning = m_parameters.GetPoisoningFunction()->CalculateDecline(n,s);
    const auto delta_n = growth - poisoning;
    m_seagrass_density += (delta_n * delta_t);
  }
  catch (std::logic_error& e)
  {
    std::stringstream s;
    s << __func__ << ": calculating seagrass density: " << e.what();
    std::clog << s.str() << std::endl;
    return;
  }
  //Sulfide
  try
  {
    const auto loripes_density = m_parameters.GetInitialLoripesDensity();
    const auto production = m_parameters.GetSulfideProductionFunction()->CalculateProduction(n);
    const auto detoxification = m_parameters.GetSulfideDetoxificationFunction()->CalculateDetoxification(n,s);
    const auto diffusion = m_parameters.GetSulfideDiffusionFunction()->CalculateDiffusion(s);
    const auto consumption = m_parameters.GetSulfideConsumptionFunction()->CalculateConsumption(s,loripes_density);
    const auto delta_s
      = production
      - diffusion
      - detoxification
      - consumption
    ;

    m_sulfide_concentration += (delta_s * delta_t);

  }
  catch (std::logic_error& e)
  {
    std::stringstream s;
    s << __func__ << ":, calculating sulfide concentration: " << e.what();
    std::clog << s.str() << std::endl;
    return;
  }
}
