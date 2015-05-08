#include "simulation.h"
#include <cmath>

Simulation::Simulation(const Parameters& parameters)
  : m_parameters{parameters},
    m_axs{},
    m_ays{},
    m_bxs{},
    m_bys{},
    m_sumxs{},
    m_sumys{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

void Simulation::Run() noexcept
{

}
