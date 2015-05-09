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
    assert(std::abs(p(    0.0)) >= 0.0);
    assert(std::abs(p(    0.0)) <= 1.0);

    assert(std::abs(p(    1.0)) >= 0.0);
    assert(std::abs(p(    1.0)) <= 1.0);

    assert(std::abs(p(   10.0)) >= 0.0);
    assert(std::abs(p(   10.0)) <= 1.0);

    assert(std::abs(p(  100.0)) >= 0.0);
    assert(std::abs(p(  100.0)) <= 1.0);

    assert(std::abs(p( 1000.0)) >= 0.0);
    assert(std::abs(p( 1000.0)) <= 1.0);

    assert(std::abs(p(10000.0)) >= 0.0);
    assert(std::abs(p(10000.0)) <= 1.0);
  }
}

double InvertLogisticPoisoning::operator()(const double seagrass_density) const noexcept
{
  const double numerator{-m_x0 * std::exp(m_r * seagrass_density)};
  const double denominator{1.0 + (m_x0 * std::exp(m_r * seagrass_density))};
  const double p_survive{
    1.0 + (numerator / denominator)
  };
  if (std::isnan(p_survive)) return 0.0;
  return p_survive;
}
