#include "poisoningfunction.h"

#include <cassert>
#include <cmath>
#include <iostream>

void PoisoningFunction::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const InvertLogisticPoisoning p;
    assert(std::abs(p(    0.0)) <= 1.0);
    assert(std::abs(p(    1.0)-0.83208) < 0.0001);
    assert(std::abs(p(   10.0)-0.820456) < 0.0001);
    assert(std::abs(p(  100.0)-0.670277) < 0.0001);
    assert(std::abs(p( 1000.0)-0.000616669) < 0.0001);
    assert(std::abs(p(10000.0)-2.45572e-17) < 0.0001);
  }
}

double InvertLogisticPoisoning::operator()(const double seagrass_density) const noexcept
{
  const double p_survive{
    1.0 - (m_x0 * std::exp(m_r * seagrass_density))
    / (1.0 + (m_x0 * std::exp(m_r * seagrass_density)))
  };
  return std::isnan(p_survive) ? 0.0 : p_survive;
}
