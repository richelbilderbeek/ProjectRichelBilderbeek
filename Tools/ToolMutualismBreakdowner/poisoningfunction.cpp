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
  using boost::units::si::species_per_square_meters;
  {
    const InvertLogisticPoisoning f;
    assert(std::abs(f.CalculateSurvivalFraction( 0.0 * species_per_square_meters)-1.0) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction( 1.0 * species_per_square_meters)-1.0) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction(23.0 * species_per_square_meters)-0.5) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction(35.0 * species_per_square_meters)-0.1) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction(50.0 * species_per_square_meters)-0.0) < 0.1);
  }
}

double InvertLogisticPoisoning::CalculateSurvivalFraction(const ribi::units::SpeciesDensity seagrass_density) const
{
  if (seagrass_density < 0.0 * boost::units::si::species_per_square_meters)
  {
    std::stringstream s;
    s << "InvertLogisticPoisoning::operator(): "
      << "Seagrass density must be positive, "
      << "value supplied was " << seagrass_density
    ;
    throw std::logic_error(s.str());
  }
  assert(seagrass_density >= 0.0 * boost::units::si::species_per_square_meters);
  const double n{seagrass_density.value()};
  assert(n >= 0.0);
  const double numerator{-m_x0 * std::exp(m_r * n)};
  const double denominator{1.0 + (m_x0 * std::exp(m_r * n))};
  assert(denominator != 0.0);
  const double p_survive{
    1.0 + (numerator / denominator)
  };
  /*
  if (std::isnan(p_survive)) return 0.0;
  assert(!std::isinf(p_survive));
  assert(!std::isinf(-p_survive));
  */
  return p_survive;
}

std::string InvertLogisticPoisoning::ToStr() const noexcept
{
  std::stringstream s;
  s << "x0: " << m_x0 << ", r:" << m_r;
  return s.str();
}
