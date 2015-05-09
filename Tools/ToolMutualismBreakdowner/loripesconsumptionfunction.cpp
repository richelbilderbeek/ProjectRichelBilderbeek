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
    assert(std::abs(p(    0.0)-0.0) < 0.0001);
    assert(std::abs(p(    1.0)-0.0487706) < 0.0001);
    assert(std::abs(p(   10.0)-0.393469) < 0.0001);
    assert(std::abs(p(  100.0)-0.993262) < 0.0001);
    assert(std::abs(p( 1000.0)-1.0) < 0.0001);
    assert(std::abs(p(10000.0)-1.0) < 0.0001);
  }
}


double InvertedExponentialConsumption::operator()(
  const double seagrass_density
) const noexcept
{
  if (seagrass_density < 0.0)
  {
    std::cerr << seagrass_density << std::endl;
  }
  assert(seagrass_density >= 0.0);
  const double result{
    1.0 - std::exp(-m_r * seagrass_density)
  };
  if (result < 0.0)
  {
    std::cerr << result << " " << seagrass_density << std::endl;
    assert(result >= -0.005);
    return 0.0;
  }
  assert(result >= 0.0);
  assert(result <= 1.0);
  return result;
}
