#include "poisoningfunction.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>

#include "testtimer.h"

void PoisoningFunction::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  {
    const InvertLogisticPoisoning p;
    assert(std::abs(p(    0.0)-1.0) < 0.1);
    assert(std::abs(p(    1.0)-1.0) < 0.1);
    assert(std::abs(p(   23.0)-0.5) < 0.1);
    assert(std::abs(p(   35.0)-0.1) < 0.1);
    assert(std::abs(p(   50.0)-0.0) < 0.1);
  }
}

double InvertLogisticPoisoning::operator()(const double seagrass_density) const
{
  const double numerator{-m_x0 * std::exp(m_r * seagrass_density)};
  const double denominator{1.0 + (m_x0 * std::exp(m_r * seagrass_density))};
  assert(denominator != 0.0);
  const double p_survive{
    1.0 + (numerator / denominator)
  };
  if (std::isnan(p_survive)) return 0.0;
  assert(!std::isinf(p_survive));
  assert(!std::isinf(-p_survive));
  return p_survive;
}

std::string InvertLogisticPoisoning::ToStr() const noexcept
{
  std::stringstream s;
  s << "x0: " << m_x0 << ", r:" << m_r;
  return s.str();
}
