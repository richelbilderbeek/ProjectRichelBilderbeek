#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "parameters.h"

struct Simulation
{
  Simulation(const Parameters& parameters);

  const std::vector<double>& GetAxs() const noexcept { return m_axs; }
  const std::vector<double>& GetAys() const noexcept { return m_ays; }
  const std::vector<double>& GetBxs() const noexcept { return m_bxs; }
  const std::vector<double>& GetBys() const noexcept { return m_bys; }
  const std::vector<double>& GetSumxs() const noexcept { return m_sumxs; }
  const std::vector<double>& GetSumys() const noexcept { return m_sumys; }

  void Run() noexcept;

  private:
  const Parameters m_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  std::vector<double> m_axs;
  std::vector<double> m_ays;
  std::vector<double> m_bxs;
  std::vector<double> m_bys;
  std::vector<double> m_sumxs;
  std::vector<double> m_sumys;
};

#endif // SIMULATION_H
