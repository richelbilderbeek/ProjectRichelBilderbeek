#include "brownianmotionhelper.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include <boost/math/constants/constants.hpp>

#include "testtimer.h"

ribi::bm::Helper::Helper()
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::bm::Helper::CalcLogLikelihood(
  const std::vector<double>& v,
  const VolatilitySquared cand_volatility_squared
  //const double cand_volatility
) const
{
  assert(!v.empty());

  using boost::math::constants::two_pi;

  if (cand_volatility_squared == 0.0 / boost::units::si::second / boost::units::si::second) return 0.0; //TODO: allow this
  const double n{static_cast<double>(v.size())};
  const double log_likelihood{
    -((n/2.0)*std::log(cand_volatility_squared.value() * two_pi<double>()))
    - std::inner_product(
        std::begin(v)+1,
        std::end(v),
        std::begin(v),
        0.0,
        std::plus<double>(),
        [cand_volatility_squared](const double a, const double b)
        {
          return std::pow(a - b,2.0) / (2.0 * cand_volatility_squared.value());
        }
      )
  };
  return log_likelihood;
}

void ribi::bm::Helper::CalcMaxLikelihood(
  const std::vector<double>& v,
  Volatility& volatility_hat
) const
{
  const bool verbose{false};
  const double n{static_cast<double>(v.size())};
  const double sum{
    std::inner_product(
      std::begin(v)+1,
      std::end(v),
      std::begin(v),
      0.0,
      std::plus<double>(),
      [](const double a, const double b)
      {
        return std::pow(a - b,2.0);
      }
    )
  };

  const double volatility_hat_squared{sum / n};

  if (verbose)
  {
    std::cout
      << "sum: " << sum << '\n'
      << "n: " << n << '\n'
      << "volatility_hat_squared: " << volatility_hat_squared << '\n'
    ;
  }
  volatility_hat = std::sqrt(volatility_hat_squared) / boost::units::si::second;
}

double ribi::bm::Helper::CalcMaxLogLikelihood(
  const std::vector<double>& v
) const
{
  Volatility volatility_hat = 0.0 / boost::units::si::second;
  CalcMaxLikelihood(v,volatility_hat);
  return CalcLogLikelihood(v,volatility_hat * volatility_hat);
}

#ifndef NDEBUG
void ribi::bm::Helper::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
