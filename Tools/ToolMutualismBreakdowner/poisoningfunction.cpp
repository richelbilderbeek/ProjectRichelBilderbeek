#include "poisoningfunction.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <boost/units/io.hpp>

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
    const InvertedExponentialPoisoning f;
  }
  /*
  {
    const InvertExponentialPoisoning f;
    assert(std::abs(f.CalculateSurvivalFraction( 0.0)-1.0) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction( 1.0)-1.0) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction(23.0)-0.5) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction(35.0)-0.1) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction(50.0)-0.0) < 0.1);
  }
  */
}

double InvertedExponentialPoisoning::CalculateSurvivalFraction(
  const double sulfide_concentration
) const
{
  if (sulfide_concentration < 0.0)
  {
    std::stringstream s;
    s << "InvertLogisticPoisoning::operator(): "
      << "sulfide_concentration must be positive, "
      << "value supplied was " << sulfide_concentration
    ;
    throw std::logic_error(s.str());
  }
  if (std::isnan(sulfide_concentration))
  {
    std::stringstream s;
    s << "InvertLogisticPoisoning::operator(): "
      << "sulfide_concentration must be a number, "
      << "value supplied was " << sulfide_concentration
    ;
    throw std::logic_error(s.str());
  }
  assert(sulfide_concentration >= 0.0);
  const double s{sulfide_concentration};
  assert(s >= 0.0);
  const double p_survive{
    m_max * (1.0 - std::exp(-m_r * s))
  };
  return p_survive;
}

std::string InvertedExponentialPoisoning::ToStr() const noexcept
{
  std::stringstream s;
  s << "max: " << m_max << ", r:" << m_r;
  return s.str();
}
