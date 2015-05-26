#include "ornsteinuhlenbeck.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "testtimer.h"

ribi::OrnsteinUhlenbeck::OrnsteinUhlenbeck(
  const PositiveNonZeroDouble lambda,
  const double mu,
  const double sigma,
  const int rng_seed
)
  : m_lambda{lambda},
    m_mu{mu},
    m_sigma{sigma},
    m_rng(rng_seed),
    m_rng_seed{rng_seed},
    m_normal_distribution(0.0,1.0)
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::OrnsteinUhlenbeck::CalcNext(const double x, const double dt)
{
  try
  {
    return CalcNext(x,PositiveNonZeroDouble(dt));
  }
  catch (std::logic_error&)
  {
    std::stringstream s;
    s << __func__ << ": delta t must be non-zero and positive, delta t given: " << dt;
    throw std::logic_error(s.str());
  }
}

double ribi::OrnsteinUhlenbeck::CalcNext(const double x, const PositiveNonZeroDouble dt) noexcept
{
  const double random_normal{m_normal_distribution(m_rng)};
  return CalcNext(x,dt,random_normal);
}

double ribi::OrnsteinUhlenbeck::CalcNext(const double x, const double dt, const double random_normal) const
{
  try
  {
    return CalcNext(x,PositiveNonZeroDouble(dt),random_normal);
  }
  catch (std::logic_error&)
  {
    std::stringstream s;
    s << __func__ << ": delta t must be non-zero and positive, delta t given: " << dt;
    throw std::logic_error(s.str());
  }

}

double ribi::OrnsteinUhlenbeck::CalcNext(const double x, const PositiveNonZeroDouble dt_safe, const double random_normal) const noexcept
{
  const double lambda{m_lambda.Get()};
  const double dt{dt_safe.Get()};
  const double term1{x*std::exp(-lambda*dt)};
  const double term2{m_mu * (1.0-std::exp(-lambda*dt))};
  const double term3{m_sigma * random_normal * std::sqrt((1.0 - std::exp(-2.0*lambda*dt))  / (2.0 * lambda))};
  const double new_x{
      term1
    + term2
    + term3
  };
  return new_x;

}


#ifndef NDEBUG
void ribi::OrnsteinUhlenbeck::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const std::vector<double> ns
    = {
     -1.0268,
     -0.4985,
      0.3825,
     -0.8102,
     -0.1206,
     -1.9604,
      0.2079,
      0.9134,
      2.1375,
      0.5461,
      1.4335,
      0.4414,
     -2.2912,
      0.3249,
     -1.3019,
     -0.8995,
      0.0281,
     -1.0959,
     -0.8118,
     -1.3890
    };
  const std::vector<double> ss
    = {
      1.7600,
      1.2693,
      1.1960,
      0.9468,
      0.9532,
      0.6252,
      0.8604,
      1.0984,
      1.4310,
      1.3019,
      1.4005,
      1.2686,
      0.7147,
      0.9237,
      0.7297,
      0.7105,
      0.8683,
      0.7406,
      0.7314,
      0.6232
    };
  assert(ss.size() == ns.size());


  {
    ///Many thanks to Thijs van den Berg from sitmo.com
    ///to allow for this detailed test
    double x = 3.0;
    OrnsteinUhlenbeck p(3.0,1.0,0.5);
    const int n{static_cast<int>(ns.size())};
    for (int i=0; i!=n; ++i)
    {
      x = p.CalcNext(x,0.25,ns[i]);
      assert(std::abs(x - ss[i]) < 0.01);
    }
  }
}
#endif
