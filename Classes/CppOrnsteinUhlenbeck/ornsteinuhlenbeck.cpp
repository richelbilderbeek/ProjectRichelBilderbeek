#include "ornsteinuhlenbeck.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

OrnsteinUhlenbeck::OrnsteinUhlenbeck(
  const double lambda,
  const double mu,
  const double sigma,
  const int rng_seed
)
  : m_lambda{lambda},
    m_mu{mu},
    m_sigma{sigma},
    m_rng(rng_seed),
    m_rng_seed{rng_seed}
{
  #ifndef NDEBUG
  Test();
  #endif
  if (lambda <= 0.0)
  {
    std::stringstream s;
    s << __func__ << ": lambda must be non-zero and positive, lambda given: " << lambda;
    throw std::logic_error(s.str());
  }
}

double OrnsteinUhlenbeck::CalcNext(const double x, const double dt, const double random_normal) const noexcept
{
  const double term1{x*std::exp(-m_lambda*dt)};
  const double term2{m_mu * (1.0-std::exp(-m_lambda*dt))};
  const double term3{m_sigma * random_normal * std::sqrt((1.0 - std::exp(-2.0*m_lambda*dt))  / (2.0 * m_lambda))};
  const double new_x{
      term1
    + term2
    + term3
  };
  return new_x;
}

#ifndef NDEBUG
void OrnsteinUhlenbeck::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ///Many thanks to Thijs van den Berg from sitmo.com
    ///to allow for this detailed test
    double x = 3.0;
    OrnsteinUhlenbeck p(3.0,1.0,0.5);
    x = p.CalcNext(x,0.25,-1.0268);
    assert(x > 1.7 && x < 1.8);
    x = p.CalcNext(x,0.25,-0.4985);
    assert(x > 1.2 && x < 1.3);
    x = p.CalcNext(x,0.25,0.3825);
    assert(x > 1.1 && x < 1.2);
    x = p.CalcNext(x,0.25,-0.8102);
    assert(x > 0.9 && x < 1.0);
    x = p.CalcNext(x,0.25,-0.1206);
    assert(x > 0.9 && x < 1.0);
    x = p.CalcNext(x,0.25,-1.9604);
    assert(x > 0.6 && x < 0.7);
    x = p.CalcNext(x,0.25,0.2079);
    assert(x > 0.8 && x < 0.9);
  }
}
#endif
