#include "brownianmotion.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include <boost/math/constants/constants.hpp>

#include "testtimer.h"

ribi::BrownianMotion::BrownianMotion(
  const double volatility,
  const int rng_seed
)
  : m_normal_distribution(0.0,1.0),
    m_rng(rng_seed),
    m_rng_seed{rng_seed},
    m_volatility{volatility}
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::BrownianMotion::CalcLogLikelihood(
  const std::vector<double>& v,
  const double cand_volatility
)
{
  assert(!v.empty());

  using boost::math::constants::two_pi;

  if (cand_volatility == 0.0) return 0.0; //TODO: allow this
  const double n{static_cast<double>(v.size())};
  const double log_likelihood{
    -((n/2.0)*std::log(cand_volatility * two_pi<double>()))
    - std::inner_product(
        std::begin(v)+1,
        std::end(v),
        std::begin(v),
        0.0,
        std::plus<double>(),
        [cand_volatility](const int a, const double b)
        {
          return std::pow(a - b,2.0) / (2.0 * cand_volatility);
        }
      )
  };
  return log_likelihood;

  /*
  const double cand_var{
    std::pow(cand_volatility,2.0) * ((1.0 - std::exp(-2.0 * dt)) / 2.0)
  };
  #ifndef NDEBUG
  if (cand_var <= 0.0) std::cerr << cand_var << std::endl;
  #endif
  assert(cand_var > 0.0);

  const double sum{
    std::inner_product(
      std::begin(v)+1,
      std::end(v),
      std::begin(v),
      0.0,
      std::plus<double>(),
      [dt](const int a, const double b)
      {
        return a - (b * std::exp(-dt));
      }
    )
  };
  const double log_likelihood{
    - ((n/2.0)*std::log(boost::math::constants::two_pi<double>()))
    - (n*std::log(cand_var))
    - ((1.0/(2.0*cand_var))*sum)
  };
  return log_likelihood;
  */
}

void ribi::BrownianMotion::CalcMaxLikelihood(
  const std::vector<double>& v,
  double& volatility_hat
)
{
  volatility_hat = 0.0 * v.size();
}

double ribi::BrownianMotion::CalcNext(const double x)
{
  const double random_normal{m_normal_distribution(m_rng)};
  return CalcNext(x,random_normal);
}

double ribi::BrownianMotion::CalcNext(
  const double x,
  const double random_normal
) const
{
  const double dt{1.0};
  const double dx{
    random_normal * m_volatility
  };
  return x + (dt * dx);
}

#ifndef NDEBUG
void ribi::BrownianMotion::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Create a Brownian motion with volatility
  {
    const double volatility{1.0};
    BrownianMotion b(volatility);
    double x{0.0};
    std::vector<double> v = {x};
    for (int i=0; i!=100; ++i)
    {
      x = b.CalcNext(x);
      v.push_back(x);
    }
    const double good_likelihood{BrownianMotion::CalcLogLikelihood(v,volatility)};
    const double bad_likelihood{BrownianMotion::CalcLogLikelihood(v,volatility * 0.5)};
    const double worse_likelihood{BrownianMotion::CalcLogLikelihood(v,volatility * 1.5)};
    assert(good_likelihood > worse_likelihood);
    assert(good_likelihood > bad_likelihood);
  }
}
#endif
