#include "loripesconsumptionfunction.h"

#include <cassert>
#include <cmath>
#include <iostream>

void LoripesConsumptionFunction::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const InvertedExponentialConsumption p;
    assert(std::abs(p(    0.0)-0.0) < 0.1);
    assert(std::abs(p(   20.0)-0.6) < 0.1);
    assert(std::abs(p(   60.0)-0.9) < 0.1);
    assert(std::abs(p(  100.0)-1.0) < 0.1);
  }
}

InvertedExponentialConsumption::InvertedExponentialConsumption(
  const double r)
  : m_r{r}
{
  assert(m_r >= 0.0);
}


double InvertedExponentialConsumption::operator()(
  const double seagrass_density
) const noexcept
{
  const double result{
    1.0 - std::exp(-m_r * seagrass_density)
  };
  if (result < 0.0)
  {
    return 0.0;
  }
  assert(result >= 0.0);
  assert(result <= 1.0);
  return result;
}
