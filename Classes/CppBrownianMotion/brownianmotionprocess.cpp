#include "brownianmotionprocess.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "brownianmotionhelper.h"
#include <boost/math/constants/constants.hpp>

#include "testtimer.h"

ribi::bm::Process::Process(
  const Parameters& parameters
)
  : m_normal_distribution(0.0,1.0),
    m_parameters{parameters},
    m_rng(parameters.GetRngSeed())
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::bm::Process::CalcNext(const double x)
{
  const double random_normal{m_normal_distribution(m_rng)};
  return CalcNext(x,random_normal);
}

double ribi::bm::Process::CalcNext(
  const double x,
  const double random_normal
) const
{
  const double dt{1.0};
  const double volatility{m_parameters.GetVolatility()};
  const double dx{
    random_normal * volatility
  };
  return x + (dt * dx);
}

#ifndef NDEBUG
void ribi::bm::Process::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Helper();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Create a Brownian motion with volatility
  {
    const double volatility{1.0};
    bm::Process b(volatility);
    double x{0.0};
    std::vector<double> v = {x};
    for (int i=0; i!=100; ++i)
    {
      x = b.CalcNext(x);
      v.push_back(x);
    }
    //Are the likelihoods best at the true volatility?
    const double good_likelihood{Helper().CalcLogLikelihood(v,volatility)};
    const double bad_likelihood{Helper().CalcLogLikelihood(v,volatility * 0.5)};
    const double worse_likelihood{Helper().CalcLogLikelihood(v,volatility * 1.5)};
    assert(good_likelihood > worse_likelihood);
    assert(good_likelihood > bad_likelihood);
    //Is the max likelihood truly the max likelihood?
    double volatility_hat{0.0};
    Helper().CalcMaxLikelihood(v,volatility_hat);
    const double max_likelihood{Helper().CalcLogLikelihood(v,volatility_hat)};
    assert(max_likelihood > good_likelihood);
  }
}
#endif
