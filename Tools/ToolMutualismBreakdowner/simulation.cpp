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
  /*
  const int n_timesteps{
    ui->box_n_timesteps->value()
  };
  std::vector<double> seagrass_densities;
  std::vector<double> sulfide_concentrations;
  const double initial_seagrass_density{
    ui->box_initial_seagrass_density->value()
  };

  const double seagrass_carrying_capacity{1.0};
  const double seagrass_growth_rate{
    ui->box_seagrass_growth_rate->value()
  };
  const double desiccation_stress{
    ui->box_desiccation_stress->value()
  };
  const double sulfide_mol_per_seagrass_density{
    ui->box_sulfide_mol_per_seagrass_density->value()
  };

  const double sulfide_toxicity{
    ui->box_sulfide_toxicity->value()
  };

  const double oxygen_inhibition_strength{
    ui->box_oxygen_inhibition_strength->value()
  };
  const double oxygen_production{
    ui->box_oxygen_production->value()
  };
  */

  //Initialize sim
  double seagrass_density{m_parameters.initial_seagrass_density};
  double sulfide_concentration{0.0};
  //double oxygen_concentration{initial_oxygen_concentration};
  for (int i=0; i!=n_timesteps; ++i)
  {
    m_timeseries.push_back(static_cast<double>(i));
    //Sim here
    {
      const double r{m_parameters.seagrass_growth_rate};
      const double k{m_parameters.seagrass_carrying_capacity};
      const double n{seagrass_density};
      const double m{m_parameters.desiccation_stress};
      const double t{m_parameters.sulfide_toxicity};
      const double s{sulfide_concentration};
      seagrass_density
        += r*n*(1.0-(n/k)) //Growth
        - (n*m) //Leaf loss
        - (t*s)
      ;
    }
    {
      using std::exp;
      const double n{seagrass_density};
      const double m{m_parameters.desiccation_stress};
      const double f{m_parameters.sulfide_mol_per_seagrass_density};
      const double a{m_parameters.oxygen_inhibition_strength};
      const double p{m_parameters.oxygen_production};
      sulfide_concentration
        += (n*m*f*exp(-a*p*n))
      ;

    }
    m_seagrass_densities.push_back(seagrass_density);
    m_sulfide_concentrations.push_back(sulfide_concentration);
  }
}
